#!/bin/bash

# Mandelbrot Benchmark - Linux Build Script
# Supports both 32-bit and 64-bit builds

set -e

echo "Mandelbrot Benchmark - Linux Build Script"
echo "=========================================="

# Check if SDL2 is installed
if ! pkg-config --exists sdl2; then
    echo "Error: SDL2 development libraries not found!"
    echo "Please install SDL2:"
    echo "  Ubuntu/Debian: sudo apt-get install libsdl2-dev"
    echo "  Fedora/RHEL:   sudo dnf install SDL2-devel"
    echo "  Arch:          sudo pacman -S sdl2"
    exit 1
fi

# Check for OpenMP support
if ! echo '#include <omp.h>' | gcc -fopenmp -x c - -o /dev/null 2>/dev/null; then
    echo "Warning: OpenMP not available. Installing..."
    if command -v apt-get >/dev/null 2>&1; then
        sudo apt-get update && sudo apt-get install -y libomp-dev
    elif command -v dnf >/dev/null 2>&1; then
        sudo dnf install -y libgomp-devel
    elif command -v pacman >/dev/null 2>&1; then
        sudo pacman -S --noconfirm openmp
    fi
fi

# Determine architecture
ARCH=$(uname -m)
if [ "$ARCH" = "x86_64" ]; then
    BUILD_TYPE="64bit"
    CMAKE_FLAGS=""
elif [ "$ARCH" = "i386" ] || [ "$ARCH" = "i686" ]; then
    BUILD_TYPE="32bit"
    CMAKE_FLAGS="-DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32"
else
    echo "Architecture $ARCH detected, building for native"
    BUILD_TYPE="native"
    CMAKE_FLAGS=""
fi

echo "Building for Linux $BUILD_TYPE..."

# Create build directory
BUILD_DIR="build_linux_$BUILD_TYPE"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
cmake .. $CMAKE_FLAGS \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=../install_linux_$BUILD_TYPE

# Build
make -j$(nproc)

echo ""
echo "Build completed successfully!"
echo "Executable: $BUILD_DIR/bin/mandelbrot_benchmark"
echo ""
echo "To install: make install"
echo "To run: ./bin/mandelbrot_benchmark"
