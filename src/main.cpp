#include <iostream>
#include "retouch/Image/ImageLoader.h"
#include "retouch/Image/ImageSaver.h"
#include "retouch/Pyramid/LaplacianPyramid.h"

int main()
{
    retouch::ImageLoader loader;
    retouch::ImageSaver saver;
    try
    {
        retouch::Image layer_1 = loader.loadPNG("../images/input_images/flower.png");
        retouch::LaplacianPyramid pyramid(layer_1);
        pyramid.build();
        auto reconstructed = pyramid.reconstructImage();
        int current_layer = 0;
        std::string file_path = "../images/output_images/reconstructed_flower_" + std::to_string(current_layer++) + ".png";
        saver.savePNG(reconstructed, file_path);

    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what();
    }
}
