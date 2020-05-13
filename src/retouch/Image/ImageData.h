#ifndef LAPLACIAN_PYRAMID_IMAGEDATA_H
#define LAPLACIAN_PYRAMID_IMAGEDATA_H

#include <cstddef>

namespace retouch
{
    struct ImageData
    {
        unsigned char* m_pixel_data;
        size_t m_width;
        size_t m_height;
        size_t m_bit_depth;
        size_t m_channels_count;
    };
}
#endif
