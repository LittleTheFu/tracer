#include "combinedMaterial.h"
#include "mathUtility.h"
#include <cassert>
#include <memory>

CombinedMaterial::CombinedMaterial(std::shared_ptr<Material> first, std::shared_ptr<Material> second)
{
    assert(first && second);

    m_factor = 0.5f;

    m_FirstMaterial = first;
    m_SecondMaterial = second;

    m_currentMaterial = m_FirstMaterial;
}

Color CombinedMaterial::get_f(const Vector3 &wo, const Vector3 &wi) const
{
    return m_currentMaterial->get_f(wo, wi);
}

Color CombinedMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta)
{
    Color color;

    if (MathUtility::genRandomDecimal() < m_factor)
    {
        m_currentMaterial = m_FirstMaterial;
        color = m_FirstMaterial->eval(u, v, wo, wi, pdf, isDelta);
        pdf *= m_factor;
    }
    else
    {
        m_currentMaterial = m_SecondMaterial;
        color = m_SecondMaterial->eval(u, v, wo, wi, pdf, isDelta);
        pdf *= (1 - m_factor);
    }

    return color;
}
