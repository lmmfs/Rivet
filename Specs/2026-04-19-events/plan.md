# Phase 3 — Events: Plan

## Group 1 — Event Base & Type System

1. Define `enum class EventType` listing every event variant: `WindowClose`, `WindowResize`,
   `WindowFocus`, `WindowLostFocus`, `KeyPressed`, `KeyReleased`, `MouseMoved`, `MouseScrolled`,
   `MouseButtonPressed`, `MouseButtonReleased`.
2. Define `enum class EventCategory` as a bitmask: `None`, `Window`, `Input`, `Keyboard`,
   `Mouse`, `MouseButton`.
3. Define `struct Event` — fields: `EventType type`, `bool handled`, and a `union` (or
   subtype-specific members) holding the event payload.
4. Define payload structs / members for each event type (see Group 2 & 3 for specifics).
5. Add a `Rivet::EventTypeToString(EventType)` helper returning a `std::string_view` — used
   for debug logging throughout Sandbox.

## Group 2 — Window Events

6. Add `WindowClose` payload — no extra fields.
7. Add `WindowResize` payload — `int width`, `int height`.
8. Add `WindowFocus` / `WindowLostFocus` payloads — no extra fields.
9. Register GLFW `glfwSetWindowCloseCallback` — push a `WindowClose` event.
10. Register GLFW `glfwSetWindowSizeCallback` — push a `WindowResize` event with new dims.
11. Register GLFW `glfwSetWindowFocusCallback` — push `WindowFocus` or `WindowLostFocus`.

## Group 3 — Input Events

12. Add `KeyPressed` payload — `Key key`, `int repeatCount` (0 = first press, >0 = held repeat).
13. Add `KeyReleased` payload — `Key key`.
14. Add `MouseMoved` payload — `float x`, `float y`.
15. Add `MouseScrolled` payload — `float xOffset`, `float yOffset`.
16. Add `MouseButtonPressed` / `MouseButtonReleased` payloads — `MouseButton button`.
17. Register GLFW `glfwSetKeyCallback` — push `KeyPressed` or `KeyReleased`.
18. Register GLFW `glfwSetCursorPosCallback` — push `MouseMoved`.
19. Register GLFW `glfwSetScrollCallback` — push `MouseScrolled`.
20. Register GLFW `glfwSetMouseButtonCallback` — push `MouseButtonPressed` or `MouseButtonReleased`.

## Group 4 — Event Queue (Polling Dispatcher)

21. Define `EventQueue` as an internal module-private `std::queue<Event>`.
22. Implement `Rivet::PushEvent(Event e)` — appends to the queue (called by GLFW callbacks).
23. Implement `Rivet::PollEvent(Event& out)` — pops the front event into `out`; returns `true`
    if an event was available, `false` when the queue is empty.
24. Remove the old inline GLFW callback handling that was wired directly inside `BeginFrame`
    (`glfwPollEvents` call stays; only the direct-action callbacks are replaced with pushes).
25. Expose `PollEvent` and `PushEvent` through the umbrella header.

## Group 5 — Integration & Sandbox Demo

26. Update `Rivet::BeginFrame()` — call `glfwPollEvents()`; no further event logic (queue is
    drained by the caller).
27. Update Sandbox `Main.cpp` to drain the event queue each frame:
    ```cpp
    Rivet::Event e;
    while (Rivet::PollEvent(e)) {
        RVT_INFO("{}", Rivet::EventTypeToString(e.type));
    }
    ```
28. Log payload details for key events (`key` field) and resize events (`width`/`height`).
29. Expose `Event`, `EventType`, `EventCategory`, `Key`, `MouseButton` through `Rivet/Rivet.h`.
30. Verify the umbrella header compiles cleanly with no extra includes in `Main.cpp`.
