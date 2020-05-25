#include <algorithm>

#include <glm/glm.hpp>

namespace retouch
{
    using Pixel = glm::i16vec4;

    inline Pixel pixelMultiplication(const Pixel& pixel, const double& multiplier)
    {
        return{ std::clamp(int(pixel.r * multiplier), 0, UCHAR_MAX),
                std::clamp(int(pixel.g * multiplier), 0, UCHAR_MAX),
                std::clamp(int(pixel.b * multiplier), 0, UCHAR_MAX),
                UCHAR_MAX };
    }
    inline Pixel pixelDivision(const Pixel& pixel, const double& divider)
    {
        return{ std::clamp(int(pixel.r / divider), 0, UCHAR_MAX),
                std::clamp(int(pixel.g / divider), 0, UCHAR_MAX),
                std::clamp(int(pixel.b / divider), 0, UCHAR_MAX),
                UCHAR_MAX };
    }
    inline Pixel pixelSubtraction(const Pixel& first, const Pixel& second)
    {
        return { (first.r - second.r),
                 (first.g - second.g),
                 (first.b - second.b),
                 UCHAR_MAX };
    }
    inline Pixel pixelSum(const Pixel& first, const Pixel& second)
    {
        return { std::clamp(first.r + second.r, 0, UCHAR_MAX),
                 std::clamp(first.g + second.g, 0, UCHAR_MAX),
                 std::clamp(first.b + second.b, 0, UCHAR_MAX),
                 UCHAR_MAX };
    }

    inline Pixel pixelPower(const Pixel& pixel, const double& power)
    {
        return { std::clamp<double>(std::pow(pixel.r, power), 0, UCHAR_MAX),
                 std::clamp<double>(std::pow(pixel.g, power), 0, UCHAR_MAX),
                 std::clamp<double>(std::pow(pixel.b, power), 0, UCHAR_MAX),
                 UCHAR_MAX };
    }

    inline glm::vec3 operator*(glm::vec3 vec, const double& value)
    {
        return {vec.r * value, vec.g * value, vec.b * value};
    }
    inline glm::vec3 operator/(glm::vec3 vec, const double& value)
    {
        return {vec.r / value, vec.g / value, vec.b / value};
    }
}