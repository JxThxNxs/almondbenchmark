@echo off
REM Mandelbrot Benchmark - Windows Build Script
REM Supports both 32-bit and 64-bit builds with Visual Studio

echo Mandelbrot Benchmark - Windows Build Script
echo ==========================================

REM Check if we're in a Visual Studio command prompt
if "%VCINSTALLDIR%"=="" (
    echo Error: This script must be run from a Visual Studio Developer Command Prompt
    echo Please run one of the following:
    echo   - "Developer Command Prompt for VS 2019" or newer
    echo   - "x64 Native Tools Command Prompt for VS 2019" for 64-bit
    echo   - "x86 Native Tools Command Prompt for VS 2019" for 32-bit
    pause
    exit /b 1
)

REM Detect architecture from environment
if "%VSCMD_ARG_TGT_ARCH%"=="x64" (
    set BUILD_TYPE=64bit
    set CMAKE_GENERATOR=Visual Studio 16 2019
    set CMAKE_ARCH=-A x64
) else if "%VSCMD_ARG_TGT_ARCH%"=="x86" (
    set BUILD_TYPE=32bit
    set CMAKE_GENERATOR=Visual Studio 16 2019
    set CMAKE_ARCH=-A Win32
) else (
    echo Warning: Could not detect architecture, defaulting to 64-bit
    set BUILD_TYPE=64bit
    set CMAKE_GENERATOR=Visual Studio 16 2019
    set CMAKE_ARCH=-A x64
)

echo Building for Windows %BUILD_TYPE%...

REM Check for vcpkg (recommended way to install SDL2 on Windows)
if exist "C:\vcpkg\vcpkg.exe" (
    echo Found vcpkg, using it for SDL2...
    set CMAKE_TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
) else if exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo Found vcpkg at VCPKG_ROOT, using it for SDL2...
    set CMAKE_TOOLCHAIN=-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
) else (
    echo Warning: vcpkg not found. Please install SDL2 manually or install vcpkg.
    echo To install vcpkg and SDL2:
    echo   git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
    echo   cd C:\vcpkg
    echo   .\bootstrap-vcpkg.bat
    echo   .\vcpkg install sdl2:x64-windows sdl2:x86-windows
    set CMAKE_TOOLCHAIN=
)

REM Create build directory
set BUILD_DIR=build_windows_%BUILD_TYPE%
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Configure with CMake
cmake .. -G "%CMAKE_GENERATOR%" %CMAKE_ARCH% %CMAKE_TOOLCHAIN% ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX=../install_windows_%BUILD_TYPE%

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build
cmake --build . --config Release -j

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build completed successfully!
echo Executable: %BUILD_DIR%\bin\Release\mandelbrot_benchmark.exe
echo.
echo To install: cmake --build . --target install --config Release
echo To run: .\bin\Release\mandelbrot_benchmark.exe

pause
