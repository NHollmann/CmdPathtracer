#include <iostream>
#include <fstream>
#include <iomanip>

inline int colorFloatToInt(float color)
{
    return (int)(255.99f * color);
}

int main()
{
    const int width = 200;
    const int height = 100;

    std::ofstream outfile;
    outfile.open("out.ppm", std::ios::out | std::ios::trunc | std::ios::binary);

    if (!outfile.is_open()) {
        std::cerr << "Could not open out.ppm" << std::endl;
        return 1;
    }

    outfile << "P3\n" << width << " " << height << "\n255\n";

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            float r = (float)(x) / (float)(width);
            float g = (float)(y) / (float)(height);
            float b = 0.2f;

            int ir = colorFloatToInt(r);
            int ig = colorFloatToInt(g);
            int ib = colorFloatToInt(b);

            outfile << std::setw(3) << ir << " ";
            outfile << std::setw(3) << ig << " ";
            outfile << std::setw(3) << ib << " ";
        }
        outfile << "\n";
    }

    outfile.close();

    return 0;
}
