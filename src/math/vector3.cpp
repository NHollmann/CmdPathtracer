#include "vector3.hpp"

namespace math
{
    Vector3 random_in_unit_sphere()
    {
        Vector3 point;

        do {
            point = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
        } while (point.squared_length() >= 1.0);

        return point;
    }

    Vector3 random_in_unit_disk()
    {
        Vector3 point;

        do {
            point = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1, 1, 0);
        } while (dot(point, point) >= 1.0);

        return point;
    }

    bool refract(const Vector3& v, const Vector3& n, floating ni_over_nt, Vector3& refracted)
    {
        Vector3 unitV = unit_vector(v);
        floating dt = dot(unitV, n);
        floating discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
        if (discriminant > 0)
        {
            refracted = ni_over_nt * (unitV - n * dt) - n * sqrt(discriminant);
            return true;
        }
        else
        {
            return false;
        }
        
    }
}
