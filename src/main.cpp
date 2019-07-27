#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#include "types.hpp"
#include "cli/argparse.hpp"
#include "output/ppmOutput.hpp"
#include "tracer/raytracer.hpp"
#include "world/world.hpp"
#include "world/random.hpp"
#include "world/demo.hpp"

#define REQUIRE_MIN(var, val) ((var) < (val) ? (val) : (var))

world::WorldData* worldFromString(std::string world, floating aspect)
{
    if (world == "random") 
    {
        return world::getRandomWorld(aspect);
    }
    else if (world == "demo")
    {
        return world::getDemoWorld(aspect);
    } 
    else 
    {
        std::cerr << "Unknown world " << world << std::endl;
    }

    exit(1);
    return nullptr;
}

output::ImageOutput* imageOutputFromString(std::string format)
{
    if (format == "ppm") 
    {
        return new output::PpmOutput;
    } 
    else 
    {
        std::cerr << "Unknown fromat " << format << std::endl;
    }

    exit(1);
    return nullptr;
}

int main(int argc, char* argv[])
{
    cli::RaytracerOptions options = cli::parseArguments(argc, argv);

    const int width = REQUIRE_MIN(options.width, 10);
    const int height = REQUIRE_MIN(options.height, 10);
    const int samples = REQUIRE_MIN(options.samples, 1);
    const int depth = REQUIRE_MIN(options.depth, 1);

    const floating aspect = (floating) width / (floating) height;

    output::ImageOutput *imageOut = imageOutputFromString(options.format);
    world::WorldData *world = worldFromString(options.world, aspect);

    std::cout << "Toy Raytracer by Nicolas Hollmann." << std::endl;
    std::cout << "Output filename: " << options.filename << std::endl;
    std::cout << "Output filetype: " << options.format << std::endl;
    std::cout << "World:           " << options.world << std::endl;
    std::cout << "Width:           " << width << std::endl;
    std::cout << "Height:          " << height << std::endl;
    std::cout << "Samples:         " << samples << std::endl;
    std::cout << "Depth:           " << depth << std::endl;
    std::cout << "Starting now!" << std::endl;

    if (!imageOut->open(options.filename, width, height)) {
        std::cerr << "Could not open " << options.filename << " for writing." << std::endl;
        return 1;
    }

    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    
    tracer::raytraceSimple(imageOut, world, width, height, samples, depth);

    imageOut->close();
    delete imageOut;
    delete world;

    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    std::cout << "Raytracer finished after " << elapsedSeconds.count() << " seconds." << std::endl;

    return 0;
}
