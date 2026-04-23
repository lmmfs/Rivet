# Phase 11 — UI Panels: Validation

## Build

- [ ] Project compiles with no errors and no new warnings
- [ ] `stb_truetype` integration does not break existing stb_image usage

## Font

- [ ] A TTF font loads without crashing
- [ ] Glyph atlas texture is generated and uploaded to the GPU successfully
- [ ] Text renders visibly in the Sandbox at two different font sizes

## Panel

- [ ] A colored rectangle renders at the correct screen position and size
- [ ] Alpha transparency visibly blends with the scene behind it

## Label

- [ ] A Label renders readable text using the loaded font
- [ ] `MeasureText` returns a non-zero size matching the visible text bounds

## Button

- [ ] Button renders panel + label together
- [ ] Clicking the button area fires the `onClick` callback (spdlog message appears)
- [ ] Clicking outside the button does NOT fire the callback

## HealthBar

- [ ] HealthBar renders background and foreground rects at correct proportions
- [ ] fill=0.0 shows only background; fill=1.0 fills entirely with foreground color
- [ ] Animated fill (sine wave) updates smoothly each frame

## Sandbox Demo

- [ ] Panel visible in top-left with FPS label inside
- [ ] Button visible and clickable
- [ ] HealthBar animates visibly
- [ ] No visual Z-fighting or draw-order issues with the 2D scene

## Merge Criteria

All checkboxes above pass. Phase 11 is checked off in `Specs/roadmap.md`.
