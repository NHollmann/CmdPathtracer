#include "movingSphere.hpp"

namespace scene
{
    math::Vector3 MovingSphere::center(floating time) const
    {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }

    bool MovingSphere::hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const
    {
        math::Vector3 oc = ray.origin() - center(ray.time());
        floating a = math::dot(ray.direction(), ray.direction());
        floating b = math::dot(oc, ray.direction());
        floating c = math::dot(oc, oc) - radius * radius;
        floating discriminant = b * b - a * c;
        
        if (discriminant > 0) 
        {
            floating temp = (-b - sqrt(discriminant)) / a;
            if (temp > tMin && temp < tMax)
            {
                rec.t = temp;
                rec.point = ray.pointAt(rec.t);
                rec.normal = (rec.point - center(ray.time())) / radius;
                rec.matPtr = material;
                return true;
            }

            temp = (-b + sqrt(discriminant)) / a;
            // TODO: Remove duplicated code
            if (temp > tMin && temp < tMax)
            {
                rec.t = temp;
                rec.point = ray.pointAt(rec.t);
                rec.normal = (rec.point - center(ray.time())) / radius;
                rec.matPtr = material;
                return true;
            }
        }

        return false;
    }
}
