#pragma once

#include <string>

namespace cli
{
    struct RaytracerOptions
    {
        int width;
        int height;
        int samples;
        int depth;
        std::string filename;
        std::string format;
        std::string world;
    };

    RaytracerOptions parseArguments(int argc, char *argv[]);
}
