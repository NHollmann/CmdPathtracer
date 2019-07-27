#include "gradientSky.hpp"

namespace sky
{
    math::Vector3 GradientSky::skyColor(const math::Ray& ray) const
    {
        math::Vector3 unit_dir = math::unit_vector(ray.direction());
        floating t = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - t) * bottomColor + t * topColor;
    }
}
