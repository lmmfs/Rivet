#include "ObjLoader.h"
#include "../../Core/Logger.h"

#include <fstream>
#include <sstream>
#include <unordered_map>

namespace Rivet {

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------

struct ObjFaceVertex
{
    int pos  = -1;  // 0-based index into positions
    int uv   = -1;  // 0-based index into uvs      (-1 = absent)
    int norm = -1;  // 0-based index into normals   (-1 = absent)

    bool operator==(const ObjFaceVertex& o) const
    {
        return pos == o.pos && uv == o.uv && norm == o.norm;
    }
};

struct ObjFaceVertexHash
{
    size_t operator()(const ObjFaceVertex& v) const
    {
        size_t h = std::hash<int>{}(v.pos);
        h ^= std::hash<int>{}(v.uv)   + 0x9e3779b9u + (h << 6) + (h >> 2);
        h ^= std::hash<int>{}(v.norm) + 0x9e3779b9u + (h << 6) + (h >> 2);
        return h;
    }
};

// Convert a raw (1-based, possibly negative) OBJ index to a 0-based index.
static int ResolveObjIndex(int raw, int size)
{
    return (raw < 0) ? (size + raw) : (raw - 1);
}

// Parse a face token such as "3", "3/2", "3//1", or "3/2/1".
// Returns a zero-initialised ObjFaceVertex on parse failure.
static ObjFaceVertex ParseFaceToken(const std::string& token,
                                    int posCount, int uvCount, int normCount)
{
    ObjFaceVertex out{};

    // Find the two possible slash positions
    const size_t first  = token.find('/');
    if (first == std::string::npos)
    {
        // "p"
        out.pos = ResolveObjIndex(std::stoi(token), posCount);
        return out;
    }

    out.pos = ResolveObjIndex(std::stoi(token.substr(0, first)), posCount);

    const size_t second = token.find('/', first + 1);
    if (second == std::string::npos)
    {
        // "p/t"
        const std::string t = token.substr(first + 1);
        if (!t.empty())
            out.uv = ResolveObjIndex(std::stoi(t), uvCount);
        return out;
    }

    // "p/t/n" or "p//n"
    const std::string t = token.substr(first + 1, second - first - 1);
    const std::string n = token.substr(second + 1);
    if (!t.empty()) out.uv   = ResolveObjIndex(std::stoi(t), uvCount);
    if (!n.empty()) out.norm = ResolveObjIndex(std::stoi(n), normCount);
    return out;
}

// ---------------------------------------------------------------------------
// LoadOBJ
// ---------------------------------------------------------------------------

Mesh LoadOBJ(const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        RVT_CORE_ERROR("[ObjLoader] Cannot open: {}", path);
        return {};
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    std::vector<Vertex3D>  outVertices;
    std::vector<uint32_t>  outIndices;

    std::unordered_map<ObjFaceVertex, uint32_t, ObjFaceVertexHash> vertexCache;

    // Returns the output index for a face vertex, inserting it if new.
    auto getOrInsert = [&](const ObjFaceVertex& fv) -> uint32_t
    {
        auto it = vertexCache.find(fv);
        if (it != vertexCache.end())
            return it->second;

        Vertex3D v{};
        if (fv.pos  >= 0 && fv.pos  < static_cast<int>(positions.size()))
            v.position = positions[fv.pos];
        if (fv.uv   >= 0 && fv.uv   < static_cast<int>(uvs.size()))
            v.uv       = uvs[fv.uv];
        if (fv.norm >= 0 && fv.norm < static_cast<int>(normals.size()))
            v.normal   = normals[fv.norm];

        const uint32_t idx = static_cast<uint32_t>(outVertices.size());
        outVertices.push_back(v);
        vertexCache[fv] = idx;
        return idx;
    };

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "v")
        {
            glm::vec3 p;
            ss >> p.x >> p.y >> p.z;
            positions.push_back(p);
        }
        else if (token == "vn")
        {
            glm::vec3 n;
            ss >> n.x >> n.y >> n.z;
            normals.push_back(n);
        }
        else if (token == "vt")
        {
            glm::vec2 t;
            ss >> t.x >> t.y;
            uvs.push_back(t);
        }
        else if (token == "f")
        {
            // Collect all face vertices, then fan-triangulate
            std::vector<ObjFaceVertex> face;
            std::string elem;
            while (ss >> elem)
            {
                face.push_back(ParseFaceToken(elem,
                    static_cast<int>(positions.size()),
                    static_cast<int>(uvs.size()),
                    static_cast<int>(normals.size())));
            }

            // Fan triangulation: (0,1,2), (0,2,3), (0,3,4), …
            for (size_t i = 1; i + 1 < face.size(); ++i)
            {
                outIndices.push_back(getOrInsert(face[0]));
                outIndices.push_back(getOrInsert(face[i]));
                outIndices.push_back(getOrInsert(face[i + 1]));
            }
        }
        // Ignore: o, g, mtllib, usemtl, s — not needed in Phase 13
    }

    if (outVertices.empty())
    {
        RVT_CORE_WARN("[ObjLoader] No geometry found in: {}", path);
        return {};
    }

    RVT_CORE_INFO("[ObjLoader] Loaded '{}' — {} vertices, {} indices",
                  path, outVertices.size(), outIndices.size());

    return CreateMesh(outVertices, outIndices);
}

} // namespace Rivet
