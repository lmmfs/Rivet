#include "EventQueue.h"

#include <queue>

namespace {

    std::queue<Rivet::Event> s_Queue;

} // namespace

namespace Rivet {

    void PushEvent(Event e)
    {
        s_Queue.push(e);
    }

    bool PollEvent(Event& out)
    {
        if (s_Queue.empty())
            return false;

        out = s_Queue.front();
        s_Queue.pop();
        return true;
    }

    std::string_view EventTypeToString(EventType type)
    {
        switch (type)
        {
            case EventType::None:               return "None";
            case EventType::WindowClose:        return "WindowClose";
            case EventType::WindowResize:       return "WindowResize";
            case EventType::WindowFocus:        return "WindowFocus";
            case EventType::WindowLostFocus:    return "WindowLostFocus";
            case EventType::KeyPressed:         return "KeyPressed";
            case EventType::KeyReleased:        return "KeyReleased";
            case EventType::MouseMoved:         return "MouseMoved";
            case EventType::MouseScrolled:      return "MouseScrolled";
            case EventType::MouseButtonPressed: return "MouseButtonPressed";
            case EventType::MouseButtonReleased:return "MouseButtonReleased";
        }
        return "Unknown";
    }

} // namespace Rivet
