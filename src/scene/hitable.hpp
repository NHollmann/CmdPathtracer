#pragma once

#include "../math/ray.hpp"

namespace scene
{

    struct HitRecord
    {
        floating t;
        math::Vector3 point;
        math::Vector3 normal;
    };

    class Hitable
    {
    public:
        virtual bool hit(const math::Ray& ray, floating tMin, floating tMay, HitRecord& rec) const = 0;
    };
}
