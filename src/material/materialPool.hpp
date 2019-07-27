#pragma once

#include "material.hpp"

#include <vector>

namespace mat
{
    class MaterialPool
    {
    public:
        MaterialPool() = default;
        ~MaterialPool();

        void add(Material* mat);
        Material* operator()(Material *mat);

    private:
        MaterialPool(const MaterialPool&) = delete;
        MaterialPool& operator=(const MaterialPool&) = delete;

        std::vector<Material*> materials;
    };
}
