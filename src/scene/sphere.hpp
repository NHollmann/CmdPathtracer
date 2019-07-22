#pragma once

#include "hitable.hpp"

namespace scene
{

    class Sphere : public Hitable
    {
    public:
        Sphere() {}
        Sphere(math::Vector3 cen, floating r) : center(cen), radius(r) {}

        virtual bool hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const;

    private:
        math::Vector3 center;
        floating radius;
    };
}
