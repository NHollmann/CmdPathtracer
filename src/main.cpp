#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.hpp"
#include "output/ppmOutput.hpp"
#include "math/ray.hpp"
#include "scene/world.hpp"
#include "scene/sphere.hpp"
#include "camera.hpp"

// TODO move into math namespace
math::Vector3 random_in_unit_sphere()
{
    math::Vector3 point;

    do {
        point = 2.0 * math::Vector3(drand48(), drand48(), drand48()) - math::Vector3(1, 1, 1);
    } while (point.squared_length() >= 1.0);

    return point;
}

math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world)
{
    scene::HitRecord rec;

    if (world->hit(ray, 0.001, MAX_FLOATING, rec))
    {
        math::Vector3 target = rec.point + rec.normal + random_in_unit_sphere();
        return 0.5 * traceColor(math::Ray(rec.point, target - rec.point), world);
    }

    math::Vector3 unit_dir = math::unit_vector(ray.direction());
    floating t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * math::Vector3(1.0, 1.0, 1.0) + t * math::Vector3(0.5, 0.7, 1.0);
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

    scene::Hitable *list[2];
    list[0] = new scene::Sphere(math::Vector3(0, 0, -1), 0.5);
    list[1] = new scene::Sphere(math::Vector3(0, -100.5, -1), 100);
    scene::Hitable *world = new scene::World(list, 2);

    Camera camera;

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
                color += traceColor(ray, world);
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
