#pragma once

#include "common.h"

void GuiWindowFloating(Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing, void (*draw_content)(Vector2, Vector2), Vector2 content_size, Vector2 *scroll, const char* title, bool crossIcon, bool interactive, bool alwaysActive);
bool IsCursorOnWindow(const Vector2 cursorPos, const Vector2 *position, const Vector2 *size, const bool *minimized);
