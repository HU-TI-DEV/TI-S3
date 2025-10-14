#pragma once

#include "Drawable.hpp"
#include <cstdint> // for uint16_t

// Forward declaration
class Ili9341Display;

class Line : public Drawable {
public:
    Line(int x0, int y0, int x1, int y1, uint16_t color);
    void draw(Ili9341Display& display) const override;

private:
    int _x0, _y0, _x1, _y1;
    uint16_t _color;
};