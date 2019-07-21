cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Raytracer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB src_files
	"src/*.hpp"
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} ${src_files})
