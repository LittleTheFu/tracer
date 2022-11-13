#ifndef _R_MATERIAL_H_
#define _R_MATERIAL_H_

#include "brdf.h"
#include "color.h"
#include "ray.h"
#include "texture.h"
#include "vector.h"

class Material
{
public:
    Material();

    virtual Color eval(float u, float v, const Vector3 &wo, Vector3 &wi, float &pdf) const;
    bool isMirror() const;

    // void setBrdf(const Brdf *pBrdf);
    // const Brdf *getBrdf() const;

    // void setTexture(const Texture *pTexture);
    // const Texture *getTexture() const;

protected:
    const Brdf *m_pBrdf;
    const Texture *m_pTexture;
};

#endif