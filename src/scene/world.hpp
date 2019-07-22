#pragma once

#include "hitable.hpp"

namespace scene
{
    class World : public Hitable
    {
    public:
        World() {}
        World(Hitable **l, int n) : list(l), listSize(n) {}

        virtual bool hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const;

    private:
        Hitable **list;
        int listSize;
    };
}
