#include <algorithm>

#include <glm/glm.hpp>

namespace retouch
{
    using Pixel = glm::i16vec4;

    inline Pixel pixelMultiplication(Pixel pixel, double multiplier)
    {
        return{std::clamp(int(pixel.r * multiplier), 0, UCHAR_MAX),
               std::clamp(int(pixel.g * multiplier), 0, UCHAR_MAX),
               std::clamp(int(pixel.b * multiplier), 0, UCHAR_MAX),
               UCHAR_MAX};
    }
    inline Pixel pixelDivision(Pixel pixel, double divider)
    {
        return{std::clamp(int(pixel.r / divider), 0, UCHAR_MAX),
               std::clamp(int(pixel.g / divider), 0, UCHAR_MAX),
               std::clamp(int(pixel.b / divider), 0, UCHAR_MAX),
               UCHAR_MAX};
    }
    inline Pixel pixelSubtraction(Pixel first, Pixel second)
    {
        return {(first.r - second.r),
                (first.g - second.g),
                (first.b - second.b),
                UCHAR_MAX};
    }
    inline Pixel pixelSum(Pixel first, Pixel second)
    {
        return {std::clamp(first.r + second.r, 0, UCHAR_MAX),
                std::clamp(first.g + second.g, 0, UCHAR_MAX),
                std::clamp(first.b + second.b, 0, UCHAR_MAX),
                UCHAR_MAX};
    }
}