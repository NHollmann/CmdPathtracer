# Ray Tracing in a Weekend
My implementation of [Ray Tracing in a Weekend](http://in1weekend.blogspot.com/2016/01/ray-tracing-in-one-weekend.html) by Peter Shirley.
The code follows the one from the book, but I've changed a lot of the code structure and added some extra features.

## Features

- [x] Runs from the command line with options
- [x] PPM Output
- [x] BMP Output
- [x] Antialiasing
- [x] Diffuse, Metal and Dielectric Materials
- [x] Positionable camera
- [x] Defocus blur

## Running
The usage is relly simple. For a complete overview of all options, enter `./raytracer --help`. Here are some examples:
```bash
./raytracer --help # Print help with all options
./raytracer # Start raytracing of the default world with default settings
./raytracer --world random # Random Scene (from the book)
./raytracer --world demo # Demo Scene (from the book)
./raytracer --width 1280 --height 640 # Output image with size 1280x640
```

## Requirements
The final binary has no requirements.

To compile this project you need `cmake` >= 3.2 and a C++ compiler with support for C++14. There aren't any other dependencies.
It was tested on Linux (Ubuntu, with gcc), macOS Mojave (clang) and Windows 10 (MSVC).

## Compiling
This project uses cmake for cross platform compilation.

### Unix
Use the default cmake workflow:
```bash
# Assuming you are already in the project directory
mkdir build # Out of source build
cd build
cmake ..
make
./raytracer --help # Show help to check if compilation was successfull.
```

### Windows
Use cmake for windows to create a Visual Studio project.
Open this project and make sure you have Release selected, then compile the complete project.
This was tested with VS 2017.

### Debug build
The project will be builded as Release by default. If you need a debug build, set `CMAKE_BUILD_TYPE` to `Debug`:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

### Double precision
To compile the project with doubles instead of floats, set the cmake option `DOUBLE_AS_FLOAT` to `ON`:
```bash
cmake -DDOUBLE_AS_FLOAT ..
```

## Todo
Some features I like to add:
- [ ] More worlds
- [ ] TGA
- [ ] Multithreading
