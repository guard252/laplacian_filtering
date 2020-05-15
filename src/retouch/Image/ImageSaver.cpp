#include <stdexcept>
#include "png.h"

#include "ImageSaver.h"

namespace retouch
{
    void ImageSaver::savePNG(const Image& image_data, std::string_view path) const
    {
        FILE *fp;
        png_structp png_ptr;
        png_infop info_ptr;
        png_byte ** row_pointers = nullptr;

        fp = std::fopen(path.data(), "wb");
        if(fp == nullptr)
        {
            throw std::runtime_error("Unable to open file for writing.");
        }

        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,nullptr, nullptr, nullptr);
        if (png_ptr == nullptr)
        {
            std::fclose(fp);
            throw std::runtime_error("Unable to initialize pnd_struct.");
        }

        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == nullptr)
        {
            std::fclose(fp);
            png_destroy_write_struct(&png_ptr,  nullptr);
            throw std::runtime_error("Unable to initialize the image info data.");
        }

        if (setjmp(png_jmpbuf(png_ptr)))
        {
            fclose(fp);
            png_destroy_write_struct(&png_ptr, &info_ptr);
            throw std::runtime_error("Unable to write to file.");
        }


        png_set_IHDR(png_ptr,
                info_ptr,
                image_data.getWidth(),
                image_data.getHeight(),
                image_data.getBitDepth(),
                PNG_COLOR_TYPE_RGBA,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_DEFAULT,
                PNG_FILTER_TYPE_DEFAULT);

        row_pointers = (png_byte**)png_malloc (png_ptr, image_data.getHeight() * sizeof (png_byte*));
        for (int y = 0; y < image_data.getHeight(); y++) {
            png_byte* row = (png_byte *)png_malloc(png_ptr, sizeof (uint8_t) * image_data.getWidth() * image_data.getChannelsCount());
            row_pointers[y] = row;
            for (int x = 0; x < image_data.getWidth(); x++) {
                unsigned char* position = image_data.getPixelData().get() + (image_data.getWidth() * y + x) * image_data.getChannelsCount();
                row[x * image_data.getChannelsCount()] =     *position;
                row[x * image_data.getChannelsCount() + 1] = *(position + 1);
                row[x * image_data.getChannelsCount() + 2] = *(position + 2);
                row[x * image_data.getChannelsCount() + 3] = *(position + 3);
            }
        }
        png_init_io(png_ptr, fp);
        png_set_rows (png_ptr, info_ptr, row_pointers);
        png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

        for (int y = 0; y < image_data.getHeight(); y++) {
            png_free (png_ptr, row_pointers[y]);
        }
        png_free (png_ptr, row_pointers);
        png_write_end(png_ptr, info_ptr);
    }
}