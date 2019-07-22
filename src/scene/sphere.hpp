#pragma once

#include "hitable.hpp"
#include "../material/material.hpp"

namespace scene
{
    class Sphere : public Hitable
    {
    public:
        Sphere() {}
        Sphere(math::Vector3 cen, floating r, mat::Material *mat) : center(cen), radius(r), material(mat) {}

        virtual bool hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const;

    private:
        math::Vector3 center;
        floating radius;
        mat::Material *material;
    };
}
