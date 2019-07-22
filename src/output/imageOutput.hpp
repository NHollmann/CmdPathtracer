#pragma once

#include <string>

namespace output
{
    class ImageOutput
    {
    public:
        virtual bool open(std::string filename, int width, int height) = 0;
        virtual void write(int r, int g, int b) = 0;
        virtual void close() = 0;

        virtual ~ImageOutput() = default;
    };
}
