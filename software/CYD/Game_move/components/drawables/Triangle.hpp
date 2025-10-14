#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#pragma once

#include "Drawable.hpp"
#include <cstdint> // for uint16_t

// Forward declaration
class Ili9341Display;

class Triangle : public Drawable {
public:
    Triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color, bool fill = false);
    void draw(Ili9341Display& display) const override;

private:
    int _x0, _y0, _x1, _y1, _x2, _y2;
    uint16_t _color;
    bool _fill;
};

#endif