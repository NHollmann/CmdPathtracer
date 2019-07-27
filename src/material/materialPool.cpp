#include "materialPool.hpp"

namespace mat
{
    MaterialPool::~MaterialPool()
    {
        for (Material* mat : materials)
        {
            delete mat;
        }
    }

    void MaterialPool::add(Material* mat)
    {
        if (mat != nullptr)
        {
            materials.push_back(mat);
        }
    }

    Material* MaterialPool::operator()(Material *mat)
    {
        add(mat);
        return mat;
    }
}
