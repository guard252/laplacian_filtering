#include <iostream>
#include "LocalLaplacianFilter.h"
#include "../Pyramid/LaplacianPyramid.h"
#include "RemapFunction.h"
#include "../Image/ImageSaver.h"

namespace retouch
{
    Image LocalLaplacianFilter::apply(const Image &image, const double &alpha,
                                                          const double &beta, const double &sigma) const
    {
        const size_t KPypamid_size = 5;
        GaussianPyramid gaussian_pyramid(image, KPypamid_size);
        LaplacianPyramid output_pyramid(image.getWidth(), image.getHeight(),
                image.getChannelsCount(), KPypamid_size);
        output_pyramid.setLayer(KPypamid_size - 1, gaussian_pyramid[KPypamid_size - 1]);

        RemapFunction remap_function(alpha, beta, sigma);

        for(int layer_number = 0; layer_number < KPypamid_size - 1; layer_number++)
        {
            const size_t KGaussian_width = gaussian_pyramid[layer_number].getWidth();
            const size_t KGaussian_height = gaussian_pyramid[layer_number].getHeight();

            const int KSubimage_size = 3 * ((pow(2, layer_number + 2)) - 1);
            const int KSubimage_radius = KSubimage_size / 2;

            for(int y = 0; y < KGaussian_height; y++)
            {
                int y_in_full_resolution = y * pow(2,  layer_number);
                int y_top_bound = std::max(y_in_full_resolution - KSubimage_radius, 0);
                int y_bottom_bound = std::min<int>(y_in_full_resolution + KSubimage_radius, image.getHeight());
                //if(y == KGaussian_height - 1) y_bottom_bound = image.getHeight();
                for(int x = 0; x < KGaussian_width; x++)
                {
                    std::cout << layer_number << " " << x << " " << y << "\n";
                    int x_in_full_resolution = x * pow(2, layer_number);

                    glm::ivec2 subimage_start = {std::max(x_in_full_resolution - KSubimage_radius, 0), y_top_bound};
                    glm::ivec2 subimage_end = {std::min<int>(x_in_full_resolution + KSubimage_radius, image.getWidth()), y_bottom_bound};

                    Image remapped_subimage = remap_function.remap(image, subimage_start,
                            subimage_end, gaussian_pyramid[layer_number].getPixel(x, y));

                    LaplacianPyramid temp_laplacian(remapped_subimage);

                    int new_x = (x_in_full_resolution - subimage_start.x) / pow(2, layer_number);
                    int new_y = (y_in_full_resolution - subimage_start.y) / pow(2, layer_number);
                    Pixel new_pixel = temp_laplacian[layer_number].getPixel(new_x, new_y);
                    output_pyramid.setLayerPixel(layer_number, x, y, new_pixel);

                }
            }
            ImageSaver saver;
            saver.savePNG(output_pyramid[layer_number], "../images/output_images/layer_" + std::to_string(layer_number) + ".png");

        }
        return output_pyramid.reconstructImage();
    }

    std::unordered_map<glm::ivec2, Image, Ivec2Hashing, Ivec2Hashing>
            LocalLaplacianFilter::divideIntoSubimages(const Image &image, size_t count_on_axis) const
    {
        size_t subimage_width = image.getWidth() / count_on_axis;
        size_t subimage_height = image.getHeight() / count_on_axis;
        std::unordered_map<glm::ivec2, Image, Ivec2Hashing, Ivec2Hashing> result;

        for(int y = 0; y < count_on_axis - 1; y++)
        {
            for(int x = 0; x < count_on_axis - 1; x++)
            {
                result.emplace(glm::ivec2{x, y}, image.getSubImage({x * subimage_width, y * subimage_height},
                                                   {(x + 1) * subimage_width - 1, (y + 1) * subimage_height - 1}));
            }
            result.emplace(glm::ivec2{count_on_axis - 1, y},
                    image.getSubImage(
                    {(count_on_axis - 1) * subimage_width, y * subimage_height},
                    {image.getWidth() - 1, (y + 1) * subimage_height - 1}
                    ));
        }
        for(int x = 0; x < count_on_axis - 1; x++)
        {
            result.emplace(glm::ivec2{x, count_on_axis - 1},
                    image.getSubImage(
                    {x * subimage_width, (count_on_axis - 1) * subimage_height},
                    {(x + 1) * subimage_width - 1, image.getHeight() - 1}
                    ));
        }
        result.emplace(glm::ivec2{count_on_axis - 1, count_on_axis - 1},
                image.getSubImage({(count_on_axis - 1) * subimage_width, (count_on_axis - 1) * subimage_height},
                {image.getWidth() - 1, image.getHeight() - 1}));
        return result;
    }
}