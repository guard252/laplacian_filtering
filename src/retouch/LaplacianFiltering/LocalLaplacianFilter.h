#ifndef LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H
#define LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H

#include <unordered_map>

#include <glm/glm.hpp>

#include "../Image/Image.h"
#include "../Others/Hashing.h"

namespace retouch
{
    class LocalLaplacianFilter
    {

        std::unordered_map<glm::ivec2, Image, Ivec2Hashing, Ivec2Hashing>
                divideIntoSubimages(const Image& image, size_t count_on_axis) const;


    public:
        Image apply(const Image& image, const double& alpha,
                const double& beta, const double& sigma) const;

    };
}

#endif //LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H
