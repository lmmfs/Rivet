# Phase 10 — Audio: Validation

## Build

- [ ] Project compiles without warnings on Linux with miniaudio vendored.
- [ ] `MINIAUDIO_IMPLEMENTATION` is defined exactly once (no duplicate symbol linker errors).

## Audio Engine

- [ ] spdlog prints `[AudioEngine] Initialized` on startup and `[AudioEngine] Shutdown` on exit.
- [ ] No crash or hang on clean shutdown after audio has been played.

## Sound Loading

- [ ] A `.wav` file loads successfully and `Sound` holds a valid `ma_sound`.
- [ ] An `.ogg` file loads successfully.
- [ ] Passing a non-existent path logs an error and returns a null/invalid handle (no crash).

## Playback Controls

- [ ] `Play` causes audible output.
- [ ] `Stop` halts playback and rewinds to the start.
- [ ] `Pause` / `Resume` continue from the same position.
- [ ] `SetLoop(true)` makes the sound repeat continuously; `SetLoop(false)` stops after one play.
- [ ] `SetVolume(0.5f)` is noticeably quieter than `SetVolume(1.0f)`.
- [ ] `IsPlaying` returns `true` while playing and `false` after stopping.

## 2D Positional Audio

- [ ] Sound pans left when emitter x < listener x and right when emitter x > listener x.
- [ ] Volume attenuates as the emitter moves farther from the listener (beyond the configured max distance, sound is inaudible).
- [ ] Setting listener position to match the emitter produces center-panned, full-volume output.

## Asset Manager Integration

- [ ] Loading the same path twice via `AudioManager` returns handles pointing to the same `Sound` instance.
- [ ] Unloading all handles frees the sound; engine shutdown produces no warnings about unreleased resources.
- [ ] `AudioManager` is accessible via the umbrella header without additional includes.

## Sandbox Demo

- [ ] Sandbox compiles and runs; background music loops without interruption.
- [ ] One-shot sound effect plays on cue without cutting the music.
- [ ] Positional emitter movement is reflected in panning (audible or logged).
- [ ] Clean exit: no ASAN errors, no miniaudio error logs on shutdown.

## Merge Criteria

All checkboxes above are ticked. `main` is rebased cleanly. No TODOs left in new source files.
