#include <iostream>
#include <thread>
#include <omp.h>
#include <iomanip>
#include "mandelbrot.h"
#include "renderer.h"
#include "color_palette.h"
#include "fps_counter.h"

class MandelbrotApp {
public:
    MandelbrotApp() : 
        params_{-0.5, 0.0, 1.0, 256, 800, 600},
        calculator_(params_.width, params_.height),
        renderer_(params_.width, params_.height, "Almond Benchmark by JxThxNxs"),
        palette_(ColorPalette::CLASSIC),
        current_palette_type_(0),
        auto_zoom_(false),
        zoom_speed_(1.02),
        single_thread_time_(0.0),
        multi_thread_time_(0.0),
        thread_count_(std::thread::hardware_concurrency()) {
    }
    
    bool initialize() {
        if (!renderer_.initialize()) {
            return false;
        }
        
        std::cout << "Almond Benchmark by JxThxNxs" << std::endl;
        std::cout << "Hardware threads: " << thread_count_ << std::endl;
        std::cout << "OpenMP threads: " << omp_get_max_threads() << std::endl;
        std::cout << "\nControls:" << std::endl;
        std::cout << "  Mouse: Click to zoom in at position" << std::endl;
        std::cout << "  WASD: Pan around" << std::endl;
        std::cout << "  Q/E: Zoom out/in" << std::endl;
        std::cout << "  R: Reset view" << std::endl;
        std::cout << "  C: Change color palette" << std::endl;
        std::cout << "  Space: Toggle auto-zoom" << std::endl;
        std::cout << "  +/-: Increase/decrease iterations" << std::endl;
        std::cout << "  B: Run benchmark" << std::endl;
        std::cout << "  ESC: Exit" << std::endl;
        
        // Initial calculation
        calculator_.calculateParallel(params_);
        runBenchmark();
        
        return true;
    }
    
