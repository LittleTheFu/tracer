#ifndef _VOLUME_H_
#define _VOLUME_H_

#include <memory>

class Medium;
class Ray;

class Volume
{
public:
    Volume(std::shared_ptr<Medium> medium);
    std::shared_ptr<Medium> getMedium() const;

    virtual bool intersect(const Ray& ray, float& t0, float& t1) const = 0;

private:
    std::shared_ptr<Medium> medium_;

};

#endif