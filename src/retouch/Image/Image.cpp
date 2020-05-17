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
        unsigned char* pixel_buffer;
        try
        {
            pixel_buffer = new unsigned char[buffer_size];
        }
        catch(std::bad_alloc&)
        {
            throw std::runtime_error("Not enough heap memory for image allocation.");
        }
        std::fill(pixel_buffer, pixel_buffer + buffer_size, UCHAR_MAX);
        m_pixel_data.reset(pixel_buffer);
    }
    Image Image::operator-(const Image &other) const
    {
        /*
         * TODO : Implement proper way of dealing with size difference in 1 pixel
         */
        if(m_width == other.m_width + 1) other.m_width += 1;
        if(m_height == other.m_height + 1) other.m_height += 1;
        if(m_width == other.m_width - 1) other.m_width -= 1;
        if(m_height == other.m_height - 1) other.m_height -= 1;


        if(m_width != other.m_width ||
           m_height != other.m_height ||
           m_channels_count != other.m_channels_count ||
           m_bit_depth != other.m_bit_depth)
        {
            throw std::runtime_error("Properties of both images must be the same");
        }
        Image difference(m_width, m_height, m_bit_depth, m_channels_count);
        for(int x = 0; x < m_width; x++)
        {
            for(int y = 0; y < m_height; y++)
            {
                Pixel pixel_difference = pixelDifference(getPixel(x, y), other.getPixel(x, y));
                difference.setPixel(x, y, pixel_difference);
            }
        }
        return difference;
    }

}

