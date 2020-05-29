#include <iostream>
#include "retouch/Image/ImageLoader.h"
#include "retouch/Image/ImageSaver.h"
#include "retouch/Pyramid/LaplacianPyramid.h"
#include "retouch/LaplacianFiltering/LocalLaplacianFilter.h"
#include "thread"
int main()
{
    retouch::ImageLoader loader;
    retouch::ImageSaver saver;
    retouch::LocalLaplacianFilter filter;
    const double KAlpha = 0.25;
    const double KBeta = 0.25;
    const double KSigma = 0.5;
    try
    {
        retouch::Image image(loader.loadPNG("../images/input_images/room.png"));
        retouch::Image filtered_image = filter.apply(image, KAlpha, KBeta, KSigma);
        //image.setSubImage(image.getSubImage( {0, 0}, {399, 265}), {0, 0}, {399, 265});

        std::string file_path = "../images/output_images/new_room.png";
        saver.savePNG(filtered_image, file_path);

    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what();
    }
}
