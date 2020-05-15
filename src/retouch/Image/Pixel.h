#ifndef LAPLACIAN_PYRAMID_PIXEL_H
#define LAPLACIAN_PYRAMID_PIXEL_H

struct Pixel
{
    unsigned char m_red{0};
    unsigned char m_green{0};
    unsigned char m_blue{0};
    unsigned char m_alpha{1};
    Pixel operator-(const Pixel& other)
    {
        return Pixel{static_cast<unsigned char>(m_red - other.m_red),
                     static_cast<unsigned char>(m_green - other.m_green),
                     static_cast<unsigned char>(m_blue - other.m_blue),
                     static_cast<unsigned char>(m_alpha - other.m_alpha)};
    }
    Pixel operator+(const Pixel& other)
    {
        return Pixel{static_cast<unsigned char>(m_red + other.m_red),
                     static_cast<unsigned char>(m_green + other.m_green),
                     static_cast<unsigned char>(m_blue + other.m_blue),
                     static_cast<unsigned char>(std::max(m_alpha, other.m_alpha))};
    }
    Pixel operator/(const double& divider)
    {
        return Pixel{static_cast<unsigned char>(m_red / divider),
                     static_cast<unsigned char>(m_green / divider),
                     static_cast<unsigned char>(m_blue / divider),
                     static_cast<unsigned char>(m_alpha)};
    }
};
#endif
