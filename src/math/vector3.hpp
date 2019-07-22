#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "../types.hpp"

namespace math {

    class Vector3
    {
    public:
        Vector3() {}
        Vector3(floating e0, floating e1, floating e2) {
            elements[0] = e0;
            elements[1] = e1;
            elements[2] = e2;
        }

        inline floating x() const { return elements[0]; }
        inline floating y() const { return elements[1]; }
        inline floating z() const { return elements[2]; }
        inline floating r() const { return elements[0]; }
        inline floating g() const { return elements[1]; }
        inline floating b() const { return elements[2]; }

        inline const Vector3& operator+() const { return *this; }
        inline Vector3 operator-() const { return Vector3(-elements[0], -elements[1], -elements[2]); }
        inline floating operator[](int i) const { return elements[i]; }
        inline floating& operator[](int i) { return elements[i]; }

        inline Vector3& operator+=(const Vector3 &v2);
        inline Vector3& operator-=(const Vector3 &v2);
        inline Vector3& operator*=(const Vector3 &v2);
        inline Vector3& operator/=(const Vector3 &v2);
        inline Vector3& operator*=(const floating t);
        inline Vector3& operator/=(const floating t);

        inline floating length() const
        {
            return sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]);
        }

        inline floating squared_length() const
        {
            return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
        }

        inline void make_unit_vector()
        {
            floating k = 1.0 / sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]);
            elements[0] *= k;
            elements[1] *= k;
            elements[2] *= k;
        }

    private:
        floating elements[3];
    };

    inline std::istream& operator>>(std::istream &is, Vector3 &t)
    {
        is >> t[0] >> t[1] >> t[2];
        return is;
    }

    inline std::ostream& operator<<(std::ostream &os, Vector3 &t)
    {
        os << t[0] << " " << t[1] << " " << t[2];
        return os;
    }

    inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
    }

    inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
    }

    inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
    }

    inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]);
    }

    inline Vector3 operator*(floating t, const Vector3 &v)
    {
        return Vector3(v[0] * t, v[1] * t, v[2] * t);
    }

    inline Vector3 operator*(const Vector3 &v, floating t)
    {
        return Vector3(v[0] * t, v[1] * t, v[2] * t);
    }

    inline Vector3 operator/(const Vector3 &v, floating t)
    {
        return Vector3(v[0] / t, v[1] / t, v[2] / t);
    }

    inline floating dot(const Vector3 &v1, const Vector3 &v2)
    {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }

    inline Vector3 cross(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3(
            v1[1] * v2[2] - v1[2] * v2[1],
            v1[2] * v2[0] - v1[0] * v2[2],
            v1[0] * v2[1] - v1[1] * v2[0]
        );
    }

    inline Vector3& Vector3::operator+=(const Vector3 &v)
    {
        elements[0] += v.elements[0];
        elements[1] += v.elements[1];
        elements[2] += v.elements[2];

        return *this;
    }

    inline Vector3& Vector3::operator-=(const Vector3 &v)
    {
        elements[0] -= v.elements[0];
        elements[1] -= v.elements[1];
        elements[2] -= v.elements[2];

        return *this;
    }

    inline Vector3& Vector3::operator*=(const Vector3 &v)
    {
        elements[0] *= v.elements[0];
        elements[1] *= v.elements[1];
        elements[2] *= v.elements[2];

        return *this;
    }

    inline Vector3& Vector3::operator/=(const Vector3 &v)
    {
        elements[0] /= v.elements[0];
        elements[1] /= v.elements[1];
        elements[2] /= v.elements[2];

        return *this;
    }

    inline Vector3& Vector3::operator*=(const floating t)
    {
        elements[0] *= t;
        elements[1] *= t;
        elements[2] *= t;

        return *this;
    }

    inline Vector3& Vector3::operator/=(const floating t)
    {
        floating k = 1.0 / t;

        elements[0] *= k;
        elements[1] *= k;
        elements[2] *= k;

        return *this;
    }

    inline Vector3 unit_vector(Vector3 v)
    {
        return v / v.length();
    }

    inline Vector3 reflect(const Vector3& v, const Vector3& n)
    {
        return v - 2.0 * dot(v, n) * n;
    }

    Vector3 random_in_unit_sphere();
}
