#pragma once

#include "material.hpp"

namespace mat
{
    class Dielectric : public Material
    {
    public:
        Dielectric(floating ri) : refractionIndex(ri) {}
        virtual ~Dielectric() = default;

        virtual bool scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const;
    
    private:
        floating refractionIndex;
    };
}
