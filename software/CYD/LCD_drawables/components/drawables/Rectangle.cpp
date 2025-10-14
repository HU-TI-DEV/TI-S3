#include "Rectangle.hpp"
#include "Ili9341Display.hpp"

Rectangle::Rectangle(int x, int y, int w, int h, uint16_t color, bool fill)
    : _x(x), _y(y), _w(w), _h(h), _color(color), _fill(fill) {}

void Rectangle::draw(Ili9341Display& display) const {
    display.drawRectangle(_x, _y, _w, _h, _color, _fill);
}