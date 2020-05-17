#include <algorithm>

#include "GaussianPyramid.h"

namespace retouch
{
    GaussianPyramid::GaussianPyramid(const Image &image) : m_layers{image}{}

    GaussianPyramid::GaussianPyramid(Image&& first_layer):
    m_layers{first_layer}{}


    void GaussianPyramid::build()
    {
        while(m_layers.back().getHeight() / 2 > KMin_image_resolution &&
        m_layers.back().getWidth() / 2> KMin_image_resolution)
        {
            m_layers.push_back(reduce(m_layers.back()));
        }
    }

    Image retouch::GaussianPyramid::reduce(const retouch::Image &original_image)
    {
        Image reduced_image(original_image.getWidth() / 2,
                            original_image.getHeight() / 2,
                            original_image.getBitDepth(),
                            original_image.getChannelsCount());

        constexpr int KRadius = 2;
        for(int x = 0; x < reduced_image.getWidth(); x++)
        {
            for(int y = 0; y < reduced_image.getHeight(); y++)
            {
                std::vector<Pixel> neighbors;
                for(int x_axis_neighbor = 2 * x - KRadius; x_axis_neighbor != 2 * x + KRadius; x_axis_neighbor++)
                {
                    for(int y_axis_neighbor = 2 * y - KRadius; y_axis_neighbor != 2 * y + KRadius; y_axis_neighbor++)
                    {
                        if(x_axis_neighbor >= 0 && x_axis_neighbor < original_image.getWidth() &&
                        y_axis_neighbor >= 0 && y_axis_neighbor < original_image.getHeight())
                        {
                            neighbors.push_back(original_image.getPixel(x_axis_neighbor, y_axis_neighbor));
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

    Image retouch::GaussianPyramid::expand(const retouch::Image &original_image)
    {
        Image expanded_image(original_image.getWidth() * 2,
                            original_image.getHeight() * 2,
                            original_image.getBitDepth(),
                            original_image.getChannelsCount());

        constexpr int KRadius = 2;
        for(int x = 0; x < expanded_image.getWidth(); x++)
        {
            for (int y = 0; y < expanded_image.getHeight(); y++)
            {
                std::vector<Pixel> neighbors;
                for(int i = -KRadius; i <= KRadius; i++)
                {
                    for(int j = -KRadius; j <= KRadius; j++)
                    {
                        if((x - i) % 2 == 0 && (y - j) % 2 == 0 &&
                                (x - i) / 2 > 0 && (x - i) / 2 < original_image.getWidth() &&
                                (y - j) / 2 > 0 && (y - j) / 2 < original_image.getHeight())
                        neighbors.push_back(original_image.getPixel((x - i) / 2, (y - j) / 2));
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