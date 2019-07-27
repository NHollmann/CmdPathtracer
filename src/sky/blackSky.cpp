#include "blackSky.hpp"

namespace sky
{
    math::Vector3 BlackSky::skyColor(const math::Ray& ray) const
    {
        return math::Vector3(0, 0, 0);
    }
}
