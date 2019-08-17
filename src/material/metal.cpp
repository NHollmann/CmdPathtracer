#include "metal.hpp"

namespace mat
{
    bool Metal::scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const
    {
        math::Vector3 reflected = math::reflect(math::unit_vector(rayIn.direction()), rec.normal);
        scattered = math::Ray(rec.point, reflected + fuzz * math::random_in_unit_sphere(), rayIn.time());
        attenuation = albedo;
        return math::dot(scattered.direction(), rec.normal) > 0;
    }
}
