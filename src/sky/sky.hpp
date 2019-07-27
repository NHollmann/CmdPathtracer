#pragma once

#include "../math/ray.hpp"

namespace sky
{
    class Sky
    {
    public:
        virtual ~Sky() = default;
        virtual math::Vector3 skyColor(const math::Ray& ray) const = 0;
    };
}
