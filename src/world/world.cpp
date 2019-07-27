#include "world.hpp"

namespace world
{
    WorldData::~WorldData()
    {
        delete camera;
        delete world;
    }

    tracer::Camera* WorldData::getCamera()
    {
        return camera;
    }

    scene::Hitable* WorldData::getWorld()
    {
        return world;
    }
}
