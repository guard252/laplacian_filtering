#include <glm/glm.hpp>

namespace retouch
{
    using Pixel = glm::u8vec4;

    inline Pixel pixelMultiplication(Pixel pixel, double multiplier)
    {
        return{static_cast<unsigned char>(pixel.r * multiplier),
               static_cast<unsigned char>(pixel.g * multiplier),
               static_cast<unsigned char>(pixel.b * multiplier),
               static_cast<unsigned char>(UCHAR_MAX)};
    }
    inline Pixel pixelDivision(Pixel pixel, double divider)
    {
        return{static_cast<unsigned char>(pixel.r / divider),
               static_cast<unsigned char>(pixel.g / divider),
               static_cast<unsigned char>(pixel.b / divider),
               static_cast<unsigned char>(UCHAR_MAX)};
    }
    inline Pixel pixelDifference(Pixel first, Pixel second)
    {
        return {static_cast<unsigned char>(std::abs((int)first.r - second.r)),
                static_cast<unsigned char>(std::abs((int)first.g - second.g)),
                static_cast<unsigned char>(std::abs((int)first.b - second.b)),
                static_cast<unsigned char>(UCHAR_MAX)};
    }
    inline Pixel pixelSum(Pixel first, Pixel second)
    {
        return {static_cast<unsigned char>(first.r + second.r),
                static_cast<unsigned char>(first.g + second.g),
                static_cast<unsigned char>(first.b + second.b),
                static_cast<unsigned char>(UCHAR_MAX)};
    }
}