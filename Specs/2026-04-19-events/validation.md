# Phase 3 — Events: Validation

## Merge Criteria

All of the following must be true before this branch is merged into `main`.

---

### 1. Build

- [ ] `cmake --build build` completes with zero errors and zero warnings on the target platform
      (Linux / Wayland).
- [ ] The precompiled header (`Rvtph.h`) is not broken by any new include.
- [ ] `Sandbox` compiles including only `<Rivet/Rivet.h>` — no extra event headers required.

---

### 2. Event Base & Type System

- [ ] `EventTypeToString` returns a non-empty string for every `EventType` variant.
- [ ] `Event` is a plain struct — `sizeof(Event)` is fixed at compile time (no heap indirection).
- [ ] `Event` default-constructs to `type == EventType::None` and `handled == false`.

---

### 3. Window Events

- [ ] Clicking the window's × button (or Alt+F4) causes a `WindowClose` event to appear in
      the queue; Sandbox logs `"Window closed"` exactly once before exiting cleanly.
- [ ] Dragging the window edge to resize causes `WindowResize` events to be logged with the
      correct new `width` and `height` values in Sandbox output.
- [ ] Clicking away from the window and back logs `WindowLostFocus` then `WindowFocus` in
      Sandbox output.

---

### 4. Key Events

- [ ] Pressing a key logs a `KeyPressed` event with the correct `Key` value.
- [ ] Holding a key past the OS repeat threshold logs subsequent `KeyPressed` events with
      `repeatCount > 0` — verified by the count incrementing in logs.
- [ ] Releasing a key logs a `KeyReleased` event with the correct `Key` value.
- [ ] No phantom key events appear when no keys are pressed.

---

### 5. Mouse Events

- [ ] Moving the cursor inside the window produces `MouseMoved` events with changing `x`/`y`
      values logged in Sandbox.
- [ ] The mouse scroll wheel produces `MouseScrolled` events with non-zero `xOffset` or
      `yOffset` logged in Sandbox.
- [ ] Clicking LMB produces `MouseButtonPressed` then `MouseButtonReleased` events with
      `button == MouseButton::Left` logged in Sandbox.
- [ ] Same verified for RMB (`MouseButton::Right`).

---

### 6. Queue Behaviour

- [ ] `PollEvent` returns `false` immediately when the queue is empty (no spin/block).
- [ ] All events pushed in a single `glfwPollEvents()` call are drained within the same
      frame's `while (PollEvent(e))` loop — no event is silently dropped.
- [ ] Setting `e.handled = true` inside the loop does not affect queue draining (handled is
      a hint only, not consumed by the queue).

---

### 7. Regression

- [ ] Phase 2 behaviour is preserved: `IsKeyDown`, `IsKeyPressed`, `IsKeyReleased`,
      `GetMousePosition()`, `GetWindowSize()` all continue to work correctly alongside the
      new event queue.
- [ ] The GLFW resize callback still updates the OpenGL viewport (no regression from
      replacing the old callback logic).
