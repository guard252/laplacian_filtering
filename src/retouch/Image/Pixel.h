#include <glm/glm.hpp>

namespace retouch
{
    using Pixel = glm::u8vec4;

    inline Pixel operator *(Pixel pixel, double multiplier)
    {
        return{static_cast<unsigned char>(pixel.r * multiplier),
               static_cast<unsigned char>(pixel.g * multiplier),
               static_cast<unsigned char>(pixel.b * multiplier),
               static_cast<unsigned char>(pixel.a * multiplier)};
    }
    inline Pixel operator /(Pixel pixel, double divider)
    {
        return{static_cast<unsigned char>(pixel.r / divider),
               static_cast<unsigned char>(pixel.g / divider),
               static_cast<unsigned char>(pixel.b / divider),
               static_cast<unsigned char>(pixel.a / divider)};
    }
}