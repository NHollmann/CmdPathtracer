#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.hpp"
#include "output/ppmOutput.hpp"
#include "math/ray.hpp"
#include "scene/world.hpp"
#include "scene/sphere.hpp"
#include "material/lambertian.hpp"
#include "material/metal.hpp"
#include "material/dielectric.hpp"
#include "camera.hpp"

math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, int depth)
{
    scene::HitRecord rec;

    if (world->hit(ray, 0.001, MAX_FLOATING, rec))
    {
        math::Ray scattered;
        math::Vector3 attenuation;
        if (depth < 50 && rec.matPtr->scatter(ray, rec, attenuation, scattered))
        {
            return attenuation * traceColor(scattered, world, depth + 1);
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

inline int colorFloatToInt(floating color)
{
    return (int)(255.99f * color);
}

int main()
{
    const int width = 200;
    const int height = 100;
    const int samples = 100;

    output::ImageOutput *imageOut = new output::PpmOutput;

    if (!imageOut->open("out.ppm", width, height)) {
        std::cerr << "Could not open out.ppm" << std::endl;
        return 1;
    }

    scene::Hitable *list[5];
    list[0] = new scene::Sphere(math::Vector3(0, 0, -1), 0.5, new mat::Lambertian(math::Vector3(0.1, 0.2, 0.5)));
    list[1] = new scene::Sphere(math::Vector3(0, -100.5, -1), 100, new mat::Lambertian(math::Vector3(0.8, 0.8, 0.0)));
    list[2] = new scene::Sphere(math::Vector3(1, 0, -1), 0.5, new mat::Metal(math::Vector3(0.8, 0.6, 0.2), 0.2));
    list[3] = new scene::Sphere(math::Vector3(-1, 0, -1), 0.5, new mat::Dielectric(1.5));
    list[4] = new scene::Sphere(math::Vector3(-1, 0, -1), -0.45, new mat::Dielectric(1.5));
    scene::Hitable *world = new scene::World(list, 5);

    Camera camera(
        math::Vector3(-2, 2, 1), // LookFrom
        math::Vector3(0, 0, -1), // LookAt
        math::Vector3(0, 1, 0),  // Up
        60, (floating)width / (floating) height
    );

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            math::Vector3 color(0, 0, 0);

            for (int sample = 0; sample < samples; sample++)
            {
                floating u = ((floating)(x) + drand48()) / (floating)(width);
                floating v = ((floating)(y) + drand48()) / (floating)(height);

                math::Ray ray = camera.getRay(u, v);
                color += traceColor(ray, world, 0);
            }

            color /= (floating) samples;
            color = math::Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

            int r = colorFloatToInt(color.r());
            int g = colorFloatToInt(color.g());
            int b = colorFloatToInt(color.b());
            imageOut->write(r, g, b);
        }
    }

    // TODO free memory? (Would need destructors)

    imageOut->close();
    delete imageOut;

    return 0;
}
