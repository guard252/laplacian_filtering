#include "LaplacianPyramid.h"

namespace retouch
{

    LaplacianPyramid::LaplacianPyramid(const Image &first_layer) : m_gaussian_pyramid(first_layer){}

    void LaplacianPyramid::build()
    {
        m_gaussian_pyramid.build();
        for(int layer = 0; layer != m_gaussian_pyramid.getLayers().size() - 1; layer++)
        {
            Image reduced_and_expanded = m_gaussian_pyramid.expand(layer + 1);;
            m_layers.push_back(m_gaussian_pyramid[layer] - reduced_and_expanded);
        }
        m_layers.push_back(m_gaussian_pyramid.getLayers().back());
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
                std::vector<Pixel> neighbors;
                for(int i = -KRadius; i <= KRadius; i++)
                {
                    for(int j = -KRadius; j <= KRadius; j++)
                    {
                        if((x - i) % 2 == 0 && (y - j) % 2 == 0 &&
                           (x - i) / 2 > 0 && (x - i) / 2 < image.getWidth() &&
                           (y - j) / 2 > 0 && (y - j) / 2 < image.getHeight())
                            neighbors.push_back(image.getPixel((x - i) / 2, (y - j) / 2));
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