#include <iostream>
#include <fstream>
#include <iomanip>

#include "types.hpp"
#include "output/ppmOutput.hpp"
#include "math/ray.hpp"

math::Vector3 traceColor(const math::Ray& ray)
{
    math::Vector3 unit_dir = math::unit_vector(ray.direction());
    floating t = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - t) * math::Vector3(1.0, 1.0, 1.0) + t * math::Vector3(0.5, 0.7, 1.0);
}

inline int colorFloatToInt(floating color)
{
    return (int)(255.99f * color);
}

int main()
{
    const int width = 400;
    const int height = 200;

    output::ImageOutput *imageOut = new output::PpmOutput;

    if (!imageOut->open("out.ppm", width, height)) {
        std::cerr << "Could not open out.ppm" << std::endl;
        return 1;
    }

    math::Vector3 lower_left(-2.0, -1.0, -1.0);
    math::Vector3 horizontal(4.0, 0.0, 0.0);
    math::Vector3 vertical(0.0, 2.0, -1.0);
    math::Vector3 origin(0.0, 0.0, 0.0);

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            floating u = (floating)(x) / (floating)(width);
            floating v = (floating)(y) / (floating)(height);

            math::Ray ray(origin, lower_left + u * horizontal + v * vertical);

            math::Vector3 color = traceColor(ray);

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
