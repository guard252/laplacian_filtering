#include "LaplacianPyramid.h"

namespace retouch
{

    LaplacianPyramid::LaplacianPyramid(const Image &first_layer)
    {
        build(first_layer);
    }

    LaplacianPyramid::LaplacianPyramid(const Image& image, size_t layers_count)
    {
        size_t width = image.getWidth();
        size_t height = image.getHeight();
        for(int layer = 0; layer != layers_count; layer++)
        {
            m_layers.push_back(Image(width, height, image.getChannelsCount()));
            width = (width + 1) / 2;
            height = (height + 1) / 2;
        }
    }

    void LaplacianPyramid::build(const Image& image)
    {
        GaussianPyramid gaussian_pyramid(image);
        for(int layer = 0; layer != gaussian_pyramid.getLayers().size() - 1; layer++)
        {
            Image reduced_and_expanded = gaussian_pyramid.expand(layer + 1);;
            m_layers.push_back(gaussian_pyramid[layer] - reduced_and_expanded);
        }
        m_layers.push_back(gaussian_pyramid.getLayers().back());
    }

    Image LaplacianPyramid::reconstructImage() const
    {
        std::vector<Image> reconstructed_particles{m_layers.back()};
        for(int i = m_layers.size() - 2; i >= 0; i--)
        {
            reconstructed_particles.push_back(expand(reconstructed_particles.back(), i) + m_layers[i]);
        }
        return reconstructed_particles.back();
    }


    Image LaplacianPyramid::expand(const Image& image, size_t layer_to_correspond) const
    {
//        assert(m_layers[layer_to_correspond].getWidth() / 2 + 1 == image.getWidth() &&
//        m_layers[layer_to_correspond].getHeight() / 2 + 1 == image.getHeight());

        Image expanded_image(m_layers[layer_to_correspond].getWidth(),
                             m_layers[layer_to_correspond].getHeight(),
                             m_layers[layer_to_correspond].getChannelsCount());

        constexpr int KRadius = 2;
        for(int y = 0; y < expanded_image.getHeight(); y++)
        {
            for (int x = 0; x < expanded_image.getWidth(); x++)
            {
                const size_t left_bound_x = static_cast<unsigned>((std::max(x - KRadius, KRadius)) + 1) & ~ 1;
                const size_t top_bound_y = static_cast<unsigned>((std::max(y - KRadius, KRadius)) + 1) & ~ 1;
                const size_t right_bound_x = std::min<unsigned>(x + KRadius, expanded_image.getWidth() - 1) / 2 * 2;
                const size_t bottom_bound_y = std::min<unsigned>(y + KRadius, expanded_image.getHeight() - 1) / 2 * 2;
                Pixel new_pixel{0,0,0,UCHAR_MAX};

                int num_of_neighbors = ((right_bound_x - left_bound_x) / 2 + 1) * ((bottom_bound_y - top_bound_y) / 2 + 1);

                for(int i = top_bound_y; i <= bottom_bound_y; i += 2)
                {
                    for(int j = left_bound_x; j <= right_bound_x; j += 2)
                    {
                        new_pixel = pixelSum(new_pixel, pixelDivision(image.getPixel(j / 2, i / 2), num_of_neighbors));
                    }
                }

                expanded_image.setPixel(x, y, new_pixel);
            }
        }
        return expanded_image;
    }


}