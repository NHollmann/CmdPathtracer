#pragma once

#include <fstream>

#include "imageOutput.hpp"

namespace output
{
    class BufferedOutput
    {
    public:
        BufferedOutput(int width, int height);
        ~BufferedOutput();

        void writeTo(ImageOutput *output);
        uint8_t* getData();

    private:
        uint8_t* data;
        size_t size;
    };
}
