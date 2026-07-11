# MergeColony

MergeColony is a city-building-simulator style game, where your objective is to build a Mars colony as big as you can!

This game was made in 5 days by a team of 4 people for [raylib 6.x gamejam](https://itch.io/jam/raylib-6x-gamejam).

The core mechanic of this game is that you can merge adjacent buildings together to save space, increase ore production or make people happier! You are able to build only 4 basic buildings. You can acquire other buildings only by merging basic ones.

Don't forget about your own citizens! If you build a mining facility under someone's window, they will not like it and will just leave your colony for good.

## Installation

You can play this game online on [itch.io page](https://gearshift-interactive.itch.io/mergecolony), install the archive with native binary for your platform or build it from source.

### Building from source

Requirements:
- **OS**: Windows
- **Compiler**: GCC (also Emscripten if you want to build for WASM)
- **Task runner**: Just

To build this game simply clone the repo and run `just build` or `just build-web`:
```sh
git clone https://codeberg.org/Priklen/MergeColony
cd MergeColony
just build
```

## License

The project uses multiple licenses.

| Content | License |
|---------|---------|
| Source code | MIT |
| Art, textures, shaders, fonts, data | MIT |
| Files inside `resources/audio/` | All Rights Reserved (see LICENSE-AUDIO) |

Unless explicitly stated otherwise, every file outside
`resources/audio/` is licensed under the MIT License.
