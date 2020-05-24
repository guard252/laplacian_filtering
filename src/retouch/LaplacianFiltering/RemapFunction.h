#ifndef LAPLACIAN_PYRAMID_REMAPFUNCTION_H
#define LAPLACIAN_PYRAMID_REMAPFUNCTION_H
#include <functional>

#include "../Image/Image.h"

namespace retouch
{
    class RemapFunction
    {
    private:
        double m_alpha;
        double m_beta;
        double m_sigma;

        std::function<double(const double&)> m_remapDetailsFunction;
    private:
        double computeTau(const double& pixel) const;

        Pixel remapPixel(const Pixel& original_pixel, const Pixel& gaussian_pixel) const;

        double remapEdges(const double& delta) const;

        double remapDetails(const double& delta) const;

    public:
        RemapFunction(const double &alpha, const double &beta, const double &sigma);

        Image remap(const Image& input_image, const Image& gaussian_layer) const;
    };
}

#endif //LAPLACIAN_PYRAMID_REMAPFUNCTION_H
