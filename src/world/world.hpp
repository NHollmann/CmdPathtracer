#pragma once

#include "../types.hpp"
#include "../scene/world.hpp"
#include "../scene/sphere.hpp"
#include "../scene/movingSphere.hpp"
#include "../tracer/camera.hpp"
#include "../material/materialPool.hpp"
#include "../material/lambertian.hpp"
#include "../material/metal.hpp"
#include "../material/dielectric.hpp"
#include "../sky/blackSky.hpp"
#include "../sky/gradientSky.hpp"

namespace world
{
    class WorldData
    {
    public:
        WorldData(tracer::Camera* c, scene::Hitable* w, sky::Sky *s) : camera(c), world(w), sky(s) {}
        ~WorldData();

        tracer::Camera* getCamera();
        scene::Hitable* getWorld();
        sky::Sky* getSky();

    private:
        tracer::Camera* camera;
        scene::Hitable* world;
        sky::Sky* sky;
    };
}

