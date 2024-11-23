#include "media.h"

Media::Media(float a, float s, Color e)
    : sigma_a(a), sigma_s(s), sigma_n(4000.0f), emitColor(e)
{
    sigma_major = sigma_s + sigma_a + sigma_n;
}

Media::Media() : Media(1.0f, 1.0f, Color::COLOR_NAVY)
{
}