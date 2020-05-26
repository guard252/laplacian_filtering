#include <cassert>

#include "Image.h"
#include "../Image/ImageSaver.h"

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
    void Image::setSubImage(const Image &subimage, const glm::ivec2 &start, const glm::ivec2 &end)
    {
        int KSubimage_width = end.x - start.x + 1;
        int KSubimage_height = end.y - start.y + 1;
        assert(start.x >= 0 && start.x < m_width &&
               end.x >= 0 && end.x < m_width &&
               start.y >= 0 && start.y < m_height &&
               end.y >= 0 && end.y < m_height);
        short* subimage_start = m_pixel_data.get() + (start.y * m_width + start.x) * m_channels_count;
        for(size_t i = 0; i < KSubimage_height; i++)
        {
            std::copy(subimage.m_pixel_data.get() + (i * KSubimage_width) * m_channels_count,
                      subimage.m_pixel_data.get() + (i + 1) * KSubimage_width * m_channels_count,
                      subimage_start + i * m_width * m_channels_count);

        }

    }

    Image Image::getSubImage(const glm::ivec2 &start, const glm::ivec2 &end) const
    {
        assert(start.x >= 0 && start.x < m_width &&
               end.x >= 0 && end.x < m_width &&
               start.y >= 0 && start.y < m_height &&
               end.y >= 0 && end.y < m_height);

        const int KSubimage_width = end.x - start.x + 1;
        const int KSubimage_height = end.y - start.y + 1;
        short* subimage_start = m_pixel_data.get() + (start.y * m_width + start.x) * m_channels_count;

        Image subimage(KSubimage_width, KSubimage_height, m_channels_count);
        for(size_t i = 0; i < KSubimage_height; i++)
        {
            int count = subimage_start + (i * m_width + KSubimage_width) * m_channels_count - (subimage_start + i * m_width * m_channels_count);
            std::copy(subimage_start + i * m_width * m_channels_count,
                      subimage_start + (i * m_width + KSubimage_width) * m_channels_count,
                      subimage.m_pixel_data.get() + i * KSubimage_width * m_channels_count);
        }
        return subimage;
    }

    Image Image::operator=(const Image &other)
    {
        m_pixel_data = std::move(other.getPixelDataCopy());
        m_width = other.m_width;
        m_height = other.m_height;
        m_channels_count = other.m_channels_count;
       return *this;
    }

}

