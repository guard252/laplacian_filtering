#ifndef LAPLACIAN_PYRAMID_LAPLACIANPYRAMID_H
#define LAPLACIAN_PYRAMID_LAPLACIANPYRAMID_H

#include "GaussianPyramid.h"

namespace retouch
{
    class LaplacianPyramid : IPyramid
    {
        GaussianPyramid m_gaussian_pyramid;

        std::vector<Image> m_layers;
    public:
        LaplacianPyramid(const Image& first_layer);

        void build() override;

        const std::vector<Image>&  getLayers() const override { return m_layers; }

        const Image& operator[](size_t index) const override { return m_layers.at(index); }

    };
}

#endif
