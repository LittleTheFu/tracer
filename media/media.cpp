#include "media.h"

Media::Media(float a, float s, Color e)
    : sigma_a(a), sigma_s(s), sigma_n(1.0f), emitColor(e)
{
    sigma_major = sigma_s + sigma_a + sigma_n;
    m_isClear = false;
}

Media::Media()
{
    m_isClear = true;
}

void Media::set(float a, float s, float n, Color e)
{
    sigma_a = a;
    sigma_s = s;
    sigma_n = n;

    sigma_major = sigma_s + sigma_a + sigma_n;
    emitColor = e;

    m_isClear = false;
}

void Media::clear()
{
    sigma_a = 0.0f;
    sigma_s = 0.0f;
    sigma_n = 0.0f;

    sigma_major = 0.0f;

    m_isClear = true;
}

bool Media::isClear() const
{
    return m_isClear;
}
