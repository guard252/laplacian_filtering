#ifndef LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#define LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#include <vector>
#include "../Image/Image.h"

namespace retouch
{
    class GaussianPyramid
    {
        static constexpr size_t KMin_image_resolution{ 4 };

        std::vector<Image> m_layers;

        void build();
    public:

        GaussianPyramid(const Image& first_layer);

        GaussianPyramid(Image&& first_layer);

        const std::vector<Image>& getLayers() const { return m_layers; }

        const Image& operator[](size_t index) const { return m_layers.at(index); }

    public:
        Image reduce(size_t layer_index);

        Image expand(size_t layer_index);
    };
}

#endif
