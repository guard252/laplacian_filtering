#include <algorithm>

#include "GaussianPyramid.h"
#include "../Image/ImageSaver.h"

namespace retouch
{
    GaussianPyramid::GaussianPyramid(const Image &image) : m_layers{image}
    {
        build();
    }

    GaussianPyramid::GaussianPyramid(Image&& first_layer):
    m_layers{first_layer}
    {
        build();
    }


    void GaussianPyramid::build()
    {
        while((m_layers.back().getHeight() + 1) / 2 > KMin_image_resolution &&
                (m_layers.back().getWidth() + 1) / 2 > KMin_image_resolution)
        {
            m_layers.push_back(reduce(m_layers.size() - 1));
        }
    }

    Image GaussianPyramid::reduce(size_t layer_index)
    {
        Image reduced_image((m_layers[layer_index].getWidth() + 1) / 2,
                            (m_layers[layer_index].getHeight() + 1) / 2,
                             m_layers[layer_index].getChannelsCount());

        constexpr int KRadius = 2;
        for(int y = 0; y < reduced_image.getHeight(); y++)
        {
            for(int x = 0; x < reduced_image.getWidth(); x++)
            {
                const size_t left_bound_x = std::max(2 * x - KRadius, 0);
                const size_t top_bound_y = std::max(2 * y - KRadius, 0);
                const size_t right_bound_x = std::min<unsigned>(2 * x + KRadius, m_layers[layer_index].getWidth() - 1);
                const size_t bottom_bound_y = std::min<unsigned>(2 * y + KRadius, m_layers[layer_index].getHeight() - 1);

                Pixel new_pixel{0,0,0,UCHAR_MAX};

                int num_of_neighbors = ((right_bound_x - left_bound_x)) * ((bottom_bound_y - top_bound_y));


                for(int j = top_bound_y; j != bottom_bound_y; j++)
                {
                    for(int i = left_bound_x; i != right_bound_x; i++)
                    {
                        new_pixel = pixelSum(new_pixel, pixelDivision(m_layers[layer_index].getPixel(i, j), num_of_neighbors));
                    }
                }

                reduced_image.setPixel(x, y, new_pixel);
            }
        }
        return reduced_image;
    }

    Image GaussianPyramid::expand(size_t layer_index)
    {
        Image expanded_image(m_layers[layer_index - 1].getWidth(),
                             m_layers[layer_index - 1].getHeight(),
                             m_layers[layer_index].getChannelsCount());

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
                        new_pixel = pixelSum(new_pixel, pixelDivision( m_layers[layer_index].getPixel(j / 2, i / 2), num_of_neighbors));
                    }
                }

                expanded_image.setPixel(x, y, new_pixel);
            }
        }
        return expanded_image;
    }

    Image GaussianPyramid::expandToLayer(size_t layer_to_expand, size_t layer_to_coincide) const
    {
        if(layer_to_expand == layer_to_coincide) return m_layers[layer_to_coincide];
        assert(layer_to_expand > layer_to_coincide &&
               layer_to_expand < m_layers.size() &&
               layer_to_coincide >= 0);

        std::vector<Image> expanded_layers{m_layers[layer_to_expand]};
        while(expanded_layers.back().getHeight() != m_layers[layer_to_coincide].getHeight())
        {
            expanded_layers.push_back(expandImageAsLayer(expanded_layers.back(), layer_to_expand--));
        }
        return expanded_layers.back();
    }

    Image GaussianPyramid::expandImageAsLayer(const Image& image, size_t layer_index) const
    {
        assert(image.getWidth() == m_layers[layer_index].getWidth() &&
        image.getHeight() == m_layers[layer_index].getHeight() &&
        image.getChannelsCount() == m_layers[layer_index].getChannelsCount());

        Image expanded_image(m_layers[layer_index - 1].getWidth(),
                             m_layers[layer_index - 1].getHeight(),
                             m_layers[layer_index - 1].getChannelsCount());

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
                        new_pixel = pixelSum(new_pixel, pixelDivision( image.getPixel(j / 2, i / 2), num_of_neighbors));
                    }
                }

                expanded_image.setPixel(x, y, new_pixel);
            }
        }
        return expanded_image;
    }

}