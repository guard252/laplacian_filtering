#include <algorithm>
#include <stdexcept>
#include <memory>

#include "png.h"

#include "ImageLoader.h"
namespace retouch
{

    Image ImageLoader::loadPNG(std::string_view path) const
    {
        const size_t KBit_depth =  8;
        const size_t KChannels_count = 4;


        png_image image = {};
        image.version = PNG_IMAGE_VERSION;
        if (png_image_begin_read_from_file(&image, path.data()) == 0)
        {
            throw std::runtime_error{"Unable to read image."};
        }
        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;

        try
        {
            buffer = new unsigned char[PNG_IMAGE_SIZE(image)/sizeof(unsigned char)];
        }
        catch(std::bad_alloc&)
        {
            throw std::runtime_error("Not enough memory for image data allocation.");
        }

        if( png_image_finish_read(&image, nullptr, buffer, 0, nullptr) == 0)
        {
            throw std::runtime_error("Unable to finish reading the image.");
        }

        Image image_data{std::unique_ptr<unsigned char>(buffer), image.width, image.height, KBit_depth, KChannels_count};
        png_image_free(&image);
        return image_data;
    }


}