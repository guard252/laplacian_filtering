#include <algorithm>

#include "GaussianPyramid.h"

namespace retouch
{
    GaussianPyramid::GaussianPyramid(const Image &image)
    {
        m_layers.push_back(Image(image.getPixelDataCopy(),
                        image.getWidth(),
                        image.getHeight(),
                        image.getBitDepth(),
                        image.getChannelsCount()));

    }

    GaussianPyramid::GaussianPyramid(Image&& first_layer):
    m_layers{std::move(first_layer)}{};


    void GaussianPyramid::build()
    {
        
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
                Pixel new_pixel;
                std::for_each(neighbors.begin(), neighbors.end(), [&](Pixel& a){a = a / neighbors.size(); new_pixel = new_pixel + a;});
                reduced_image.setPixel(x, y, new_pixel);
            }
        }
        return reduced_image;
    }

}