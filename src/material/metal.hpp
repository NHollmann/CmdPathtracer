#pragma once

#include "material.hpp"

namespace mat
{
    class Metal : public Material
    {
    public:
        Metal(const math::Vector3& a, floating f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
        virtual ~Metal() = default;

        virtual bool scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const;
    
    private:
        math::Vector3 albedo;
        floating fuzz;
    };
}
