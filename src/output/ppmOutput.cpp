#include "ppmOutput.hpp"

#include <iostream>
#include <iomanip>

namespace output
{
    bool PpmOutput::open(std::string filename, int width, int height)
    {
        this->width = width;
        outfile.open(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

        if (outfile.is_open())
        {
            outfile << "P3\n" << width << " " << height << "\n255\n";
        }

        return outfile.is_open();
    }

    void PpmOutput::write(int r, int g, int b)
    {
        outfile << std::setw(3) << r << " ";
        outfile << std::setw(3) << g << " ";
        outfile << std::setw(3) << b << " ";

        counter++;
        if (counter % width == 0) {
            outfile << "\n";
        }
    }

    void PpmOutput::close()
    {
        outfile.close();
    }

    PpmOutput::~PpmOutput() 
    {
        if (outfile.is_open()) {
            std::cerr << "ppm Output was not closed properly!" << std::endl;
            outfile.close();
        }
    }
}
