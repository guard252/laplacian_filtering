#include "RemapFunction.h"

namespace retouch
{

    double RemapFunction::computeTau(const double& delta) const
    {
        constexpr double zero_upper_bound = 0.01;
        constexpr double one_lower_bound = 2 * zero_upper_bound;

        if(delta < zero_upper_bound) return 0;
        if(delta > one_lower_bound) return 1;
        return (delta - zero_upper_bound) / (one_lower_bound - zero_upper_bound);
    }


    RemapFunction::RemapFunction(const double &alpha, const double &beta, const double &sigma):
    m_alpha{alpha}, m_beta{beta}, m_sigma{sigma}
    {
        assert(alpha > 0);
        if (m_alpha > 1)
        {
            m_remapDetailsFunction = [this](const double& delta) {
                return std::pow(delta, m_alpha);
            };
        }
        else if(m_alpha < 1)
        {
            m_remapDetailsFunction = [this](const double& delta) {
                double tau = computeTau(delta);
                return tau * pow(delta, m_alpha) + (1 - tau) * m_sigma;
            };
        }
    }

    double RemapFunction::remapEdges(const double& delta) const
    {
        return m_beta * delta;
    }


    double RemapFunction::remapDetails(const double& delta) const
    {
        return m_remapDetailsFunction(delta);
    }

    Image RemapFunction::remap(const Image& input_image, const Image& gaussian_layer) const
    {
        Image remapped_image(input_image);
        for(int y = 0; y < input_image.getHeight(); y++)
        {
            for(int x = 0; x < input_image.getWidth(); x++)
            {
                Pixel remapped_pixel = remapPixel(input_image.getPixel(x, y), gaussian_layer.getPixel(x, y));
                remapped_image.setPixel(x, y, remapped_pixel);
            }
        }
    }

    Pixel RemapFunction::remapPixel(const Pixel &pixel, const Pixel& gaussian_pixel) const
    {
        Pixel remapped_pixel;
        Pixel delta = pixel - gaussian_pixel;
        if(pixel != gaussian_pixel)
        {
            delta = glm::normalize(delta);
        }

        if(delta.length() < m_sigma)
        {
            remapped_pixel = gaussian_pixel + pixelMultiplication(pixelMultiplication(delta, m_sigma),
                    remapDetails(delta.length() / m_sigma));
        }
        else
        {
            remapped_pixel = gaussian_pixel + pixelMultiplication(delta, remapEdges(delta.length() - m_sigma) + m_sigma);
        }
        return remapped_pixel;
    }
}