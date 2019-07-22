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
}
