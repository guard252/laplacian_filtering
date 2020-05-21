#include <algorithm>

#include "GaussianPyramid.h"

namespace retouch
{
    GaussianPyramid::GaussianPyramid(const Image &image) : m_layers{image}{}

    GaussianPyramid::GaussianPyramid(Image&& first_layer):
    m_layers{first_layer}{}


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
                const size_t left_bound_x = std::max(x - KRadius, 0) * 2;
                const size_t left_bound_y = std::max(y - KRadius, 0) * 2;
                const size_t right_bound_x = std::min<unsigned>(x + KRadius, reduced_image.getWidth() - 1) * 2;
                const size_t right_bound_y = std::min<unsigned>(y + KRadius, reduced_image.getHeight() - 1) * 2;

                Pixel new_pixel{0,0,0,UCHAR_MAX};

                int num_of_neighbors = ((right_bound_x - left_bound_x) + 1) * ((right_bound_y - left_bound_y) + 1);


                for(int j = left_bound_y; j != right_bound_y; j++)
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
                const size_t left_bound_y = static_cast<unsigned>((std::max(y - KRadius, KRadius)) + 1) & ~ 1;
                const size_t right_bound_x = std::min<unsigned>(x + KRadius, expanded_image.getWidth() - 1) / 2 * 2;
                const size_t right_bound_y = std::min<unsigned>(y + KRadius, expanded_image.getHeight() - 1) / 2 * 2;
                Pixel new_pixel{0,0,0,UCHAR_MAX};

                int num_of_neighbors = ((right_bound_x - left_bound_x) / 2 + 1) * ((right_bound_y - left_bound_y) / 2 + 1);

                for(int i = left_bound_y; i <= right_bound_y; i += 2)
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

}