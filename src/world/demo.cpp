#include "random.hpp"

namespace world
{
    WorldData* getDemoWorld(floating aspect, mat::MaterialPool& matPool)
    {
        mat::Material *mat;
        scene::Hitable **list = new scene::Hitable*[5];

        mat = matPool(new mat::Lambertian(math::Vector3(0.1, 0.2, 0.5)));
        list[0] = new scene::Sphere(math::Vector3(0, 0, -1), 0.5, mat);

        mat = matPool(new mat::Lambertian(math::Vector3(0.8, 0.8, 0.0)));
        list[1] = new scene::Sphere(math::Vector3(0, -100.5, -1), 100, mat);

        mat = matPool(new mat::Metal(math::Vector3(0.8, 0.6, 0.2), 0.2));
        list[2] = new scene::Sphere(math::Vector3(1, 0, -1), 0.5, mat);

        mat = matPool(new mat::Dielectric(1.5));
        list[3] = new scene::Sphere(math::Vector3(-1, 0, -1), 0.5, mat);
        list[4] = new scene::Sphere(math::Vector3(-1, 0, -1), -0.45, mat);

        scene::Hitable *world = new scene::World(list, 5);

        math::Vector3 lookFrom(0, 0, 1);
        math::Vector3 lookAt(0, 0, 0);
        floating distToFocus = 1.0;
        floating aperture = 0;

        tracer::Camera* camera = new tracer::Camera(
            lookFrom,
            lookAt,
            math::Vector3(0, 1, 0),
            50, aspect,
            aperture, distToFocus
        );

        return new WorldData(camera, world);
    }
}
