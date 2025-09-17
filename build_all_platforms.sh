#!/bin/bash

# Almond Benchmark - Multi-Platform Build Script
# Creates builds for all supported platforms

set -e

echo "Almond Benchmark - Multi-Platform Build Script"
echo "=============================================="

# Create release directories
mkdir -p releases/linux-64bit
mkdir -p releases/windows-32bit  
mkdir -p releases/windows-64bit

echo "Building Linux 64-bit..."
if [ ! -d "build_linux_64bit" ]; then
    mkdir build_linux_64bit
    cd build_linux_64bit
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cd ..
fi

cd build_linux_64bit
make -j$(nproc)
cd ..

# Copy Linux 64-bit build
cp build_linux_64bit/bin/mandelbrot_benchmark releases/linux-64bit/
echo "✓ Linux 64-bit build completed"

# Create Windows build instructions
cat > releases/windows-build-instructions.txt << 'EOF'
Windows Build Instructions for Almond Benchmark
==============================================

To build for Windows, you need:
1. Visual Studio 2019 or newer with C++ support
2. vcpkg for SDL2 dependencies

Setup vcpkg:
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install sdl2:x64-windows sdl2:x86-windows

For 64-bit Windows:
1. Open "x64 Native Tools Command Prompt for VS"
2. Run: build_windows.bat
3. Executable will be in: build_windows_64bit\bin\Release\mandelbrot_benchmark.exe

For 32-bit Windows:
1. Open "x86 Native Tools Command Prompt for VS"  
2. Run: build_windows.bat
3. Executable will be in: build_windows_32bit\bin\Release\mandelbrot_benchmark.exe

Note: Windows builds require the system to have Visual Studio and vcpkg installed.
EOF

# Create README for releases
cat > releases/README.txt << 'EOF'
Almond Benchmark by JxThxNxs - Release Files
==========================================

This package contains pre-built binaries for different platforms:

📁 linux-64bit/
   └── mandelbrot_benchmark    (Linux 64-bit executable)

📁 windows-32bit/
   └── (Windows 32-bit build - requires Visual Studio to compile)

📁 windows-64bit/  
   └── (Windows 64-bit build - requires Visual Studio to compile)

🎮 How to Run:
- Linux: ./mandelbrot_benchmark
- Windows: mandelbrot_benchmark.exe

🎯 Controls:
- Mouse: Click to zoom
- WASD: Pan around
- Q/E: Zoom out/in
- R: Reset view
- C: Change color palette
- Space: Toggle auto-zoom
- +/-: Adjust iterations
- B: Run benchmark
- ESC: Exit

🏆 Get your Almond Score and challenge your CPU!

For source code and build instructions, visit:
https://github.com/JxThxNxs/almond-benchmark

Created by JxThxNxs
EOF

# Create a simple launcher script for Linux
cat > releases/linux-64bit/run.sh << 'EOF'
#!/bin/bash
echo "Starting Almond Benchmark by JxThxNxs..."
./mandelbrot_benchmark
EOF

chmod +x releases/linux-64bit/run.sh
chmod +x releases/linux-64bit/mandelbrot_benchmark

echo ""
echo "Release package created in 'releases/' directory:"
echo "- Linux 64-bit: Ready to use"
echo "- Windows builds: Instructions provided (requires Visual Studio)"
echo ""
echo "Files ready for GitHub upload:"
ls -la releases/
echo ""
echo "To create a release archive:"
echo "tar -czf almond-benchmark-release.tar.gz releases/"
