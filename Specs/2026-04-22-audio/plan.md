# Phase 10 — Audio: Plan

## Task Group 1 — Integrate miniaudio

1.1 Add miniaudio as a vendored single-header in `Rivet/Vendor/miniaudio/` (download `miniaudio.h`).  
1.2 Create `miniaudio.cpp` that defines `MINIAUDIO_IMPLEMENTATION` (one-translation-unit rule).  
1.3 Wire into `Rivet/CMakeLists.txt` — add the impl source and include path.  
1.4 Verify the project compiles with miniaudio included (no Sandbox changes yet).

## Task Group 2 — Audio Engine Init / Shutdown

2.1 Create `Rivet/Source/Rivet/Audio/AudioEngine.h` — declare `Init()`, `Shutdown()`, and internal `ma_engine` handle.  
2.2 Implement `AudioEngine.cpp` — `ma_engine_init`, `ma_engine_uninit`.  
2.3 Call `AudioEngine::Init()` / `Shutdown()` from the application lifecycle (alongside Window init/shutdown).  
2.4 Log engine start/stop via spdlog.

## Task Group 3 — Sound Loading

3.1 Define `Sound` resource wrapper (holds `ma_sound`).  
3.2 Implement `Sound::Load(const std::string& path)` using `ma_sound_init_from_file`.  
3.3 Implement `Sound::Unload()` using `ma_sound_uninit`.  
3.4 Support WAV and OGG (both decoded natively by miniaudio).

## Task Group 4 — Playback Controls

4.1 Free functions in `rvt::audio` namespace:  
  - `Play(Sound&)`  
  - `Stop(Sound&)`  
  - `Pause(Sound&)`  
  - `Resume(Sound&)`  
  - `SetLoop(Sound&, bool)`  
  - `SetVolume(Sound&, float)` (0.0–1.0)  
4.2 Implement each by delegating to the corresponding `ma_sound_*` call.  
4.3 Expose convenience query: `IsPlaying(const Sound&) -> bool`.

## Task Group 5 — 2D Positional Audio

5.1 Enable miniaudio's spatialization engine (already on by default with `ma_engine`).  
5.2 Add `SetPosition(Sound&, float x, float y)` — maps to `ma_sound_set_position` with z=0.  
5.3 Add `SetListenerPosition(float x, float y)` — maps to `ma_engine_listener_set_position`.  
5.4 Set reasonable default attenuation model (`MA_ATTENUATION_MODEL_LINEAR`) and max distance.  
5.5 Document coordinate system (matches world-space units used by the 2D camera).

## Task Group 6 — Asset Manager Integration

6.1 Create `AudioManager` following the same `ResourceHandle<Sound>` pattern as `TextureManager`.  
6.2 `AudioManager::Load(const std::string& path) -> ResourceHandle<Sound>` — loads once, returns shared handle.  
6.3 `AudioManager::Unload(ResourceHandle<Sound>)` — decrements ref count, uninits `ma_sound` when zero.  
6.4 Add `AudioManager` instance to the existing `AssetManager` (or register alongside it).  
6.5 Expose through umbrella header `Rivet/Rivet.h`.

## Task Group 7 — Sandbox Demo

7.1 Load a WAV and an OGG sample file into `Sandbox/assets/audio/`.  
7.2 In `Main.cpp` demonstrate:  
  - Load both files via `AudioManager`.  
  - Play, loop the background track, one-shot the effect.  
  - Set volume independently.  
  - Move a positional emitter each frame and print its pan value to verify spatialization.  
7.3 Confirm no memory leaks on shutdown (all sounds unloaded before `AudioEngine::Shutdown()`).