    void run() {
        while (renderer_.isRunning()) {
            handleEvents();
            update();
            render();
            fps_counter_.update();
        }
    }
    
private:
    void handleEvents() {
        while (renderer_.pollEvent()) {
            SDL_Event& event = renderer_.getEvent();
            
            switch (event.type) {
                case SDL_QUIT:
                    renderer_.setRunning(false);
                    break;
                    
                case SDL_KEYDOWN:
                    handleKeyPress(event.key.keysym.sym);
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        handleMouseClick(event.button.x, event.button.y);
                    }
                    break;
            }
        }
    }
    
    void handleKeyPress(SDL_Keycode key) {
        bool recalculate = false;
        
        switch (key) {
            case SDLK_ESCAPE:
                renderer_.setRunning(false);
                break;
                
            case SDLK_w:
                params_.center_y -= 0.1 / params_.zoom;
                recalculate = true;
                break;
                
            case SDLK_s:
                params_.center_y += 0.1 / params_.zoom;
                recalculate = true;
                break;
                
            case SDLK_a:
                params_.center_x -= 0.1 / params_.zoom;
                recalculate = true;
                break;
                
            case SDLK_d:
                params_.center_x += 0.1 / params_.zoom;
                recalculate = true;
                break;
                
            case SDLK_q:
                params_.zoom /= 1.5;
                recalculate = true;
                break;
                
            case SDLK_e:
                params_.zoom *= 1.5;
                recalculate = true;
                break;
                
            case SDLK_r:
                params_.center_x = -0.5;
                params_.center_y = 0.0;
                params_.zoom = 1.0;
                params_.max_iterations = 256;
                recalculate = true;
                break;
                
            case SDLK_c:
                current_palette_type_ = (current_palette_type_ + 1) % 6;
                palette_.setPaletteType(static_cast<ColorPalette::PaletteType>(current_palette_type_));
                break;
                
            case SDLK_SPACE:
                auto_zoom_ = !auto_zoom_;
                std::cout << "Auto-zoom: " << (auto_zoom_ ? "ON" : "OFF") << std::endl;
                break;
                
            case SDLK_PLUS:
            case SDLK_EQUALS:
                params_.max_iterations = std::min(2048, params_.max_iterations + 32);
                recalculate = true;
                std::cout << "Iterations: " << params_.max_iterations << std::endl;
                break;
                
            case SDLK_MINUS:
                params_.max_iterations = std::max(32, params_.max_iterations - 32);
                recalculate = true;
                std::cout << "Iterations: " << params_.max_iterations << std::endl;
                break;
                
            case SDLK_b:
                runBenchmark();
                break;
        }
        
        if (recalculate) {
            calculator_.calculateParallel(params_);
        }
    }
    
    void handleMouseClick(int mouse_x, int mouse_y) {
        // Convert mouse coordinates to complex plane
        double scale = 4.0 / params_.zoom;
        double x_min = params_.center_x - scale * 0.5;
        double y_min = params_.center_y - scale * 0.5 * params_.height / params_.width;
        double dx = scale / params_.width;
        double dy = scale / params_.width;
        
        params_.center_x = x_min + mouse_x * dx;
        params_.center_y = y_min + mouse_y * dy;
        params_.zoom *= 2.0;
        
        calculator_.calculateParallel(params_);
    }
    
    void update() {
        if (auto_zoom_) {
            params_.zoom *= zoom_speed_;
            calculator_.calculateParallel(params_);
        }
    }
    
    void render() {
        renderer_.clear();
        renderer_.renderMandelbrot(calculator_.getIterations(), params_, palette_);
        renderer_.renderFPSCounter(fps_counter_);
        renderer_.renderBenchmarkInfo(single_thread_time_, multi_thread_time_, thread_count_);
        renderer_.present();
    }
    
    void runBenchmark() {
        std::cout << "\nRunning Almond Benchmark..." << std::endl;
        
        MandelbrotParams bench_params = params_;
        bench_params.max_iterations = 512; // Fixed iterations for consistent benchmarking
        
        // Single-threaded benchmark
        omp_set_num_threads(1);
        single_thread_time_ = calculator_.benchmarkSingle(bench_params, 3);
        
        // Multi-threaded benchmark
        omp_set_num_threads(thread_count_);
        multi_thread_time_ = calculator_.benchmarkParallel(bench_params, 3);
        
        double speedup = single_thread_time_ / multi_thread_time_;
        
        // Calculate Almond Score (higher is better)
        // Base score: 10000 / multi_thread_time (in ms)
        // Bonus for good parallelization efficiency
        double efficiency = speedup / thread_count_;
        double base_score = 10000.0 / multi_thread_time_;
        double efficiency_bonus = efficiency * 1000.0;
        almond_score_ = static_cast<int>(base_score + efficiency_bonus);
        
        std::cout << "Single-threaded: " << static_cast<int>(single_thread_time_) << " ms" << std::endl;
        std::cout << "Multi-threaded (" << thread_count_ << " threads): " << static_cast<int>(multi_thread_time_) << " ms" << std::endl;
        std::cout << "Speedup: " << std::fixed << std::setprecision(2) << speedup << "x" << std::endl;
        std::cout << "Efficiency: " << static_cast<int>(efficiency * 100) << "%" << std::endl;
        std::cout << "ALMOND SCORE: " << almond_score_ << " points" << std::endl;
        
        // Score rating
        std::string rating;
        if (almond_score_ >= 500) rating = "EXCELLENT!";
        else if (almond_score_ >= 300) rating = "VERY GOOD";
        else if (almond_score_ >= 200) rating = "GOOD";
        else if (almond_score_ >= 100) rating = "AVERAGE";
        else rating = "NEEDS IMPROVEMENT";
        
        std::cout << "Rating: " << rating << std::endl;
    }
    
    MandelbrotParams params_;
    MandelbrotCalculator calculator_;
    Renderer renderer_;
    ColorPalette palette_;
    FPSCounter fps_counter_;
    
    int current_palette_type_;
    bool auto_zoom_;
    double zoom_speed_;
    double single_thread_time_;
    double multi_thread_time_;
    int thread_count_;
    int almond_score_;
};

int main() {
    MandelbrotApp app;
    
    if (!app.initialize()) {
        std::cerr << "Failed to initialize application" << std::endl;
        return 1;
    }
    
    app.run();
    return 0;
}
