#include "combinedMaterial.h"
#include "mathUtility.h"
#include <cassert>
#include <memory>

CombinedMaterial::CombinedMaterial(std::shared_ptr<const Material> first, std::shared_ptr<const Material> second)
{
    assert(first && second);

    m_factor = 0.5f;

    m_FirstMaterial = first;
    m_SecondMaterial = second;

    m_currentMaterial = m_FirstMaterial;
}

Color CombinedMaterial::eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf, bool &isDelta) const
{
    // if (MathUtility::genRandomDecimal() < m_factor)
    //     m_currentMaterial = m_FirstMaterial;
    // else
    //     m_currentMaterial = m_SecondMaterial;

    return Color();
}
