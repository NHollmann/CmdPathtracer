#include "random.hpp"

namespace world
{
    static scene::Hitable* randomScene(mat::MaterialPool& matPool)
    {
        const int N = 500;
        mat::Material* mat;
        scene::Hitable **list = new scene::Hitable*[N+1];

        mat = matPool(new mat::Lambertian(math::Vector3(0.5, 0.5, 0.5)));
        list[0] = new scene::Sphere(math::Vector3(0, -1000, 0), 1000, mat);

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
                        mat = matPool(new mat::Lambertian(math::Vector3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                    }
                    else if (chooseMat < 0.95)
                    {
                        mat = matPool(new mat::Metal(math::Vector3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
                    }
                    else
                    {
                        mat = matPool(new mat::Dielectric(1.5));
                    }

                    list[i++] = new scene::Sphere(center, 0.2, mat);
                }
            }
        }

        mat = matPool(new mat::Dielectric(1.5));
        list[i++] = new scene::Sphere(math::Vector3(0, 1, 0), 1.0, mat);

        mat = matPool(new mat::Lambertian(math::Vector3(0.4, 0.2, 0.1)));
        list[i++] = new scene::Sphere(math::Vector3(-4, 1, 0), 1.0, mat);

        mat = matPool(new mat::Metal(math::Vector3(0.7, 0.6, 0.5), 0.0));
        list[i++] = new scene::Sphere(math::Vector3(4, 1, 0), 1.0, mat);

        return new scene::World(list, i);
    }

    WorldData* getRandomWorld(floating aspect, mat::MaterialPool& matPool)
    {
        math::Vector3 lookFrom(13, 2, 3);
        math::Vector3 lookAt(0, 0, 0);
        floating distToFocus = 10.0;
        floating aperture = 0.1;

        tracer::Camera* camera = new tracer::Camera(
            lookFrom,
            lookAt,
            math::Vector3(0, 1, 0),
            20, aspect,
            aperture, distToFocus
        );

        return new WorldData(camera, randomScene(matPool));
    }
}
