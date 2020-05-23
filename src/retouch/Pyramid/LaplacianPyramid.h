#ifndef LAPLACIAN_PYRAMID_LAPLACIANPYRAMID_H
#define LAPLACIAN_PYRAMID_LAPLACIANPYRAMID_H

#include "GaussianPyramid.h"

namespace retouch
{
    class LaplacianPyramid
    {

        std::vector<Image> m_layers;
    private:
        void build(const Image& image);
    public:

        LaplacianPyramid(const Image& first_layer);

        // Builds an empty pyramid with layers_count layers
        LaplacianPyramid(const Image& image, size_t layers_count);

        const std::vector<Image>&  getLayers() const { return m_layers; }

        const Image& operator[](size_t index) const { return m_layers.at(index); }

        Image expand(const Image& image, size_t layer_to_correspond) const;

        Image reconstructImage() const;
    };
}

#endif
