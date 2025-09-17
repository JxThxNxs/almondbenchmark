#pragma once

#include <vector>
#include <cstdint>

struct Color {
    uint8_t r, g, b, a;
    
    Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

class ColorPalette {
public:
    enum PaletteType {
        CLASSIC,
        FIRE,
        OCEAN,
        RAINBOW,
        GRAYSCALE,
        ELECTRIC
    };
    
    ColorPalette(PaletteType type = CLASSIC, int size = 256);
    
    Color getColor(int iterations, int max_iterations) const;
    void setPaletteType(PaletteType type);
    
private:
    void generateClassic();
    void generateFire();
    void generateOcean();
    void generateRainbow();
    void generateGrayscale();
    void generateElectric();
    
    std::vector<Color> colors_;
    PaletteType current_type_;
};
