#pragma once

#include "hitable.hpp"
#include "../material/material.hpp"

namespace scene
{
    class MovingSphere : public Hitable
    {
    public:
        MovingSphere() {}
        MovingSphere(math::Vector3 cen0, math::Vector3 cen1, floating t0, floating t1, floating r, mat::Material *mat) : 
                        center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), material(mat) {}
        virtual ~MovingSphere() = default;

        virtual bool hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const;

        math::Vector3 center(floating time) const;

    private:
        math::Vector3 center0, center1;
        floating time0, time1;
        floating radius;
        mat::Material *material;
    };
}
