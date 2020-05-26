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
        assert(alpha >= 0 && beta >= 0 && sigma > 0);
    }

    double RemapFunction::remapEdges(const double& delta) const
    {
        return m_beta * delta;
    }


    double RemapFunction::remapDetails(const double& delta) const
    {
        if (m_alpha > 1)
        {
            return std::pow(delta, m_alpha);
        }
        else
        {
            double tau = computeTau(delta);
            double result =  tau * pow(delta, m_alpha) + (1 - tau) * delta;
            return result;
        }
    }

    Image RemapFunction::remap(const Image& input_image, const Image& gaussian_layer) const
    {
        Image remapped_image(input_image.getWidth(), input_image.getHeight());
        for(int y = 0; y < input_image.getHeight(); y++)
        {
            for(int x = 0; x < input_image.getWidth(); x++)
            {
                Pixel remapped_pixel = remapPixel(input_image.getPixel(x, y), gaussian_layer.getPixel(x, y));
                remapped_image.setPixel(x, y, remapped_pixel);
            }
        }
        return remapped_image;
    }

    Pixel RemapFunction::remapPixel(const Pixel &pixel, const Pixel& gaussian_pixel) const
    {
        glm::vec3 i = {pixel.r / 255.0, pixel.g / 255.0, pixel.b / 255.0};
        glm::vec3 g = {gaussian_pixel.r / 255.0, gaussian_pixel.g / 255.0, gaussian_pixel.b / 255.0};
        glm::vec3 delta = i - g;
        glm::vec3 remapped_pixel;
        double delta_magnitude = glm::length(delta);
        if(delta_magnitude > 1e-10)
        {
            delta = glm::normalize(delta);
        }
        else return pixel;

        if(delta_magnitude < m_sigma)
        {
            remapped_pixel = g + delta * m_sigma * pow(remapDetails(delta_magnitude / m_sigma), m_alpha);
        }
        else
        {
            remapped_pixel = g +  delta * (remapEdges(delta_magnitude - m_sigma) + m_sigma);
        }
        return Pixel{remapped_pixel.r * 255,remapped_pixel.g * 255,remapped_pixel.b * 255, UCHAR_MAX} ;
    }


}