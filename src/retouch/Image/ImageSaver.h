#ifndef LAPLACIAN_PYRAMID_IMAGESAVER_H
#define LAPLACIAN_PYRAMID_IMAGESAVER_H

#include <string_view>

#include "ImageData.h"
namespace retouch
{
    class ImageSaver
    {
    public:
        void savePNG(const ImageData& image_data, std::string_view output_path)const;
    };
}

#endif
