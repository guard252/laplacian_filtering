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

        LaplacianPyramid(const Image& image, size_t layers_count);

        // Builds an empty pyramid with layers_count layers
        LaplacianPyramid(size_t width, size_t height, size_t channels_count, size_t layers_count);

        const std::vector<Image>&  getLayers() const { return m_layers; }

        const Image& operator[](size_t index) const { return m_layers[index]; }

        void setLayerSubImage(size_t layer, const Image& img, glm::ivec2 start,glm::ivec2 end);

        void setLayer(size_t layer, const Image& image);

        Image expand(const Image& image, size_t layer_to_correspond) const;

        Image reconstructImage() const;
    };
}

#endif
