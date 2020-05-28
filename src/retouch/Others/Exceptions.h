#ifndef LAPLACIAN_PYRAMID_EXCEPTIONS_H
#define LAPLACIAN_PYRAMID_EXCEPTIONS_H
#include <stdexcept>

class ImageSizeTooSmallException : public std::runtime_error
{
public:
    ImageSizeTooSmallException(std::string message) : std::runtime_error(message){}
};


#endif //LAPLACIAN_PYRAMID_EXCEPTIONS_H
