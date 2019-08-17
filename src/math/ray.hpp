#pragma once

#include "vector3.hpp"
#include "../types.hpp"

namespace math {

    class Ray
    {
    public:
        Ray() {}
        Ray(const Vector3& a, const Vector3& b, floating time = 0.0) { orig = a; dir = b; _time = time; }
        inline Vector3 origin() const { return orig; }
        inline Vector3 direction() const { return dir; }
        inline floating time() const { return _time; }
        inline Vector3 pointAt(floating t) const { return orig + t * dir; }

    private:
        Vector3 orig;
        Vector3 dir;
        floating _time;
    };
}
