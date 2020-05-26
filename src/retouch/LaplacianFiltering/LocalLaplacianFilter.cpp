#include "LocalLaplacianFilter.h"
#include "../Pyramid/LaplacianPyramid.h"
#include "RemapFunction.h"
#include "../Image/ImageSaver.h"

namespace retouch
{
    Image LocalLaplacianFilter::apply(const Image &image, const double &alpha,
                                                          const double &beta, const double &sigma) const
    {
        GaussianPyramid gaussian_pyramid(image);
        const size_t KGaussian_pyramid_size = gaussian_pyramid.getLayers().size();
        const size_t KGaussian_laplacian_difference = 3;
        const size_t KLaplacian_pyramid_size = KGaussian_pyramid_size - KGaussian_laplacian_difference;

        LaplacianPyramid output_pyramid(image.getWidth(), image.getHeight(),
                image.getChannelsCount(), KLaplacian_pyramid_size);

        output_pyramid.setLayer(KLaplacian_pyramid_size - 1, gaussian_pyramid[KLaplacian_pyramid_size - 1]);

        RemapFunction remap_function(alpha, beta, sigma);

        const size_t KSubimage_min_width = gaussian_pyramid[KLaplacian_pyramid_size - 2].getWidth() / 2;
        const size_t KSubimage_min_height = gaussian_pyramid[KLaplacian_pyramid_size - 2].getHeight() / 2;

        for(int layer_number = 0; layer_number < KLaplacian_pyramid_size - 1; layer_number++)
        {
            const size_t KSubimages_on_axis = std::pow(2, layer_number + 1);
            const size_t KOutput_layer_number = KLaplacian_pyramid_size - layer_number - 2;
            Image gaussian_current_layer = gaussian_pyramid.expandToLayer(KOutput_layer_number, 0);
            if(layer_number == 0)
            {
                Image cur = remap_function.remap(gaussian_pyramid[0], gaussian_current_layer);
                ImageSaver saver;
                saver.savePNG(cur, "../images/output_images/cur.png");
            }

            std::unordered_map subimages = divideIntoSubimages(image, KSubimages_on_axis);
            std::unordered_map gaussian_subimages = divideIntoSubimages(gaussian_current_layer, KSubimages_on_axis);

            size_t overall_width = 0;
            for(int x = 0; x < KSubimages_on_axis; x++)
            {
                size_t overall_height = 0;
                int current_width;
                for(int y = 0; y < KSubimages_on_axis; y++)
                {
                     assert(subimages.find({x, y}) != subimages.end() &&
                     gaussian_subimages.find({x, y}) != gaussian_subimages.end());

                    Image locally_good_image = remap_function.remap(subimages.find({x, y})->second, gaussian_subimages.find({x, y})->second);
                    LaplacianPyramid temp_laplacian(locally_good_image);

                    glm::vec2 start = {x * KSubimage_min_width, y * KSubimage_min_height};
                    glm::vec2 end = {x * KSubimage_min_width + KSubimage_min_width - 1,
                                     y * KSubimage_min_height + KSubimage_min_height - 1};

//                    if(end.y >= output_pyramid[KOutput_layer_number].getHeight())
//                        end.y = output_pyramid[KOutput_layer_number].getHeight() - 1;
//                    if(end.x >= output_pyramid[KOutput_layer_number].getWidth())
//                        end.x = output_pyramid[KOutput_layer_number].getWidth() - 1;


                    if(start.x < end.x && start.y < end.y)
                    {
                        output_pyramid.setLayerSubImage(KOutput_layer_number,
                                                        temp_laplacian[temp_laplacian.getLayers().size() - 4], start, end);

                    }
                    current_width = temp_laplacian[temp_laplacian.getLayers().size() - 4].getWidth() - 1;
                }
                overall_width += current_width;
            }

        }
        for(int i = 0; i < output_pyramid.getLayers().size(); i++)
        {
            ImageSaver saver;
            saver.savePNG(output_pyramid[i],
                              "../images/output_images/layer_" + std::to_string(i) + ".png");


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