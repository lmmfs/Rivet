# Phase 11 — UI Panels: Requirements

## Scope

A minimal in-game UI system built on top of the existing 2D renderer (Phase 7).
This is **not** a replacement for Dear ImGui — ImGui stays for debug overlays only.
This layer provides player-facing, game-world UI (HUD, health bars, in-game menus).

## Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Renderer | Phase 7 textured quad / batch renderer | Reuse existing infrastructure; no extra dep |
| Font rendering | stb_truetype (already available via stb vendor) | Vendored, lightweight, no runtime dep |
| Font format | TTF | Universal, well-supported by stb_truetype |
| ImGui | Debug / editor only — unchanged | ImGui is not appropriate for game UI |
| Component API | Free functions (procedural, raylib-style) | Matches mission principles |
| Button interaction | Callback (function pointer or std::function) on click | Simple and non-intrusive |
| Panel nesting | Not in this phase — flat panels only | Keep scope small; revisit if needed |
| Layout | Manual positioning (x, y, width, height) | Simplest first; no layout engine |

## Components

- **Font** — load a TTF file, generate a glyph atlas texture, expose metrics
- **Panel** — a positioned, colored rectangle; acts as a background container
- **Label** — renders text at a position using a loaded Font
- **Button** — a Panel with a Label and an onClick callback
- **HealthBar** — a filled rectangle with a normalized `fill` value (0.0–1.0), two colors (bg/fg)

## Context

- Builds on: Phase 4 (renderer), Phase 5 (buffer layouts), Phase 7 (2D drawing, camera)
- Font atlas texture is a regular Rivet texture managed through the Asset Manager (Phase 8)
- All UI coordinates are in screen space (pixels), not world space
