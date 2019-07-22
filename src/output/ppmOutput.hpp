#pragma once

#include <fstream>

#include "imageOutput.hpp"

namespace output
{
    class PpmOutput : public ImageOutput
    {
    public:
        bool open(std::string filename, int width, int height);
        void write(int r, int g, int b) ;
        void close();
        ~PpmOutput();

    private:
        std::ofstream outfile;
        long counter = 0;
        int width;
    };
}
