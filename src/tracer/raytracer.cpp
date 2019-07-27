#include "raytracer.hpp"
#include "../material/material.hpp"

namespace tracer
{
    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, int depth)
    {
        scene::HitRecord rec;

        if (world->hit(ray, 0.001, MAX_FLOATING, rec))
        {
            math::Ray scattered;
            math::Vector3 attenuation;
            if (depth > 0 && rec.matPtr->scatter(ray, rec, attenuation, scattered))
            {
                return attenuation * traceColor(scattered, world, depth - 1);
            }
            else
            {
                return math::Vector3(0, 0, 0);
            }
        }
        else
        {
            math::Vector3 unit_dir = math::unit_vector(ray.direction());
            floating t = 0.5 * (unit_dir.y() + 1.0);
            return (1.0 - t) * math::Vector3(1.0, 1.0, 1.0) + t * math::Vector3(0.5, 0.7, 1.0);
        }
    }
}
