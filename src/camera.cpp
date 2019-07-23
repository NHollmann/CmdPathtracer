#include "camera.hpp"

Camera::Camera(math::Vector3 lookFrom, math::Vector3 lookAt, math::Vector3 vUp, floating vfov, floating aspect)
{
    math::Vector3 u, v, w;

    floating theta = vfov * M_PI / 180;
    floating halfHeight = tan(theta / 2);
    floating halfWidth = aspect * halfHeight;

    origin = lookFrom;
    w = math::unit_vector(lookFrom - lookAt);
    u = math::unit_vector(math::cross(vUp, w));
    v = math::cross(w, u);

    lower_left_corner = origin - halfWidth * u - halfHeight * v - w;
    horizontal = 2 * halfWidth * u;
    vertical = 2 * halfHeight * v;;
}

math::Ray Camera::getRay(float u, float v)
{
    return math::Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}
