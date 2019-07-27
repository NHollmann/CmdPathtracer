#pragma once

#include "material.hpp"

namespace mat
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const math::Vector3& a) : albedo(a) {}
        virtual ~Lambertian() = default;

        virtual bool scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const;
    
    private:
        math::Vector3 albedo;
    };
}
