#include "lambertian.hpp"

namespace mat
{
    bool Lambertian::scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const
    {
        math::Vector3 target = rec.point + rec.normal + math::unit_vector(math::random_in_unit_sphere());
        scattered = math::Ray(rec.point, target - rec.point, rayIn.time());
        attenuation = albedo;
        return true;
    }
}
