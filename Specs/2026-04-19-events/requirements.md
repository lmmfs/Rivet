# Phase 3 — Events: Requirements

## Scope

Introduce a lightweight event system that surfaces GLFW callbacks as typed `Event` values
available to user code via a polling queue. This is the first consumer-visible event API;
it must remain simple, data-oriented, and free of heap allocation in the hot path.

### In scope
- `Event` struct with `EventType` enum and per-type payload (union or flat struct fields)
- `EventCategory` bitmask for coarse filtering
- Window events: close, resize, focus gained, focus lost
- Input events: key pressed/released (with repeat count), mouse moved, mouse scrolled,
  mouse button pressed/released
- `EventQueue` — module-private, drained by `Rivet::PollEvent(Event&)` each frame
- `EventTypeToString()` helper for debug logging
- Full exposure through `Rivet/Rivet.h`

### Out of scope
- Thread-safe / concurrent event queue
- Event priorities or filtering hooks
- Text / character input events (deferred — require Unicode handling)
- Touch or gamepad events
- User-defined / custom event types
- Event replay or recording

---

## API Style Decisions

**Polling queue — SDL-style**  
GLFW callbacks push `Event` values onto an internal queue. Each frame the caller drains the
queue by calling `PollEvent` in a loop. No callbacks or virtual dispatch are exposed to the
user; the API is a simple value-type drain.

```cpp
// Intended usage
Rivet::Event e;
while (Rivet::PollEvent(e)) {
    switch (e.type) {
        case Rivet::EventType::WindowClose:
            RVT_INFO("Window closed");
            break;
        case Rivet::EventType::KeyPressed:
            RVT_INFO("Key pressed: {}", static_cast<int>(e.key.key));
            break;
        case Rivet::EventType::WindowResize:
            RVT_INFO("Resize: {}x{}", e.windowResize.width, e.windowResize.height);
            break;
        default: break;
    }
}
```

**Event as a flat value type**  
`Event` is a plain struct — no vtable, no heap allocation. The payload is stored inline
(e.g. via a union or named members per type). This keeps event storage and copying cheap.

```cpp
struct Event {
    EventType     type     = EventType::None;
    bool          handled  = false;

    union {
        struct { int width; int height; } windowResize;
        struct { Key key; int repeatCount; } keyPressed;
        struct { Key key; }                 keyReleased;
        struct { float x; float y; }       mouseMoved;
        struct { float xOffset; float yOffset; } mouseScrolled;
        struct { MouseButton button; }     mouseButton;
    };
};
```

**GLFW callbacks push; BeginFrame does not consume**  
`Rivet::BeginFrame()` calls `glfwPollEvents()` which fires the GLFW callbacks; those
callbacks push to the queue. `BeginFrame` itself does not drain the queue — the user does
that explicitly after `BeginFrame` returns.

**No `EventDispatcher` class**  
A dispatcher object is unnecessary given the polling model. `PollEvent` is the dispatcher.
If per-type handling helpers are needed later they can be free functions.

---

## Key & MouseButton Reuse

`EventType::KeyPressed` and `EventType::KeyReleased` reuse the `Key` enum defined in Phase 2.  
`EventType::MouseButtonPressed` and `EventType::MouseButtonReleased` reuse `MouseButton`.  
No new enums are introduced for these; the payload structs reference the existing types.

---

## Naming Conventions

Follows the existing Rivet pattern: everything in `namespace Rivet`, PascalCase types,
free functions with a `Rivet::` prefix. Files live under `Rivet/Source/Rivet/`.
