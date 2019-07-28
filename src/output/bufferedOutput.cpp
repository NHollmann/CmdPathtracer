#include "bufferedOutput.hpp"

#include <iostream>
#include <iomanip>

namespace output
{
    BufferedOutput::BufferedOutput(int width, int height)
    {
        size = width * height * 3;
        data = new uint8_t[size];
    }

    BufferedOutput::~BufferedOutput() 
    {
        delete[] data;
    }

    void BufferedOutput::writeTo(ImageOutput *output)
    {
        for (size_t i = 0; i < size; i += 3) {
            output->write(data[i], data[i + 1], data[i + 2]);
        }
    }

    uint8_t* BufferedOutput::getData()
    {
        return data;
    }
}
