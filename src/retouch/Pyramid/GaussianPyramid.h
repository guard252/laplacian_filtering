#ifndef LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#define LAPLACIAN_PYRAMID_GAUSSIANPYRAMID_H
#include <vector>
#include "../Image/Image.h"
#include "IPyramid.h"

namespace retouch
{
    class GaussianPyramid : public IPyramid
    {
        static constexpr size_t KMin_image_resolution{ 4 };

        std::vector<Image> m_layers;

    public:
        GaussianPyramid(const Image& first_layer);

        GaussianPyramid(Image&& first_layer);

        void build() override;

        [[nodiscard]] const std::vector<Image>& getLayers() const override { return m_layers; }

        [[nodiscard]] const Image& operator[](size_t index) const override { return m_layers.at(index); }

        [[nodiscard]] static Image reduce(const Image& original_image);

        [[nodiscard]] static Image expand(const Image& image);
    };
}

#endif
