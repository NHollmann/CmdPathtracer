cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(raytracer VERSION 1.1 LANGUAGES CXX)

option(DOUBLE_AS_FLOAT "Use doubles instead of floats" OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall /we")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

if (DOUBLE_AS_FLOAT)
	add_definitions(-DDOUBLE_AS_FLOAT)
endif()

file(GLOB_RECURSE src_files
	"src/*.hpp"
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} ${src_files})
