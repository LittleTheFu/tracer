#include "combinedMaterial.h"
#include "mathUtility.h"
#include <cassert>
#include <memory>

CombinedMaterial::CombinedMaterial(std::shared_ptr<Material> first, std::shared_ptr<Material> second, float weight)
{
    assert(first && second);

    m_weight = weight;

    m_FirstMaterial = first;
    m_SecondMaterial = second;

    m_currentMaterial = m_FirstMaterial;
}

Color CombinedMaterial::eval(float u,
                             float v,
                             const Vector3 &wo,
                             Vector3 &wi,
                             float &pdf,
                             bool &isDelta,
                             std::shared_ptr<Brdf> &brdf)
{
    Color color;

    if (MathUtility::genRandomDecimal() < m_weight)
    {
        m_currentMaterial = m_FirstMaterial;
        color = m_FirstMaterial->eval(u, v, wo, wi, pdf, isDelta, brdf);
        pdf *= m_weight;
    }
    else
    {
        m_currentMaterial = m_SecondMaterial;
        color = m_SecondMaterial->eval(u, v, wo, wi, pdf, isDelta, brdf);
        pdf *= (1 - m_weight);
    }

    return color;
}
