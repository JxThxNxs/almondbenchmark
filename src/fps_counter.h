#pragma once

#include <chrono>
#include <deque>
#include <string>

class FPSCounter {
public:
    FPSCounter();
    
    void update();
    double getFPS() const { return current_fps_; }
    double getAverageFPS() const;
    double getMinFPS() const;
    double getMaxFPS() const;
    
    std::string getStatsString() const;
    
    void reset();
    
private:
    std::chrono::high_resolution_clock::time_point last_time_;
    std::deque<double> frame_times_;
    double current_fps_;
    
    static const size_t MAX_SAMPLES = 60; // Keep last 60 frame times
};
