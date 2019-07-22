#include "camera.hpp"

Camera::Camera()
{
    lower_left_corner = math::Vector3(-2.0, -1.0, -1.0);
    horizontal = math::Vector3(4.0, 0.0, 0.0);
    vertical = math::Vector3(0.0, 2.0, 0.0);
    origin = math::Vector3(0.0, 0.0, 0.0);
}

math::Ray Camera::getRay(float u, float v)
{
    return math::Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}
