#pragma once

#include "sky.hpp"

namespace sky
{
    class BlackSky : public Sky
    {
    public:
        virtual ~BlackSky() = default;
        virtual math::Vector3 skyColor(const math::Ray& ray) const;
    };
}
