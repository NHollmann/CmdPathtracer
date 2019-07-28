#include "bufferedOutput.hpp"

#include <iostream>
#include <iomanip>

namespace output
{
    bool BufferedOutput::open(std::string filename, int width, int height)
    {
        data = new uint8_t[width * height * 3];

        this->width = width;
        outfile.open(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

        if (outfile.is_open())
        {
            outfile << "P3\n" << width << " " << height << "\n255\n";
        }

        return outfile.is_open();
    }

    void BufferedOutput::write(int r, int g, int b)
    {
        outfile << std::setw(3) << r << " ";
        outfile << std::setw(3) << g << " ";
        outfile << std::setw(3) << b << " ";

        counter++;
        if (counter % width == 0) {
            outfile << "\n";
        }
    }

    void BufferedOutput::close()
    {
        outfile.close();
    }

    BufferedOutput::~BufferedOutput() 
    {
        delete[] data;
    }
}
