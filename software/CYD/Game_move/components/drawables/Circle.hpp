#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#pragma once

#include "Drawable.hpp"
#include <cstdint> // for uint16_t

// Forward declaration
class Ili9341Display;

class Circle : public Drawable {
public:
    Circle(int x, int y, int radius, uint16_t color, bool fill = false);
    void draw(Ili9341Display& display) const override;

private:
    int _x, _y, _radius;
    uint16_t _color;
    bool _fill;
};

#endif