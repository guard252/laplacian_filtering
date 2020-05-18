#include "LaplacianPyramid.h"

namespace retouch
{

    LaplacianPyramid::LaplacianPyramid(const Image &first_layer) : m_gaussian_pyramid(first_layer){}

    void LaplacianPyramid::build()
    {
        m_gaussian_pyramid.build();
        for(int layer = 0; layer != m_gaussian_pyramid.getLayers().size() - 1; layer++)
        {
            Image reduced_and_expanded = m_gaussian_pyramid.expand(layer + 1);;
            m_layers.push_back(reduced_and_expanded - m_gaussian_pyramid[layer]);
        }
        m_layers.push_back(m_gaussian_pyramid.getLayers().back());
    }
}