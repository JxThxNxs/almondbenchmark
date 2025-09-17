#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "mandelbrot.h"
#include "color_palette.h"
#include "fps_counter.h"

class Renderer {
public:
    Renderer(int width, int height, const std::string& title);
    ~Renderer();
    
    bool initialize();
    void shutdown();
    
    void clear();
    void present();
    
    void renderMandelbrot(const std::vector<int>& iterations, const MandelbrotParams& params, const ColorPalette& palette);
    void renderText(const std::string& text, int x, int y, Color color = Color(255, 255, 255));
    void renderFPSCounter(const FPSCounter& fps_counter);
    void renderBenchmarkInfo(double single_thread_time, double multi_thread_time, int thread_count);
    
    bool isRunning() const { return running_; }
    void setRunning(bool running) { running_ = running; }
    
    SDL_Event& getEvent() { return event_; }
    bool pollEvent() { return SDL_PollEvent(&event_) != 0; }
    
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    
private:
    void setPixel(int x, int y, const Color& color);
    void renderChar(char c, int x, int y, const Color& color);
    
    SDL_Window* window_;
    SDL_Renderer* sdl_renderer_;
    SDL_Texture* texture_;
    SDL_Event event_;
    
    std::vector<uint32_t> pixel_buffer_;
    
    int width_;
    int height_;
    bool running_;
    bool initialized_;
};
