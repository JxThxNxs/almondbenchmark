#include "fps_counter.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

FPSCounter::FPSCounter() : current_fps_(0.0) {
    last_time_ = std::chrono::high_resolution_clock::now();
}

void FPSCounter::update() {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time_);
    
    double frame_time = duration.count() / 1000000.0; // Convert to seconds
    
    if (frame_time > 0.0) {
        current_fps_ = 1.0 / frame_time;
        
        frame_times_.push_back(frame_time);
        
        // Keep only the last MAX_SAMPLES frame times
        if (frame_times_.size() > MAX_SAMPLES) {
            frame_times_.pop_front();
        }
    }
    
    last_time_ = current_time;
}

double FPSCounter::getAverageFPS() const {
    if (frame_times_.empty()) return 0.0;
    
    double avg_frame_time = std::accumulate(frame_times_.begin(), frame_times_.end(), 0.0) / frame_times_.size();
    return avg_frame_time > 0.0 ? 1.0 / avg_frame_time : 0.0;
}

double FPSCounter::getMinFPS() const {
    if (frame_times_.empty()) return 0.0;
    
    auto max_frame_time = *std::max_element(frame_times_.begin(), frame_times_.end());
    return max_frame_time > 0.0 ? 1.0 / max_frame_time : 0.0;
}

double FPSCounter::getMaxFPS() const {
    if (frame_times_.empty()) return 0.0;
    
    auto min_frame_time = *std::min_element(frame_times_.begin(), frame_times_.end());
    return min_frame_time > 0.0 ? 1.0 / min_frame_time : 0.0;
}

std::string FPSCounter::getStatsString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "FPS: " << current_fps_;
    
    if (!frame_times_.empty()) {
        oss << " | Avg: " << getAverageFPS();
        oss << " | Min: " << getMinFPS();
        oss << " | Max: " << getMaxFPS();
    }
    
    return oss.str();
}

void FPSCounter::reset() {
    frame_times_.clear();
    current_fps_ = 0.0;
    last_time_ = std::chrono::high_resolution_clock::now();
}
