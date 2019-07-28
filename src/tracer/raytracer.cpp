#include "raytracer.hpp"
#include "../material/material.hpp"

namespace tracer
{
    inline int colorFloatToInt(floating color)
    {
        return (int)(255.99f * color);
    }

    void raytraceSimple(output::ImageOutput* imageOut, world::WorldData* world, int width, int height, int samples, int depth)
    {
        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                math::Vector3 color(0, 0, 0);

                for (int sample = 0; sample < samples; sample++)
                {
                    floating u = ((floating)(x) + drand48()) / (floating)(width);
                    floating v = ((floating)(y) + drand48()) / (floating)(height);

                    math::Ray ray = world->getCamera()->getRay(u, v);
                    color += tracer::traceColor(ray, world->getWorld(), world->getSky(), depth);
                }

                color /= (floating) samples;
                color = math::Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

                int r = colorFloatToInt(color.r());
                int g = colorFloatToInt(color.g());
                int b = colorFloatToInt(color.b());
                imageOut->write(r, g, b);
            }
        }
    }

    void raytraceMultithreaded(output::ImageOutput* imageOut, world::WorldData* world, int width, int height, int samples, int depth)
    {
        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                math::Vector3 color(0, 0, 0);

                for (int sample = 0; sample < samples; sample++)
                {
                    floating u = ((floating)(x) + drand48()) / (floating)(width);
                    floating v = ((floating)(y) + drand48()) / (floating)(height);

                    math::Ray ray = world->getCamera()->getRay(u, v);
                    color += tracer::traceColor(ray, world->getWorld(), world->getSky(), depth);
                }

                color /= (floating) samples;
                color = math::Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

                int r = colorFloatToInt(color.r());
                int g = colorFloatToInt(color.g());
                int b = colorFloatToInt(color.b());
                imageOut->write(r, g, b);
            }
        }
    }

    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, sky::Sky *sky, int depth)
    {
        scene::HitRecord rec;
        
        if (world->hit(ray, 0.001, MAX_FLOATING, rec))
        {
            math::Ray scattered;
            math::Vector3 attenuation;
            if (depth > 0 && rec.matPtr->scatter(ray, rec, attenuation, scattered))
            {
                return attenuation * traceColor(scattered, world, sky, depth - 1);
            }
            else
            {
                return math::Vector3(0, 0, 0);
            }
        }
        else
        {
            return sky->skyColor(ray);
        }
    }
}
