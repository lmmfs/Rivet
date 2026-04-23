# Phase 11 — UI Panels: Plan

## Task Group 1 — Font System

1.1 Add `stb_truetype.h` to `Rivet/Vendor/stb/` (or confirm already present)
1.2 Define `Font` struct: TTF path, glyph atlas texture, glyph metrics map, font size
1.3 Implement `Font LoadFont(const std::string& path, float size)` — loads TTF, rasterizes glyphs, uploads atlas to GPU
1.4 Implement `void UnloadFont(Font& font)`
1.5 Expose `Font` through the Asset Manager (Phase 8 FontManager)

## Task Group 2 — Panel Component

2.1 Define `Panel` struct: position (x, y), size (width, height), background color
2.2 Implement `void DrawPanel(const Panel& panel)` using the Phase 7 batch renderer
2.3 Support alpha transparency on panel background

## Task Group 3 — Label Component

3.1 Define `Label` struct: text, position, font reference, color, scale
3.2 Implement `void DrawLabel(const Label& label)` — renders glyphs from atlas as quads
3.3 Implement `glm::vec2 MeasureText(const Font& font, const std::string& text, float scale)` — returns bounding size

## Task Group 4 — Button Component

4.1 Define `Button` struct: Panel, Label, `std::function<void()> onClick`
4.2 Implement `void DrawButton(const Button& button)` — draws panel + label
4.3 Implement `bool UpdateButton(Button& button, glm::vec2 mousePos, bool mousePressed)` — hit test + fires callback
4.4 Integrate UpdateButton into the input polling step (before draw)

## Task Group 5 — HealthBar Component

5.1 Define `HealthBar` struct: position, size, fill (0.0–1.0), foreground color, background color
5.2 Implement `void DrawHealthBar(const HealthBar& bar)` — two layered quads (bg then fg)
5.3 Clamp fill value to [0, 1]

## Task Group 6 — UI Module Header

6.1 Create `Rivet/UI.h` umbrella header exposing Font, Panel, Label, Button, HealthBar and all free functions
6.2 Include `UI.h` in the main `Rivet/Rivet.h` umbrella

## Task Group 7 — Sandbox Integration & Demo

7.1 Load a TTF font in the Sandbox
7.2 Render a Panel in the top-left corner
7.3 Render a Label with the current FPS inside the panel
7.4 Render a Button; on click print "Button clicked" via spdlog
7.5 Render a HealthBar; animate fill value over time (sine wave)
7.6 Confirm all UI renders correctly over the 2D scene (correct depth / draw order)
