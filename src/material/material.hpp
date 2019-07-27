#pragma once

#include "../math/ray.hpp"
#include "../scene/hitable.hpp"

namespace mat
{
    class Material
    {
    public:
        virtual ~Material() = default;
        virtual bool scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const = 0;
    };
}
