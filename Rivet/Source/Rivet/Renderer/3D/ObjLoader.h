#pragma once

#include <string>
#include "Mesh.h"

namespace Rivet {

    // Parse a Wavefront OBJ file and return a ready-to-draw Mesh.
    // Supported tokens: v, vn, vt, f (triangles and quads via fan triangulation).
    // Returns a Mesh with indexCount == 0 on failure.
    Mesh LoadOBJ(const std::string& path);

} // namespace Rivet
