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

    public:
        GaussianPyramid(const Image& first_layer);
        GaussianPyramid(Image&& first_layer);

        [[nodiscard]] const auto& getLayers() const { return m_layers; }

        // Builds all layers of the pyramid, thereby fills m_layers.
        void build();

        const Image& operator[](size_t index)const { return m_layers.at(index); }

        static Image reduce(const Image& original_image);

        static Image expand(const Image& image);
    };
}

#endif
