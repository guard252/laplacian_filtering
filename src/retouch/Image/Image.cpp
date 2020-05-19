#include <cassert>

#include "Image.h"

namespace retouch
{

    Image::Image(std::unique_ptr<short[]> &&pixel_data, size_t width, size_t height, size_t channels_count) :
                 m_pixel_data(std::move(pixel_data)),
                 m_width{width},
                 m_height{height},
                 m_channels_count{channels_count}{}

    std::unique_ptr<short[]> Image::getPixelDataCopy() const
    {
        short* image_buffer = new short[m_height * m_width * m_channels_count];
        std::copy(m_pixel_data.get(),
                  m_pixel_data.get() + m_height * m_width * m_channels_count,
                  image_buffer);
        return std::unique_ptr<short[]>(image_buffer);
    }

    Image::Image(Image &&other) :
            m_pixel_data(std::move(other.m_pixel_data)),
            m_width{other.m_width},
            m_height{other.m_height},
            m_channels_count{other.m_channels_count}{}

    Image::Image(const Image &other) :
            m_pixel_data(other.getPixelDataCopy()),
            m_width{other.m_width},
            m_height{other.m_height},
            m_channels_count{other.m_channels_count}{}

    Image::Image(size_t width, size_t height,size_t channels_count):
            m_width{width},
            m_height{height},
            m_channels_count{channels_count}
    {
        size_t buffer_size = m_width * m_height * m_channels_count;
        short* pixel_buffer = new short[buffer_size];
        std::fill(pixel_buffer, pixel_buffer + buffer_size, UCHAR_MAX);
        m_pixel_data.reset(pixel_buffer);
    }

    Image Image::operator-(const Image &other) const
    {
        assert(m_width == other.m_width &&
           m_height == other.m_height &&
           m_channels_count == other.m_channels_count);

        Image difference(m_width, m_height, m_channels_count);
        for(int y = 0; y < m_height; y++)
        {
            for(int x = 0; x < m_width; x++)
            {
                Pixel pixel_difference = pixelSubtraction(getPixel(x, y), other.getPixel(x, y));
                difference.setPixel(x, y, pixel_difference);
            }
        }
        return difference;
    }

    Image Image::operator+(const Image &other) const
    {
        assert(m_width == other.m_width &&
               m_height == other.m_height &&
               m_channels_count == other.m_channels_count);

        Image sum(m_width, m_height, m_channels_count);
        for(int y = 0; y < m_height; y++)
        {
            for(int x = 0; x < m_width; x++)
            {
                Pixel pixel_sum = pixelSum(getPixel(x, y), other.getPixel(x, y));
                sum.setPixel(x, y, pixel_sum);
            }
        }
        return sum;
    }

}

