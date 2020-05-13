#include <iostream>
#include "retouch/ImageLoader.h"
#include "retouch/ImageSaver.h"
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
