#ifndef LAPLACIAN_PYRAMID_IPYRAMID_H
#define LAPLACIAN_PYRAMID_IPYRAMID_H
#include "../Image/Image.h"

namespace retouch
{
    class IPyramid
    {
    public:
        virtual void build() = 0;

        virtual const Image &operator[](size_t index) const = 0;

        virtual const std::vector<Image>&  getLayers() const = 0;
    };
}

#endif