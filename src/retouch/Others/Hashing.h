#ifndef LAPLACIAN_PYRAMID_HASHING_H
#define LAPLACIAN_PYRAMID_HASHING_H
#include <memory>

#include <glm/glm.hpp>

namespace retouch
{
    struct Ivec2Hashing
    {
        size_t operator()(const glm::ivec2 &k) const
        {
            return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
        }

        bool operator()(const glm::ivec2 &a, const glm::ivec2 &b) const
        {
            return a.x == b.x && a.y == b.y;
        }
    };
}
#endif
