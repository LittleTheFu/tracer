#include "media.h"

Media::Media(float a, float s, Color e)
    : sigma_a(a), sigma_s(s), sigma_n(5.0f), emitColor(e)
{
    sigma_major = sigma_s + sigma_a + sigma_n;
}

Media::Media()
    : sigma_a(0.0f), sigma_s(0.0f), sigma_n(0.0f), emitColor(Color::COLOR_BLACK)
{
}

void Media::set(float a, float s, float n, Color e)
{
    sigma_a = a;
    sigma_s = s;
    sigma_n = n;

    sigma_major = sigma_s + sigma_a + sigma_n;
    emitColor = e;
}

bool Media::isVacuum() const
{
    return sigma_major == 0.0f;
}
