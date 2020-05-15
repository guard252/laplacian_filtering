#include <iostream>
#include "retouch/Image/ImageLoader.h"
#include "retouch/Image/ImageSaver.h"
#include "retouch/Pyramid/GaussianPyramid.h"

int main()
{
    retouch::ImageLoader loader;
    retouch::ImageSaver saver;
    try
    {
        retouch::Image data = loader.loadPNG("../images/input_images/room.png");
        retouch::Image reduced_image = retouch::GaussianPyramid::reduce(data);
        saver.savePNG(reduced_image, "../images/output_images/room_reduced.png");
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what();
    }
}
