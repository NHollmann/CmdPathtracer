#pragma once

#include "../math/ray.hpp"

namespace mat
{
    class Material;
}

namespace scene
{
    struct HitRecord
    {
        floating t;
        math::Vector3 point;
        math::Vector3 normal;
        mat::Material *matPtr;
    };

    class Hitable
    {
    public:
        virtual bool hit(const math::Ray& ray, floating tMin, floating tMay, HitRecord& rec) const = 0;
    };
}
