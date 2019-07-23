#include "camera.hpp"

Camera::Camera(math::Vector3 lookFrom, math::Vector3 lookAt, math::Vector3 vUp, floating vfov, floating aspect, floating aperture, floating focusDist)
{
    lensRadius = aperture / 2.0;

    floating theta = vfov * M_PI / 180;
    floating halfHeight = tan(theta / 2);
    floating halfWidth = aspect * halfHeight;

    origin = lookFrom;
    w = math::unit_vector(lookFrom - lookAt);
    u = math::unit_vector(math::cross(vUp, w));
    v = math::cross(w, u);

    lower_left_corner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
    horizontal = 2 * halfWidth * focusDist * u;
    vertical = 2 * halfHeight * focusDist * v;;
}

math::Ray Camera::getRay(floating s, floating t)
{
    math::Vector3 rd = lensRadius * math::random_in_unit_disk();
    math::Vector3 offset = u * rd.x() + v * rd.y();
    return math::Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}
