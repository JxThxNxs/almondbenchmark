#include "mandelbrot.h"
#include <chrono>
#include <omp.h>
#include <algorithm>

MandelbrotCalculator::MandelbrotCalculator(int width, int height)
    : width_(width), height_(height), iterations_(width * height) {
}

int MandelbrotCalculator::mandelbrotIterations(std::complex<double> c, int max_iter) {
    std::complex<double> z(0.0, 0.0);
    int iter = 0;
    
    while (iter < max_iter && std::norm(z) <= 4.0) {
        z = z * z + c;
        ++iter;
    }
    
    return iter;
}

void MandelbrotCalculator::calculate(const MandelbrotParams& params) {
    double scale = 4.0 / params.zoom;
    double x_min = params.center_x - scale * 0.5;
    double y_min = params.center_y - scale * 0.5 * height_ / width_;
    double dx = scale / width_;
    double dy = scale / width_;
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            std::complex<double> c(x_min + x * dx, y_min + y * dy);
            iterations_[y * width_ + x] = mandelbrotIterations(c, params.max_iterations);
        }
    }
}

void MandelbrotCalculator::calculateParallel(const MandelbrotParams& params) {
    double scale = 4.0 / params.zoom;
    double x_min = params.center_x - scale * 0.5;
    double y_min = params.center_y - scale * 0.5 * height_ / width_;
    double dx = scale / width_;
    double dy = scale / width_;
    
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            std::complex<double> c(x_min + x * dx, y_min + y * dy);
            iterations_[y * width_ + x] = mandelbrotIterations(c, params.max_iterations);
        }
    }
}

double MandelbrotCalculator::benchmarkSingle(const MandelbrotParams& params, int runs) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < runs; ++i) {
        calculate(params);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    return static_cast<double>(duration.count()) / runs;
}

double MandelbrotCalculator::benchmarkParallel(const MandelbrotParams& params, int runs) {
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < runs; ++i) {
        calculateParallel(params);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    return static_cast<double>(duration.count()) / runs;
}
