#include "world.hpp"

namespace world
{
    WorldData::~WorldData()
    {
        delete camera;
        delete world;
        delete sky;
    }

    tracer::Camera* WorldData::getCamera()
    {
        return camera;
    }

    scene::Hitable* WorldData::getWorld()
    {
        return world;
    }

    sky::Sky* WorldData::getSky()
    {
        return sky;
    }
}
