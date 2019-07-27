#pragma once

#include "../math/ray.hpp"

namespace tracer
{
    class Camera
    {
    public:
        Camera(math::Vector3 lookFrom, math::Vector3 lookAt, math::Vector3 vUp, floating vfov, floating aspect, floating aperture, floating focusDist);
        math::Ray getRay(floating s, floating t);

    private:
        math::Vector3 origin;
        math::Vector3 lower_left_corner;
        math::Vector3 horizontal;
        math::Vector3 vertical;
        math::Vector3 u, v, w;
        floating lensRadius;
    };
}
