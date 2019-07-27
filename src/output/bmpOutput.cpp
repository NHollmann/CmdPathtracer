#include "bmpOutput.hpp"

#include <iostream>

// WARNING: This code may only run with litte endian systems!
#define BYTE1(num) ((uint8_t)((num) & 0xFF))
#define BYTE2(num) ((uint8_t)(((num) >> 8) & 0xFF))
#define BYTE3(num) ((uint8_t)(((num) >> 16) & 0xFF))
#define BYTE4(num) ((uint8_t)(((num) >> 24) & 0xFF))

namespace output
{
    bool BmpOutput::open(std::string filename, int width, int height)
    {
        outfile.open(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

        if (outfile.is_open())
        {
            uint32_t bmpSize = 54 + width * height * 3;

            uint8_t fileHeader[] = {
                0x42, 0x4D, // "BM"
                BYTE1(bmpSize), BYTE2(bmpSize), BYTE3(bmpSize), BYTE4(bmpSize), // Size
                0x00, 0x00, 0x00, 0x00, // Reserved
                0x36, 0x00, 0x00, 0x00, // Data Offset
            };

            int32_t bmpW =  width;
            int32_t bmpH = -height; // negative becuase this is a top-down bmp

            uint8_t infoHeader[] = {
                0x28, 0x00, 0x00, 0x00, // Size of this header
                BYTE1(bmpW), BYTE2(bmpW), BYTE3(bmpW), BYTE4(bmpW), // Width
                BYTE1(bmpH), BYTE2(bmpH), BYTE3(bmpH), BYTE4(bmpH), // Height
                0x01, 0x00,             // Planes
                0x18, 0x00,             // Bits per Pixel => 24
                0x00, 0x00, 0x00, 0x00, // Compression
                0x00, 0x00, 0x00, 0x00, // Image size, 0 is allowed for uncompressed images
                0x00, 0x00, 0x00, 0x00, // Horizontal resolution, 0 allowed
                0x00, 0x00, 0x00, 0x00, // Vertical resolution, 0 allowed
                0x00, 0x00, 0x00, 0x00, // Entries in color table
                0x00, 0x00, 0x00, 0x00, // Colors used, not needed
            };


            outfile.write((char*)fileHeader, sizeof(fileHeader));
            outfile.write((char*)infoHeader, sizeof(infoHeader));
        }

        return outfile.is_open();
    }

    void BmpOutput::write(int r, int g, int b)
    {
        uint8_t bgrData[3];
        bgrData[0] = b;
        bgrData[1] = g;
        bgrData[2] = r;
        outfile.write((char *) bgrData, sizeof(bgrData));
    }

    void BmpOutput::close()
    {
        outfile.close();
    }

    BmpOutput::~BmpOutput() 
    {
        if (outfile.is_open()) {
            std::cerr << "bmp Output was not closed properly!" << std::endl;
            outfile.close();
        }
    }
}
