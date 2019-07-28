#include "tgaOutput.hpp"

#include <iostream>

// WARNING: This code may only run with litte endian systems!
#define BYTE1(num) ((uint8_t)((num) & 0xFF))
#define BYTE2(num) ((uint8_t)(((num) >> 8) & 0xFF))

namespace output
{
    bool TgaOutput::open(std::string filename, int width, int height)
    {
        data = new uint8_t[width * height * 3];
        this->width = width;
        counter = 0;
        line = height - 1;

        outfile.open(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

        if (outfile.is_open())
        {
            uint32_t tgaW = width;
            uint32_t tgaH = height;

            uint8_t tgaHeader[] = {
                0x00,       // Image-ID Length 
                0x00,       // Color-Palette (0 = no)
                0x02,       // Image-Type (2 = RGB)
                0x00, 0x00, // Palette-Start
                0x00, 0x00, // Palette-Length
                0x00,       // Palette entry size 
                0x00, 0x00, // x start
                0x00, 0x00, // y start
                BYTE1(tgaW), BYTE2(tgaW), // width
                BYTE1(tgaH), BYTE2(tgaH), // height
                0x18,       // Bits per pixel = 24
                0x00,       // Attributes
            };

            outfile.write((char*)tgaHeader, sizeof(tgaHeader));
        }

        return outfile.is_open();
    }

    void TgaOutput::write(int r, int g, int b)
    {
        int idx = (line * width + (counter % width)) * 3;

        data[idx + 0] = b;
        data[idx + 1] = g;
        data[idx + 2] = r;

        counter++;
        if (counter % width == 0) {
            line--;
        }
    }

    void TgaOutput::close()
    {
        outfile.write((char *) data, counter * 3);
        outfile.close();
    }

    TgaOutput::~TgaOutput() 
    {
        delete[] data;

        if (outfile.is_open()) {
            std::cerr << "tga Output was not closed properly!" << std::endl;
            outfile.close();
        }
    }
}
