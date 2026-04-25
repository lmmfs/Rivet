#pragma once

// Forward-declare the miniaudio engine handle so consumers don't have to
// pull in the full miniaudio.h just to call Init/Shutdown.
struct ma_engine;

namespace Rivet::Audio {

    // Initialise the miniaudio engine.  Call once from Rivet::Init().
    void Init();

    // Tear down the engine.  Call once from Rivet::Shutdown(), after all
    // sounds have been unloaded.
    void Shutdown();

    // Returns the raw engine pointer (needed by Sound loading internals).
    ma_engine* GetEngine();

} // namespace Rivet::Audio
