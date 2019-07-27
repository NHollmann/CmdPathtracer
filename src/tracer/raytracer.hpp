#pragma once

#include "../math/ray.hpp"
#include "../scene/hitable.hpp"

namespace tracer
{
    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, int depth);
}
