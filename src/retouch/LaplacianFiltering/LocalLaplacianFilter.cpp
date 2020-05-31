#include <iostream>
#include <thread>

#include "LocalLaplacianFilter.h"
#include "../Image/ImageSaver.h"

namespace retouch
{
    Image LocalLaplacianFilter::apply(const Image &image, const double &alpha,
                                                          const double &beta, const double &sigma) const
    {
        constexpr size_t KPyramid_size = 5;
        GaussianPyramid gaussian_pyramid(image, KPyramid_size);
        LaplacianPyramid output_pyramid(image.getWidth(), image.getHeight(),
                                        image.getChannelsCount(), KPyramid_size);
        output_pyramid.setLayer(KPyramid_size - 1, gaussian_pyramid[KPyramid_size - 1]);

        // hardware_concurrency can return 0
        const size_t number_of_threads = (std::thread::hardware_concurrency() != 0) ?
                std::thread::hardware_concurrency() : 1;

        std::vector<std::thread> working_threads(number_of_threads);

        RemapFunction remap_function(alpha, beta, sigma);

        for(int i = 0; i < number_of_threads; i++)
        {
            working_threads[i] = std::thread(&LocalLaplacianFilter::threadExecute, *this,
                    std::cref(gaussian_pyramid), std::ref(output_pyramid), std::cref(remap_function),
                    number_of_threads, i);
        }

        for(int i = 0; i < number_of_threads; i++)
        {
            working_threads[i].join();
        }

        return output_pyramid.reconstructImage();
    }


    void LocalLaplacianFilter::threadExecute(const GaussianPyramid &gaussian_pyramid, LaplacianPyramid &output_pyramid,
                                             RemapFunction remap_function, size_t num_of_threads, size_t current_thread) const
    {
        const size_t KPyramid_size = output_pyramid.getLayers().size();

        for(int layer_number = 0; layer_number < KPyramid_size - 1; layer_number++)
        {
            const size_t KGaussian_width = gaussian_pyramid[layer_number].getWidth();
            const size_t KGaussian_height = gaussian_pyramid[layer_number].getHeight();

            const int KSubimage_size = 3 * ((pow(2, layer_number + 2)) - 1);
            const int KSubimage_radius = KSubimage_size / 2;

            for(int y = current_thread; y < KGaussian_height; y+=num_of_threads)
            {
                int y_in_full_resolution = y * pow(2,  layer_number);
                int y_top_bound = std::max(y_in_full_resolution - KSubimage_radius, 0);
                int y_bottom_bound = std::min<int>(y_in_full_resolution + KSubimage_radius,
                        gaussian_pyramid[0].getHeight());
                for(int x = 0; x < KGaussian_width; x++)
                {
                    std::cout << layer_number << " " << x << " " << y << "\n";
                    int x_in_full_resolution = x * pow(2, layer_number);

                    glm::ivec2 subimage_start = {std::max(x_in_full_resolution - KSubimage_radius, 0), y_top_bound};
                    glm::ivec2 subimage_end = {std::min<int>(x_in_full_resolution + KSubimage_radius, gaussian_pyramid[0].getWidth()), y_bottom_bound};

                    Image remapped_subimage = remap_function.remap(gaussian_pyramid[0], subimage_start,
                                                                   subimage_end, gaussian_pyramid[layer_number].getPixel(x, y));

                    LaplacianPyramid temp_laplacian(remapped_subimage);

                    int new_x = (x_in_full_resolution - subimage_start.x) / pow(2, layer_number);
                    int new_y = (y_in_full_resolution - subimage_start.y) / pow(2, layer_number);
                    Pixel new_pixel = temp_laplacian[layer_number].getPixel(new_x, new_y);
                    output_pyramid.setLayerPixel(layer_number, x, y, new_pixel);

                }
            }

        }
    }
}