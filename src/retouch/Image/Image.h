#ifndef LAPLACIAN_PYRAMID_IMAGE_H
#define LAPLACIAN_PYRAMID_IMAGE_H

#include <cstddef>
#include <memory>

#include "Pixel.h"
namespace retouch
{
    class Image
    {
        static constexpr size_t KDefault_bit_depth = 8;
        static constexpr size_t KDefault_channels_count = 4;

        std::unique_ptr<unsigned char> m_pixel_data;
        size_t m_width;
        size_t m_height;
        size_t m_bit_depth;
        size_t m_channels_count;
    public:
        Image(const Image& other);
        Image(Image&& other);
        Image(std::unique_ptr<unsigned char>&& pixel_data, size_t width, size_t height,
                size_t bit_depth = KDefault_bit_depth,
                size_t channels_count = KDefault_channels_count);

        //This ctor generates an image with every buffer bit set to 0
        Image(size_t width, size_t height,
              size_t bit_depth = KDefault_bit_depth,
              size_t channels_count = KDefault_channels_count);

        [[nodiscard]] const auto& getPixelData() const { return m_pixel_data; }
        [[nodiscard]] size_t getWidth() const { return m_width; }
        [[nodiscard]] size_t getHeight() const { return m_height; }
        [[nodiscard]] size_t getBitDepth() const { return m_bit_depth; }
        [[nodiscard]] size_t getChannelsCount() const { return m_channels_count; }

        std::unique_ptr<unsigned char> getPixelDataCopy() const;

        Pixel getPixel(size_t x, size_t y) const
        {
                if(x >= m_width || y >= m_height) throw std::out_of_range("Index out of bounds of image data.");
                unsigned char* pixel_start = m_pixel_data.get() + (y * m_width + x) * m_channels_count;
                return Pixel{*(pixel_start),
                             *(pixel_start + 1),
                             *(pixel_start + 2),
                             *(pixel_start + 3)};
        }
        void setPixel(size_t x, size_t y, Pixel new_pixel)
        {
            if(x >= m_width || y >= m_height) throw std::out_of_range("Index out of bounds of image data.");
            unsigned char* pixel_start = m_pixel_data.get() + (y * m_width + x) * m_channels_count;
            *(pixel_start) = new_pixel.m_red;
            *(pixel_start + 1) = new_pixel.m_green;
            *(pixel_start + 2) = new_pixel.m_blue;
            *(pixel_start + 3) = new_pixel.m_alpha;
        }

    };
}
#endif
