#include "argparse.hpp"

#include <iostream>
#include "cxxopts.hpp"

namespace cli
{
    RaytracerOptions parseArguments(int argc, char *argv[])
    {
        RaytracerOptions raytracerOptions;
        cxxopts::Options options(argv[0], "A toy raytracer by Nicolas Hollmann.");

        options.add_options("General")
            ("help", "Print help");

        options.add_options("IO")
            ("o,output", "Output filename", cxxopts::value<std::string>()->default_value("out.ppm"), "file")
            ("f,format", "Output format", cxxopts::value<std::string>()->default_value("ppm"), "format");

        options.add_options("Raytracer")    
            ("w,width", "Width of the target image", cxxopts::value<int>()->default_value("200"), "width")
            ("h,height", "Height of the target image", cxxopts::value<int>()->default_value("100"), "height")
            ("s,samples", "Samples per pixel", cxxopts::value<int>()->default_value("100"), "samples")
            ("d,depth", "Max ray depth", cxxopts::value<int>()->default_value("50"), "depth");
        
        options.add_options("Multithreading")
            ("p,parallel", "Enables multithreading")
            ("t,threads", "Sets the thread count, 0 for auto", cxxopts::value<unsigned int>()->default_value("0"), "threads")
            ("blocksize", "Sets the size of a thread block", cxxopts::value<unsigned int>()->default_value("16"), "size");
        
        options.add_options("Scene")
            ("world", "The world to render", cxxopts::value<std::string>()->default_value("random"), "world");

        try {
            auto result = options.parse(argc, argv);
            
            if (result.count("help"))
            {
                std::cout << options.help() << std::endl;
                exit(0);
            }

            raytracerOptions.width = result["width"].as<int>();
            raytracerOptions.height = result["height"].as<int>();
            raytracerOptions.samples = result["samples"].as<int>();
            raytracerOptions.depth = result["depth"].as<int>();

            raytracerOptions.filename = result["output"].as<std::string>();
            raytracerOptions.format = result["format"].as<std::string>();

            raytracerOptions.multithreading = result.count("parallel") != 0;
            raytracerOptions.threadCount = result["threads"].as<unsigned int>();
            raytracerOptions.blockSize = result["blocksize"].as<unsigned int>();

            raytracerOptions.world = result["world"].as<std::string>();
        } 
        catch (const cxxopts::OptionException& e)
        {
            std::cerr << "Error parsing options: " << e.what() << std::endl;
            exit(1);
        }

        return raytracerOptions;
    }
}

