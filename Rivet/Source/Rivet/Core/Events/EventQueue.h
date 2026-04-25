#pragma once

#include "Event.h"

namespace Rivet {

    // Push an event onto the internal queue.
    // Called by GLFW callbacks inside Window; not intended for direct user use.
    void PushEvent(Event e);

    // Pop the front event into `out`.
    // Returns true if an event was dequeued, false when the queue is empty.
    bool PollEvent(Event& out);

} // namespace Rivet
