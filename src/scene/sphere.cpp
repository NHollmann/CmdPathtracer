#include "sphere.hpp"

namespace scene
{
    Sphere::~Sphere()
    {
        // TODO delete Material! (Materialpool?)
    }

    bool Sphere::hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const
    {
        math::Vector3 oc = ray.origin() - center;
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
                rec.normal = (rec.point - center) / radius;
                rec.matPtr = material;
                return true;
            }

            temp = (-b + sqrt(discriminant)) / a;
            // TODO: Remove duplicated code
            if (temp > tMin && temp < tMax)
            {
                rec.t = temp;
                rec.point = ray.pointAt(rec.t);
                rec.normal = (rec.point - center) / radius;
                rec.matPtr = material;
                return true;
            }
        }

        return false;
    }
}
