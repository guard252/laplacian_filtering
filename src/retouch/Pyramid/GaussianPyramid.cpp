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

    Image GaussianPyramid::reduce(size_t layer)
    {
        Image reduced_image((m_layers[layer].getWidth() + 1) / 2,
                            (m_layers[layer].getHeight() + 1) / 2,
                            m_layers[layer].getChannelsCount());

        constexpr int KRadius = 2;
        for(int y = 0; y < reduced_image.getHeight(); y++)
        {
            for(int x = 0; x < reduced_image.getWidth(); x++)
            {
                std::vector<Pixel> neighbors;
                for(int x_axis_neighbor = 2 * x - KRadius; x_axis_neighbor != 2 * x + KRadius; x_axis_neighbor++)
                {
                    for(int y_axis_neighbor = 2 * y - KRadius; y_axis_neighbor != 2 * y + KRadius; y_axis_neighbor++)
                    {
                        if(x_axis_neighbor >= 0 && x_axis_neighbor < m_layers[layer].getWidth() &&
                        y_axis_neighbor >= 0 && y_axis_neighbor < m_layers[layer].getHeight())
                        {
                            neighbors.push_back(m_layers[layer].getPixel(x_axis_neighbor, y_axis_neighbor));
                        }
                    }
                }
                Pixel new_pixel{0,0,0,0};
                std::for_each(neighbors.begin(), neighbors.end(), [&](Pixel& a){a = pixelDivision(a, neighbors.size());
                new_pixel = pixelSum(new_pixel, a);});
                reduced_image.setPixel(x, y, new_pixel);
            }
        }
        return reduced_image;
    }

    Image GaussianPyramid::expand(size_t layer)
    {
        Image expanded_image(m_layers[layer - 1].getWidth(),
                             m_layers[layer - 1].getHeight(),
                             m_layers[layer].getChannelsCount());

        constexpr int KRadius = 2;
        for(int y = 0; y < expanded_image.getHeight(); y++)
        {
            for (int x = 0; x < expanded_image.getWidth(); x++)
            {
                std::vector<Pixel> neighbors;
                for(int i = -KRadius; i <= KRadius; i++)
                {
                    for(int j = -KRadius; j <= KRadius; j++)
                    {
                        if((x - i) % 2 == 0 && (y - j) % 2 == 0 &&
                                (x - i) / 2 > 0 && (x - i) / 2 < m_layers[layer].getWidth() &&
                                (y - j) / 2 > 0 && (y - j) / 2 < m_layers[layer].getHeight())
                        neighbors.push_back(m_layers[layer].getPixel((x - i) / 2, (y - j) / 2));
                    }
                }
                Pixel new_pixel{0,0,0,UCHAR_MAX};
                std::for_each(neighbors.begin(), neighbors.end(), [&](Pixel& a){
                    a = pixelDivision(a, neighbors.size());
                    new_pixel = pixelSum(new_pixel, a);
                });
                expanded_image.setPixel(x, y, new_pixel);
            }
        }
        return expanded_image;
    }

}