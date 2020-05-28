#ifndef LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#define LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#include <vector>
#include "../Image/Image.h"

namespace retouch
{
    class GaussianPyramid
    {
        static constexpr size_t KMin_image_resolution{ 2 };

        std::vector<Image> m_layers;

        void build();

        void build(int num_of_layers);
    public:

        GaussianPyramid(const Image& first_layer);

        GaussianPyramid(const Image& first_layer, size_t num_of_layers);

        GaussianPyramid(Image&& first_layer);

        GaussianPyramid(Image&& first_layer, size_t num_of_layers);

        const std::vector<Image>& getLayers() const { return m_layers; }

        const Image& operator[](size_t index) const { return m_layers.at(index); }

    public:
        Image reduce(size_t layer_index);

        Image expand(size_t layer_index);

        Image expandImageAsLayer(const Image& image, size_t layer_index)const;

        Image expandToLayer(size_t layer_to_expand, size_t layer_to_coincide)const;
    };
}

#endif
