#include "Image.h"

namespace retouch
{

    Image::Image(std::unique_ptr<unsigned char> &&pixel_data, size_t width, size_t height, size_t bit_depth,
                 size_t channels_count) :
                 m_pixel_data(std::move(pixel_data)),
                 m_width{width},
                 m_height{height},
                 m_bit_depth{bit_depth},
                 m_channels_count{channels_count}{}

    std::unique_ptr<unsigned char> Image::getPixelDataCopy() const
    {
        unsigned char* image_buffer = nullptr;
        try
        {
            image_buffer = new unsigned char[m_height * m_width * m_channels_count];
        }
        catch(std::bad_alloc&)
        {
            throw std::runtime_error("Unable to allocate memory for the image buffer.");
        }
        std::copy(m_pixel_data.get(),
                  m_pixel_data.get() + m_height * m_width * m_channels_count,
                  image_buffer);

        return std::unique_ptr<unsigned char>(image_buffer);
    }

    Image::Image(Image &&other) :
            m_pixel_data(std::move(other.m_pixel_data)),
            m_width{other.m_width},
            m_height{other.m_height},
            m_bit_depth{other.m_bit_depth},
            m_channels_count{other.m_channels_count}{}

    Image::Image(const Image &other) :
            m_pixel_data(other.getPixelDataCopy()),
            m_width{other.m_width},
            m_height{other.m_height},
            m_bit_depth{other.m_bit_depth},
            m_channels_count{other.m_channels_count}{}

    Image::Image(size_t width, size_t height, size_t bit_depth, size_t channels_count):
            m_width{width},
            m_height{height},
            m_bit_depth{bit_depth},
            m_channels_count{channels_count}
    {
        size_t buffer_size = m_width * m_height * m_bit_depth;
        unsigned char* pixel_buffer = new unsigned char[buffer_size];
        std::fill(pixel_buffer, pixel_buffer + buffer_size, 0);
        m_pixel_data.reset(pixel_buffer);
    }

}

