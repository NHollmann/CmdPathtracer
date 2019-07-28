#pragma once

#include <fstream>

#include "imageOutput.hpp"

namespace output
{
    class TgaOutput : public ImageOutput
    {
    public:
        virtual bool open(std::string filename, int width, int height);
        virtual void write(int r, int g, int b) ;
        virtual void close();
        virtual ~TgaOutput();

    private:
        uint8_t* data;
        uint64_t counter;
        int line;
        int width;
        std::ofstream outfile;
    };
}
