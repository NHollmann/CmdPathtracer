#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.hpp"
#include "output/imageOutput.hpp"
#include "output/ppmOutput.hpp"

inline int colorFloatToInt(floating color)
{
    return (int)(255.99f * color);
}

int main()
{
    const int width = 200;
    const int height = 100;

    output::ImageOutput *imageOut = new output::PpmOutput;

    if (!imageOut->open("out.ppm", width, height)) {
        std::cerr << "Could not open out.ppm" << std::endl;
        return 1;
    }

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            floating r = (floating)(x) / (floating)(width);
            floating g = (floating)(y) / (floating)(height);
            floating b = 0.2f;

            int ir = colorFloatToInt(r);
            int ig = colorFloatToInt(g);
            int ib = colorFloatToInt(b);

            imageOut->write(ir, ig, ib);
        }
    }

    imageOut->close();
    delete imageOut;

    return 0;
}
