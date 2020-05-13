#include <iostream>
#include "retouch/Image/ImageLoader.h"
#include "retouch/Image/ImageSaver.h"
int main()
{
    retouch::ImageLoader loader;
    retouch::ImageSaver saver;
    try
    {
        retouch::ImageData data = loader.loadPNG("../input_images/room.png");
        saver.savePNG(data, "../input_images/room_new.png");
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what();
    }
}
