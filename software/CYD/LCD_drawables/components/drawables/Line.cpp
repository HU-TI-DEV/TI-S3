#include "Line.hpp"
#include "Ili9341Display.hpp"

Line::Line(int x0, int y0, int x1, int y1, uint16_t color)
    : _x0(x0), _y0(y0), _x1(x1), _y1(y1), _color(color) {}

void Line::draw(Ili9341Display& display) const {
    display.drawLine(_x0, _y0, _x1, _y1, _color);
}