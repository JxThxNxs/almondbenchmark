# Aalmond Benchmark by JxThxNxs

A high-performance, cross-platform CPU benchmarking tool featuring Mandelbrot set visualization with real-time rendering and comprehensive performance scoring.

![Almond Benchmark](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-blue) ![Architecture](https://img.shields.io/badge/Architecture-32bit%20%7C%2064bit-green) ![Language](https://img.shields.io/badge/Language-C%2B%2B17-red) ![Author](https://img.shields.io/badge/by-JxThxNxs-purple)

## Features

### 🚀 Performance
- **CPU-only computation** with OpenMP parallelization
- **Real-time FPS counter** with min/max/average statistics
- **Almond Score System** - comprehensive CPU performance rating
- **Comprehensive benchmarking** comparing single vs multi-threaded performance
- **Optimized algorithms** with SIMD-friendly code structure

### 🎨 Visualization
- **6 beautiful color palettes**: Classic, Fire, Ocean, Rainbow, Grayscale, Electric
- **Smooth color interpolation** for artifact-free rendering
- **Real-time interactive exploration** with mouse and keyboard controls
- **Auto-zoom mode** for mesmerizing animations

### 🎮 Interactive Controls
- **Mouse**: Click to zoom into any point
- **WASD**: Pan around the fractal
- **Q/E**: Zoom out/in
- **R**: Reset to default view
- **C**: Change color palette (6 beautiful options)
- **Space**: Toggle auto-zoom animation
- **+/-**: Increase/decrease iterations (32-2048)
- **B**: Run benchmark and get your Almond Score
- **ESC**: Exit application

### 🔧 Cross-Platform Support
- **Windows**: 32-bit and 64-bit builds
- **Linux**: 32-bit and 64-bit builds
- **Modern C++17** with CMake build system
- **SDL2** for cross-platform graphics and input

## Quick Start

### Prerequisites

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libsdl2-dev libomp-dev pkg-config
```

#### Linux (Fedora/RHEL)
```bash
sudo dnf install gcc-c++ cmake SDL2-devel libgomp-devel pkgconfig
```

#### Windows
1. Install Visual Studio 2019 or newer with C++ support
2. Install vcpkg (recommended):
   ```cmd
   git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
   cd C:\vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg install sdl2:x64-windows sdl2:x86-windows
   ```

### Building

#### Linux
```bash
chmod +x build_linux.sh
./build_linux.sh
```

#### Windows
Run from Visual Studio Developer Command Prompt:
```cmd
build_windows.bat
```

### Running
```bash
# Linux
./build_linux_64bit/bin/mandelbrot_benchmark

# Windows
.\build_windows_64bit\bin\Release\mandelbrot_benchmark.exe
```

## Almond Score System

The Almond Benchmark features a comprehensive scoring system that evaluates your CPU's performance:

- **Base Score**: Calculated from multi-threaded execution time (10000 / time_ms)
- **Efficiency Bonus**: Rewards good parallelization (efficiency × 1000)
- **Final Score**: Base + Bonus = Your Almond Score
- **Rating System**: 
  - 500+ points: **EXCELLENT!**
  - 300-499: **VERY GOOD**
  - 200-299: **GOOD**
  - 100-199: **AVERAGE**
  - <100: **NEEDS IMPROVEMENT**

### Performance Metrics
- **Single-threaded**: Uses one CPU core
- **Multi-threaded**: Uses all available CPU cores with OpenMP
- **Speedup**: Performance improvement ratio
- **Efficiency**: Parallelization effectiveness
- **Real-time display**: All stats shown during rendering

### Sample Output
```
Almond Benchmark by JxThxNxs
Hardware threads: 8
OpenMP threads: 8

Running Almond Benchmark...
Single-threaded: 121 ms
Multi-threaded (8 threads): 38 ms
Speedup: 3.17x
Efficiency: 39%
ALMOND SCORE: 657 points
Rating: EXCELLENT!
```

## Technical Details

### Algorithm Optimization
- **Escape-time algorithm** with configurable iteration limits
- **Smooth coloring** using continuous iteration count
- **Memory-efficient** pixel buffer management
- **Cache-friendly** memory access patterns

### Parallelization
- **OpenMP** for automatic work distribution
- **Thread-safe** color palette operations
- **NUMA-aware** memory allocation
- **Scalable** to high core counts

### Graphics Pipeline
- **Software rendering** for maximum compatibility
- **32-bit ARGB** pixel format
- **Double-buffered** presentation
- **Optimized** pixel manipulation

## Build Targets

| Platform | Architecture | Compiler | Output |
|----------|-------------|----------|---------|
| Linux | x86_64 | GCC/Clang | `build_linux_64bit/bin/mandelbrot_benchmark` |
| Linux | i386 | GCC/Clang | `build_linux_32bit/bin/mandelbrot_benchmark` |
| Windows | x64 | MSVC | `build_windows_64bit/bin/Release/mandelbrot_benchmark.exe` |
| Windows | x86 | MSVC | `build_windows_32bit/bin/Release/mandelbrot_benchmark.exe` |

## Configuration

### Compilation Flags
- **Release mode**: `-O3` optimization with native CPU tuning
- **OpenMP**: Automatic parallelization enabled
- **Warnings**: Comprehensive warning flags enabled
- **Standards**: C++17 compliance required

### Runtime Parameters
- **Resolution**: 800x600 (configurable in source)
- **Default iterations**: 256 (adjustable 32-2048)
- **Default zoom**: 1.0 (interactive adjustment)
- **Color depth**: 32-bit ARGB

## Troubleshooting

### Common Issues

**SDL2 not found (Linux)**
```bash
# Ubuntu/Debian
sudo apt-get install libsdl2-dev

# Fedora
sudo dnf install SDL2-devel
```

**OpenMP not available**
```bash
# Ubuntu/Debian
sudo apt-get install libomp-dev

# Fedora
sudo dnf install libgomp-devel
```

**Visual Studio not found (Windows)**
- Install Visual Studio 2019 or newer
- Run build script from "Developer Command Prompt"

**Low performance**
- Ensure Release build configuration
- Check CPU thermal throttling
- Verify OpenMP is enabled (`omp_get_max_threads()` > 1)

## About

**Almond Benchmark by JxThxNxs** is a specialized CPU benchmarking tool that combines performance testing with fractal visualization. Challenge your hardware and discover your Almond Score!

## License

This project is open source. Feel free to modify and distribute.

## Contributing

Contributions welcome! Areas for improvement:
- Additional color palettes
- Enhanced scoring algorithms
- Advanced fractal types
- Performance optimizations
- UI enhancements

---

**Test your CPU power with Almond Benchmark!** 🌰✨
