#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.hpp"
#include "output/imageOutput.hpp"
#include "output/ppmOutput.hpp"
#include "math/vector3.hpp"

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
            math::Vector3 color((floating)(x) / (floating)(width), (floating)(y) / (floating)(height), 0.2);

            int r = colorFloatToInt(color.r());
            int g = colorFloatToInt(color.g());
            int b = colorFloatToInt(color.b());
            imageOut->write(r, g, b);
        }
    }

    imageOut->close();
    delete imageOut;

    return 0;
}
