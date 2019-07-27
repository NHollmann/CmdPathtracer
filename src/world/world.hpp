#pragma once

#include "../types.hpp"
#include "../scene/world.hpp"
#include "../scene/sphere.hpp"
#include "../tracer/camera.hpp"
#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"

namespace world
{
    class WorldData
    {
    public:
        WorldData(tracer::Camera* c, scene::Hitable* w) : camera(c), world(w) {}
        ~WorldData();

        tracer::Camera* getCamera();
        scene::Hitable* getWorld();

    private:
        tracer::Camera* camera;
        scene::Hitable* world;
    };
}

