#pragma once

#include "../math/ray.hpp"
#include "../scene/hitable.hpp"
#include "../output/imageOutput.hpp"
#include "../output/bufferedOutput.hpp"
#include "../world/world.hpp"

namespace tracer
{
    void raytraceSimple(output::ImageOutput* imageOut, world::WorldData* world, int width, int height, int samples, int depth);
    void raytraceMultithreaded(output::BufferedOutput& buffer, world::WorldData* world, int width, int height, int samples, int depth, int threadCount, int blockSize);

    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, sky::Sky *sky, int depth);
}
