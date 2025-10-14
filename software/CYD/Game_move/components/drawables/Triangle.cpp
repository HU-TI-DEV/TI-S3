#include "Triangle.hpp"
#include "Ili9341Display.hpp"

Triangle::Triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color, bool fill)
    : _x0(x0), _y0(y0), _x1(x1), _y1(y1), _x2(x2), _y2(y2), _color(color), _fill(fill) {}

void Triangle::draw(Ili9341Display& display) const {
    display.drawTriangle(_x0, _y0, _x1, _y1, _x2, _y2, _color, _fill);
}