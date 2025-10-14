#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#pragma once

#include "Drawable.hpp"
#include <cstdint> // for uint16_t

// Forward declaration
class Ili9341Display;

class Rectangle : public Drawable {
public:
    Rectangle(int x, int y, int w, int h, uint16_t color, bool fill = false);
    void draw(Ili9341Display& display) const override;

protected:
    int _x, _y, _w, _h;
    uint16_t _color;
    bool _fill;
};

#endif