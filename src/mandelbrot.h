#pragma once

#include <complex>
#include <vector>
#include <cstdint>

struct MandelbrotParams {
    double center_x = -0.5;
    double center_y = 0.0;
    double zoom = 1.0;
    int max_iterations = 256;
    int width = 800;
    int height = 600;
};

class MandelbrotCalculator {
public:
    MandelbrotCalculator(int width, int height);
    
    void calculate(const MandelbrotParams& params);
    void calculateParallel(const MandelbrotParams& params);
    
    const std::vector<int>& getIterations() const { return iterations_; }
    
    // Benchmark methods
    double benchmarkSingle(const MandelbrotParams& params, int runs = 10);
    double benchmarkParallel(const MandelbrotParams& params, int runs = 10);
    
private:
    int mandelbrotIterations(std::complex<double> c, int max_iter);
    
    int width_;
    int height_;
    std::vector<int> iterations_;
};
