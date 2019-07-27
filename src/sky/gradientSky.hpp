#pragma once

#include "sky.hpp"

namespace sky
{
    class GradientSky : public Sky
    {
    public:
        GradientSky(math::Vector3 top, math::Vector3 bot) : topColor(top), bottomColor(bot) {}
        virtual ~GradientSky() = default;
        virtual math::Vector3 skyColor(const math::Ray& ray) const;
    
    private:
        math::Vector3 topColor;
        math::Vector3 bottomColor;
    };
}
