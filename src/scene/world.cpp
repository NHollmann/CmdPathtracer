#include "world.hpp"

namespace scene
{
    bool World::hit(const math::Ray& ray, floating tMin, floating tMax, HitRecord& rec) const
    {
        HitRecord tempRec;
        bool hitAnything = false;
        floating closestSoFar = tMax;

        for (int i = 0; i < listSize; i++)
        {
            if (list[i]->hit(ray, tMin, closestSoFar, tempRec))
            {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }
}
