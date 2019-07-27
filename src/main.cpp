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
#include "tracer/camera.hpp"
#include "tracer/raytracer.hpp"

inline int colorFloatToInt(floating color)
{
    return (int)(255.99f * color);
}

scene::Hitable *randomScene()
{
    const int N = 500;
    scene::Hitable **list = new scene::Hitable*[N+1];
    list[0] = new scene::Sphere(math::Vector3(0, -1000, 0), 1000, new mat::Lambertian(math::Vector3(0.5, 0.5, 0.5)));
    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            floating chooseMat = drand48();
            math::Vector3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - math::Vector3(4, 0.2, 0)).length() > 0.9)
            {
                if (chooseMat < 0.8)
                {
                    list[i++] = new scene::Sphere(center, 0.2, new mat::Lambertian(math::Vector3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                }
                else if (chooseMat < 0.95)
                {
                    list[i++] = new scene::Sphere(center, 0.2, new mat::Metal(math::Vector3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
                }
                else
                {
                    list[i++] = new scene::Sphere(center, 0.2, new mat::Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new scene::Sphere(math::Vector3(0, 1, 0), 1.0, new mat::Dielectric(1.5));
    list[i++] = new scene::Sphere(math::Vector3(-4, 1, 0), 1.0, new mat::Lambertian(math::Vector3(0.4, 0.2, 0.1)));
    list[i++] = new scene::Sphere(math::Vector3(4, 1, 0), 1.0, new mat::Metal(math::Vector3(0.7, 0.6, 0.5), 0.0));

    return new scene::World(list, i);
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

    /* scene::Hitable *list[5];
    list[0] = new scene::Sphere(math::Vector3(0, 0, -1), 0.5, new mat::Lambertian(math::Vector3(0.1, 0.2, 0.5)));
    list[1] = new scene::Sphere(math::Vector3(0, -100.5, -1), 100, new mat::Lambertian(math::Vector3(0.8, 0.8, 0.0)));
    list[2] = new scene::Sphere(math::Vector3(1, 0, -1), 0.5, new mat::Metal(math::Vector3(0.8, 0.6, 0.2), 0.2));
    list[3] = new scene::Sphere(math::Vector3(-1, 0, -1), 0.5, new mat::Dielectric(1.5));
    list[4] = new scene::Sphere(math::Vector3(-1, 0, -1), -0.45, new mat::Dielectric(1.5));
    scene::Hitable *world = new scene::World(list, 5); */
    scene::Hitable *world = randomScene();

    math::Vector3 lookFrom(13, 2, 3);
    math::Vector3 lookAt(0, 0, 0);
    floating distToFocus = 10.0;
    floating aperture = 0.1;

    tracer::Camera camera(
        lookFrom,
        lookAt,
        math::Vector3(0, 1, 0),  // Up
        20, (floating)width / (floating) height,
        aperture, distToFocus
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
                color += tracer::traceColor(ray, world, 0);
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
