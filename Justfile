set dotenv-filename := "project.env"
set dotenv-load := true

project_name := env_var("NAME")
project_version := env_var("VERSION")

binary := "bin/" + project_name
web_binary := "bin/" + project_name + ".html"
c_env := "-DAPP_NAME=\\\"" + project_name + "\\\" " + \
         "-DAPP_VERSION=\\\"" + project_version + "\\\""
files := "$(find src -name \"*.c\")"
xargs := "$(xargs < compile_flags.txt)"

_create-bin:
    mkdir -p bin

_create-lib:
    mkdir -p lib

_pull-repo dir repo commit:
    @if [ ! -d "{{dir}}/.git" ]; then      \
        git clone {{repo}} {{dir}}; \
    fi
    @if [ "$(git -C {{dir}} rev-parse HEAD)" != "{{commit}}" ]; then \
        git -C {{dir}} fetch --all && \
        git -C {{dir}} checkout {{commit}}; \
    fi

build-raylib-web: _create-lib
    just _pull-repo lib/raylib https://github.com/raysan5/raylib dbc56a87da87d973a9c5baa4e7438a9d20121d28
    if [ ! -e "lib/raylib/src/libraylib.web.a" ]; then \
        emcc -c lib/raylib/src/rcore.c     -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -o lib/raylib/src/rcore.o; \
        emcc -c lib/raylib/src/rshapes.c   -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -o lib/raylib/src/rshapes.o; \
        emcc -c lib/raylib/src/rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -o lib/raylib/src/rtextures.o; \
        emcc -c lib/raylib/src/rtext.c     -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -o lib/raylib/src/rtext.o; \
        emcc -c lib/raylib/src/rmodels.c   -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 -o lib/raylib/src/rmodels.o; \
        emcc -c lib/raylib/src/raudio.c    -Os -Wall -DPLATFORM_WEB                           -o lib/raylib/src/raudio.o; \
        emar rcs lib/raylib/src/libraylib.web.a lib/raylib/src/rcore.o lib/raylib/src/rshapes.o lib/raylib/src/rtextures.o lib/raylib/src/rtext.o lib/raylib/src/rmodels.o lib/raylib/src/raudio.o; \
    fi

build-raylib: _create-lib
    just _pull-repo lib/raylib https://github.com/raysan5/raylib dbc56a87da87d973a9c5baa4e7438a9d20121d28
    if [ ! -e "lib/raylib/src/libraylib.a" ]; then \
        make -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP GRAPHICS=GRAPHICS_API_OPENGL_33 raylib; \
    fi

build-web: _create-bin build-raylib-web
    emcc {{ xargs }} -Llib/raylib/src -lraylib.web -Ilib/raylib/src --preload-file resources {{ c_env }} -DPLATFORM_WEB -s USE_GLFW=3 --shell-file lib/raylib/src/minshell.html {{ files }} -o {{ web_binary }}

build: _create-bin build-raylib
    gcc {{ xargs }} -Ilib/raylib/src -Llib/raylib/src {{ c_env }} {{ files }} -Wl,--start-group -Wl,--allow-multiple-definition -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,--end-group -o {{ binary }}

build-asan: _create-bin build-raylib
    gcc {{ xargs }} -Ilib/raylib/src -Llib/raylib/src {{ c_env }} -fsanitize=address -g {{ files }} -Wl,--start-group -Wl,--allow-multiple-definition -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,--end-group -o {{ binary }}

build-profiler: _create-bin build-raylib
    gcc {{ xargs }} -Ilib/raylib/src -Llib/raylib/src {{ c_env }} -pg -O0 -g {{ files }} -Wl,--start-group -Wl,--allow-multiple-definition -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wl,--end-group -o {{ binary }}

run:
    {{ binary }} | tee log.log

run-asan: build-asan run

run-profiler: build-profiler run
    gprof bin/main gmon.out > profile.txt
    cat profile.txt

clear:
    rm -rf bin

update-compiler-defines:
    bear -- just build

default: build run
