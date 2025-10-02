#include "color_palette.h"
#include <cmath>
#include <algorithm>

ColorPalette::ColorPalette(PaletteType type, int size) : current_type_(type) {
    colors_.reserve(size);
    setPaletteType(type);
}

Color ColorPalette::getColor(int iterations, int max_iterations) const {
    if (iterations >= max_iterations) {
        return Color(0, 0, 0); // Black for points in the set
    }
    
    // Smooth coloring using continuous iteration count
    double smooth_iter = iterations + 1 - std::log2(std::log2(2.0));
    int index = static_cast<int>(smooth_iter * colors_.size() / max_iterations) % colors_.size();
    return colors_[std::max(0, std::min(static_cast<int>(colors_.size()) - 1, index))];
}

void ColorPalette::setPaletteType(PaletteType type) {
    current_type_ = type;
    colors_.clear();
    
    switch (type) {
        case CLASSIC: generateClassic(); break;
        case FIRE: generateFire(); break;
        case OCEAN: generateOcean(); break;
        case RAINBOW: generateRainbow(); break;
        case GRAYSCALE: generateGrayscale(); break;
        case ELECTRIC: generateElectric(); break;
    }
}

void ColorPalette::generateClassic() {
    for (int i = 0; i < 256; ++i) {
        double t = i / 255.0;
        uint8_t r = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::cos(3.0 + t * 6.28)));
        uint8_t g = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::cos(2.0 + t * 6.28)));
        uint8_t b = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::cos(1.0 + t * 6.28)));
        colors_.emplace_back(r, g, b);
    }
}

void ColorPalette::generateFire() {
    for (int i = 0; i < 256; ++i) {
        double t = i / 255.0;
        uint8_t r = static_cast<uint8_t>(255 * std::min(1.0, t * 2.0));
        uint8_t g = static_cast<uint8_t>(255 * std::max(0.0, std::min(1.0, (t - 0.3) * 2.0)));
        uint8_t b = static_cast<uint8_t>(255 * std::max(0.0, std::min(1.0, (t - 0.7) * 3.0)));
        colors_.emplace_back(r, g, b);
    }
}

void ColorPalette::generateOcean() {
    for (int i = 0; i < 256; ++i) {
        double t = i / 255.0;
        uint8_t r = static_cast<uint8_t>(255 * t * 0.3);
        uint8_t g = static_cast<uint8_t>(255 * (0.3 + t * 0.4));
        uint8_t b = static_cast<uint8_t>(255 * (0.5 + t * 0.5));
        colors_.emplace_back(r, g, b);
    }
}

void ColorPalette::generateRainbow() {
    for (int i = 0; i < 256; ++i) {
        double t = i / 255.0 * 6.0;
        int section = static_cast<int>(t);
        double fraction = t - section;
        
        uint8_t r = 0, g = 0, b = 0;
        
        switch (section % 6) {
            case 0: r = 255; g = static_cast<uint8_t>(255 * fraction); break;
            case 1: r = static_cast<uint8_t>(255 * (1 - fraction)); g = 255; break;
            case 2: g = 255; b = static_cast<uint8_t>(255 * fraction); break;
            case 3: g = static_cast<uint8_t>(255 * (1 - fraction)); b = 255; break;
            case 4: r = static_cast<uint8_t>(255 * fraction); b = 255; break;
            case 5: r = 255; b = static_cast<uint8_t>(255 * (1 - fraction)); break;
        }
        
        colors_.emplace_back(r, g, b);
    }
}

void ColorPalette::generateGrayscale() {
    for (int i = 0; i < 256; ++i) {
        uint8_t value = static_cast<uint8_t>(i);
        colors_.emplace_back(value, value, value);
    }
}

void ColorPalette::generateElectric() {
    for (int i = 0; i < 256; ++i) {
        double t = i / 255.0;
        uint8_t r = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::sin(t * 12.56)));
        uint8_t g = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::sin(t * 18.84 + 2.09)));
        uint8_t b = static_cast<uint8_t>(255 * (0.5 + 0.5 * std::sin(t * 25.12 + 4.18)));
        colors_.emplace_back(r, g, b);
    }
}
