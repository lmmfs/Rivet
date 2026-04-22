#pragma once

#include <cstdint>

namespace Rivet::Physics {

    struct BodyHandle
    {
        int32_t id = -1;
        bool IsValid() const { return id >= 0; }
    };

    enum class BodyType { Static, Dynamic };

} // namespace Rivet::Physics
