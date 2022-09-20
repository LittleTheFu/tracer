#include "spectrum.h"

const float Spectrum::CIE_Y_integral = 106.856895f;

Spectrum::Spectrum()
{
    for (int i = 0; i <= number; i++)
    {
        c[i] = RGBRefl2SpectWhite[i / nRGB2SpectSamples];
    }
}

void Spectrum::getXYZ(float xyz[3])
{
    xyz[0] = xyz[1] = xyz[2] = 0.f;
    for (int i = 0; i < number; ++i)
    {
        xyz[0] += CIE_X[i] * c[i];
        xyz[1] += CIE_Y[i] * c[i];
        xyz[2] += CIE_Z[i] * c[i];
    }

    float scale = 1 / float(CIE_Y_integral * number);

    xyz[0] *= scale;
    xyz[1] *= scale;
    xyz[2] *= scale;
}

void Spectrum::getRGB(float inXyz[3], float outRgb[3])
{
    outRgb[0] = 3.240479f * inXyz[0] - 1.537150f * inXyz[1] - 0.498535f * inXyz[2];
    outRgb[1] = -0.969256f * inXyz[0] + 1.875991f * inXyz[1] + 0.041556f * inXyz[2];
    outRgb[2] = 0.055648f * inXyz[0] - 0.204043f * inXyz[1] + 1.057311f * inXyz[2];
}