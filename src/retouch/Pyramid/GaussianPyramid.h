#ifndef LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#define LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#include <vector>
#include "../Image/Image.h"

namespace retouch
{
    class GaussianPyramid
    {
        std::vector<Image> m_layers;

        void build();

        void build(int num_of_layers);

        static size_t getLayerSize(size_t width_or_height, size_t layer);

    public:
        static constexpr size_t KMin_image_resolution{ 2 };

        GaussianPyramid(const Image& first_layer);

        GaussianPyramid(const Image& first_layer, size_t num_of_layers);

        GaussianPyramid(Image&& first_layer);

        GaussianPyramid(Image&& first_layer, size_t num_of_layers);

        const std::vector<Image>& getLayers() const { return m_layers; }

        const Image& operator[](size_t index) const { return m_layers.at(index); }

        Image reduce(size_t layer_index);

        Image expand(size_t layer_index);

        static Image getGaussianLayer(const Image& image, size_t layer);

    };
}

#endif
