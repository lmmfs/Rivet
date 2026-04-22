# Phase 10 — Audio: Requirements

## Scope

Integrate audio playback into Rivet using **miniaudio** (single-header, no external dependencies). Expose a clean, procedural API consistent with Rivet's raylib-style philosophy. Audio assets are managed through the existing Asset Manager introduced in Phase 8.

## Goals

- Load and play **WAV** and **OGG** audio files.
- Support **play, stop, pause, resume, loop** controls.
- Per-sound **volume** control.
- **2D positional audio** (pan/attenuation based on emitter position relative to a listener).
- Audio assets (sounds) managed by an `AudioManager` that follows the same handle-based pattern as `TextureManager` and `ShaderManager`.

## Non-Goals

- 3D (z-axis) audio spatialization.
- Audio effects / DSP pipeline.
- Streaming for very large music files (can be revisited).
- Multiple simultaneous listener positions.

## Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Audio library | miniaudio | Single-header, no deps, MIT licensed, supports WAV + OGG via built-in decoders |
| Asset integration | `AudioManager` inside existing Asset Manager | Consistent with Phase 8 pattern; avoids scattered raw handles |
| API style | Free functions (`rvt::audio::*`) | Matches Rivet's procedural, raylib-style API |
| 2D positional | Pan + volume falloff via `ma_sound_set_position` / spatialization engine | miniaudio has a built-in spatialization engine sufficient for 2D |

## Context

- Phases 1–9 are complete and merged to `main`.
- The Asset Manager (Phase 8) provides a `ResourceHandle<T>` pattern with `TextureManager` and `ShaderManager` as precedents.
- miniaudio will be vendored or fetched via CMake `FetchContent` using its single-header distribution.
- All audio calls must be safe to make from the main thread (miniaudio runs its own decode/mix thread internally).
