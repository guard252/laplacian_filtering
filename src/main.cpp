#include <iostream>
#include "retouch/Image/ImageLoader.h"
#include "retouch/Image/ImageSaver.h"
#include "retouch/Pyramid/LaplacianPyramid.h"
#include "retouch/LaplacianFiltering/LocalLaplacianFilter.h"
#include "retouch/Others/Timer.h"
int main()
{
    retouch::ImageLoader loader;
    retouch::ImageSaver saver;
    retouch::LocalLaplacianFilter filter;
    const double KAlpha = 0.25;
    const double KBeta = 0.25;
    const double KSigma = 0.5;
    Timer timer;
    try
    {
        retouch::Image image(loader.loadPNG("../images/input_images/room_new.png"));
        retouch::Image filtered_image = filter.apply(image, KAlpha, KBeta, KSigma);
        std::string file_path = "../images/output_images/room_remapped1.png";
        saver.savePNG(filtered_image, file_path);
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what();
    }

}
