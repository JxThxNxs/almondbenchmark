cmake_minimum_required(VERSION 3.12)
project(MandelbrotBenchmark VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLATFORM_NAME "Windows")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_NAME "Linux")
endif()

# Architecture detection
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_NAME "64bit")
else()
    set(ARCH_NAME "32bit")
endif()

message(STATUS "Building for ${PLATFORM_NAME} ${ARCH_NAME}")

# Find SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/mandelbrot.cpp
    src/renderer.cpp
    src/fps_counter.cpp
    src/color_palette.cpp
)

# Create executable
add_executable(mandelbrot_benchmark ${SOURCES})

# Link libraries
target_link_libraries(mandelbrot_benchmark ${SDL2_LIBRARIES})

# Compiler flags for optimization
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(mandelbrot_benchmark PRIVATE 
        -O3 -march=native -mtune=native -fopenmp
        -Wall -Wextra -Wpedantic
    )
    target_link_libraries(mandelbrot_benchmark -fopenmp)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(mandelbrot_benchmark PRIVATE 
        /O2 /openmp /W4
    )
endif()

# Set output directory
set_target_properties(mandelbrot_benchmark PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install target
install(TARGETS mandelbrot_benchmark
    RUNTIME DESTINATION bin
)
