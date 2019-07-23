#include "dielectric.hpp"

namespace mat
{
    floating schlick(floating cosine, floating refractionIndex)
    {
        floating r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow(1 - cosine, 5);
    }

    bool Dielectric::scatter(const math::Ray& rayIn, const scene::HitRecord& rec, math::Vector3& attenuation, math::Ray& scattered) const
    {
        attenuation = math::Vector3(1.0, 1.0, 1.0);

        math::Vector3 outwardNormal;
        floating ni_over_nt;
        math::Vector3 refracted;

        floating reflectProb;
        floating cosine;
        

        if (math::dot(rayIn.direction(), rec.normal) > 0)
        {
            outwardNormal = -rec.normal;
            ni_over_nt = refractionIndex;
            cosine = refractionIndex * math::dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
        }
        else
        {
            outwardNormal = rec.normal;
            ni_over_nt = 1.0 / refractionIndex;
            cosine = - math::dot(rayIn.direction(), rec.normal) / rayIn.direction().length();
        }
        
        if (math::refract(rayIn.direction(), outwardNormal, ni_over_nt, refracted))
        {
            reflectProb = schlick(cosine, refractionIndex);
        }
        else
        {
            reflectProb = 1.0;
        }

        if (drand48() < reflectProb)
        {
            math::Vector3 reflected = math::reflect(rayIn.direction(), rec.normal);
            scattered = math::Ray(rec.point, reflected);
        }
        else
        {
            scattered = math::Ray(rec.point, refracted);
        }
        
        
        return true;
    }
}
