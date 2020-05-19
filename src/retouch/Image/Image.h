#ifndef LAPLACIAN_PYRAMID_IMAGE_H
#define LAPLACIAN_PYRAMID_IMAGE_H

#include <cstddef>
#include <memory>

#include "Pixel.h"
namespace retouch
{
    class Image
    {
        static constexpr size_t KDefault_channels_count = 4;

        std::unique_ptr<short[]> m_pixel_data;
        size_t m_width;
        size_t m_height;
        size_t m_channels_count;
    public:
        Image(const Image& other);
        Image(Image&& other);
        Image(std::unique_ptr<short[]>&& pixel_data, size_t width, size_t height,
                size_t channels_count = KDefault_channels_count);
        //This ctor generates an image with every buffer bit set to 1
        Image(size_t width, size_t height,
              size_t channels_count = KDefault_channels_count);

        const std::unique_ptr<short[]>& getPixelData() const { return m_pixel_data; }

        size_t getWidth() const { return m_width; }

        size_t getHeight() const { return m_height; }

        size_t getChannelsCount() const { return m_channels_count; }

        std::unique_ptr<short[]> getPixelDataCopy() const;

        Image operator-(const Image& other)const;

        Image operator+(const Image& other)const;

        Pixel getPixel(size_t x, size_t y) const
        {
            assert(x < m_width && y < m_height);
            short* pixel_start = m_pixel_data.get() + (y * m_width + x) * m_channels_count;
             return {*(pixel_start),
                     *(pixel_start + 1),
                     *(pixel_start + 2),
                     *(pixel_start + 3)};
        }
        void setPixel(size_t x, size_t y, Pixel new_pixel)
        {
            assert(x < m_width && y < m_height);
            short* pixel_start = m_pixel_data.get() + (y * m_width + x) * m_channels_count;
            *(pixel_start) = new_pixel.r;
            *(pixel_start + 1) = new_pixel.g;
            *(pixel_start + 2) = new_pixel.b;
            *(pixel_start + 3) = new_pixel.a;
        }

    };

}
#endif
