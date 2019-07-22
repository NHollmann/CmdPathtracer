#pragma once

#include "math/ray.hpp"

class Camera
{
public:
    Camera();
    math::Ray getRay(float u, float v);

private:
    math::Vector3 origin;
    math::Vector3 lower_left_corner;
    math::Vector3 horizontal;
    math::Vector3 vertical;
};
