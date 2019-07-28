#include "raytracer.hpp"
#include "../material/material.hpp"

#include <thread>
#include <atomic>
#include <vector>

namespace tracer
{
    inline int colorFloatToInt(floating color)
    {
        return (int)(255.99f * color);
    }

    void raytraceSimple(output::ImageOutput* imageOut, world::WorldData* world, int width, int height, int samples, int depth)
    {
        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                math::Vector3 color(0, 0, 0);

                for (int sample = 0; sample < samples; sample++)
                {
                    floating u = ((floating)(x) + drand48()) / (floating)(width);
                    floating v = ((floating)(y) + drand48()) / (floating)(height);

                    math::Ray ray = world->getCamera()->getRay(u, v);
                    color += tracer::traceColor(ray, world->getWorld(), world->getSky(), depth);
                }

                color /= (floating) samples;
                color = math::Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

                int r = colorFloatToInt(color.r());
                int g = colorFloatToInt(color.g());
                int b = colorFloatToInt(color.b());
                imageOut->write(r, g, b);
            }
        }
    }

    void raytraceMultithreaded(output::BufferedOutput& buffer, world::WorldData* world, int width, int height, int samples, int depth, int threadCount, int blockSize)
    {
        std::atomic_int count(0);
        std::vector<std::thread> threadPool;
        threadPool.reserve(threadCount);
        uint8_t* dataBuffer = buffer.getData();
        const int blockCountH = 1 + ((width - 1) / blockSize);
        const int blockCountV = 1 + ((height - 1) / blockSize);
        const int blockMax = blockCountH * blockCountV;

        for (int i = 0; i < threadCount; i++)
        {
            threadPool.emplace_back([=, &count](){
                while (true)
                {
                    const int index = count++;
                    if (index >= blockMax)
                    {
                        break;
                    }

                    const int xStart = (index % blockCountH) * blockSize;
                    const int yStart = (index / blockCountH) * blockSize;
                    const int xEnd = MIN(width, xStart + blockSize);
                    const int yEnd = MIN(height, yStart + blockSize);

                    for (int y = yStart; y < yEnd; y++)
                    {
                        for (int x = xStart; x < xEnd; x++)
                        {
                            math::Vector3 color(0, 0, 0);

                            for (int sample = 0; sample < samples; sample++)
                            {
                                floating u = ((floating)(x) + drand48()) / (floating)(width);
                                floating v = ((floating)(y) + drand48()) / (floating)(height);

                                math::Ray ray = world->getCamera()->getRay(u, v);
                                color += tracer::traceColor(ray, world->getWorld(), world->getSky(), depth);
                            }

                            color /= (floating) samples;
                            color = math::Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

                            int idx = (((height - 1) - y) * width + x) * 3;
                            dataBuffer[idx + 0] = colorFloatToInt(color.r());
                            dataBuffer[idx + 1] = colorFloatToInt(color.g());
                            dataBuffer[idx + 2] = colorFloatToInt(color.b());
                        }
                    }
                }
            });
        }

        for (auto& thread : threadPool)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

    math::Vector3 traceColor(const math::Ray& ray, scene::Hitable *world, sky::Sky *sky, int depth)
    {
        scene::HitRecord rec;
        
        if (world->hit(ray, 0.001, MAX_FLOATING, rec))
        {
            math::Ray scattered;
            math::Vector3 attenuation;
            if (depth > 0 && rec.matPtr->scatter(ray, rec, attenuation, scattered))
            {
                return attenuation * traceColor(scattered, world, sky, depth - 1);
            }
            else
            {
                return math::Vector3(0, 0, 0);
            }
        }
        else
        {
            return sky->skyColor(ray);
        }
    }
}
