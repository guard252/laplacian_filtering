#include <algorithm>
#include <stdexcept>
#include <memory>

#include "png.h"

#include "ImageLoader.h"
namespace retouch
{

    Image ImageLoader::loadPNG(std::string_view path) const
    {
        const size_t KChannels_count = 4;


        png_image image = {};
        image.version = PNG_IMAGE_VERSION;
        if (png_image_begin_read_from_file(&image, path.data()) == 0)
        {
            throw std::runtime_error{"Unable to read image."};
        }
        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;
        const size_t buffer_size = PNG_IMAGE_SIZE(image)/sizeof(unsigned char);
        buffer = new unsigned char[buffer_size];

        if( png_image_finish_read(&image, nullptr, buffer, 0, nullptr) == 0)
        {
            throw std::runtime_error("Unable to finish reading the image.");
        }

        short* buffer_short = new short[buffer_size];
        for(int i = 0; i < buffer_size; i++)
        {
            buffer_short[i] = buffer[i];
        }
        delete[] buffer;

        Image image_data{std::unique_ptr<short[]>(buffer_short), image.width, image.height, KChannels_count};
        png_image_free(&image);
        return image_data;
    }


}