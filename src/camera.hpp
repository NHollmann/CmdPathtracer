#pragma once

#include "math/ray.hpp"

class Camera
{
public:
    Camera(math::Vector3 lookFrom, math::Vector3 lookAt, math::Vector3 vUp, floating vfov, floating aspect);
    math::Ray getRay(float u, float v);

private:
    math::Vector3 origin;
    math::Vector3 lower_left_corner;
    math::Vector3 horizontal;
    math::Vector3 vertical;
};
