#ifndef LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H
#define LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H

#include <unordered_map>

#include <glm/glm.hpp>

#include "../Image/Image.h"
#include "../Others/Hashing.h"
#include "RemapFunction.h"
#include "../Pyramid/LaplacianPyramid.h"



namespace retouch
{
    class LocalLaplacianFilter
    {

        void threadExecute(const GaussianPyramid& gaussian_pyramid,
                LaplacianPyramid& output_pyramid,
                const RemapFunction remap_function,
                size_t num_of_threads, size_t current_thread) const;

    public:
        Image apply(const Image& image, const double& alpha,
                const double& beta, const double& sigma) const;

    };
}

#endif //LAPLACIAN_PYRAMID_LOCALLAPLACIANFILTER_H
