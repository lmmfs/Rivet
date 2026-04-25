#pragma once

#include <string_view>
#include "../Input.h"

namespace Rivet {

    // -----------------------------------------------------------------------
    // Event type & category
    // -----------------------------------------------------------------------

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus,
        KeyPressed, KeyReleased,
        MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
    };

    enum class EventCategory : uint32_t
    {
        None        = 0,
        Window      = 1 << 0,
        Input       = 1 << 1,
        Keyboard    = 1 << 2,
        Mouse       = 1 << 3,
        MouseButton = 1 << 4,
    };

    // -----------------------------------------------------------------------
    // Event — flat value type, no heap allocation
    // -----------------------------------------------------------------------

    struct Event
    {
        EventType type    = EventType::None;
        bool      handled = false;

        union {
            struct { int width; int height; }         windowResize;
            struct { Key key; int repeatCount; }      keyPressed;
            struct { Key key; }                       keyReleased;
            struct { float x; float y; }              mouseMoved;
            struct { float xOffset; float yOffset; }  mouseScrolled;
            struct { MouseButton button; }            mouseButton;
        };
    };

    // -----------------------------------------------------------------------
    // Debug helper
    // -----------------------------------------------------------------------

    std::string_view EventTypeToString(EventType type);

} // namespace Rivet
