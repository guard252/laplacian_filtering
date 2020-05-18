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
        const auto& layers = pyramid.getLayers();
        int current_layer = 0;
        for(auto layer : layers)
        {
            std::string file_path = "../images/output_images/flower_layer_" + std::to_string(current_layer) + ".png";
            saver.savePNG(layer, file_path);
            current_layer++;
        }
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what();
    }
}
