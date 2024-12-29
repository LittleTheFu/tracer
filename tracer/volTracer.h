// #ifndef _VOL_TRACER_H_
// #define _VOL_TRACER_H_

// #include "tracer.h"
// #include "noise.h"
// #include "vox.h"

// class VolTracer : public Tracer
// {
// public:
//     Color trace(std::shared_ptr<const ObjectPool> pool,
//                 Ray &ray,
//                 int bounceNum,
//                 const HitRecord &currentState) const override;

//     Color traceFirstBounce(std::shared_ptr<const ObjectPool> pool, Ray &ray) const override;

// private:
//     Noise m_noise;
//     Vox m_vox;
// };

// #endif