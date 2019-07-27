#pragma once

#include "../math/ray.hpp"
#include "../scene/hitable.hpp"
#include "../output/imageOutput.hpp"
#include "../world/world.hpp"

namespace tracer
{
    void raytraceSimple(output::ImageOutput* imageOut, world::WorldData* world, int width, int height, int samples, int depth);

    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, int depth);
}
