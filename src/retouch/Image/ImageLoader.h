#ifndef LAPLACIAN_PYRAMID_IMAGELOADER_H
#define LAPLACIAN_PYRAMID_IMAGELOADER_H

#include <string>
#include <string_view>
#include "Image.h"
namespace retouch
{
    class ImageLoader
    {
    public:
        Image loadPNG(std::string_view input_path)const;
    };
}

#endif
