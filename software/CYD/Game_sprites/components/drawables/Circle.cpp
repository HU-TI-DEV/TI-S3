#include "Circle.hpp"
#include "Ili9341Display.hpp"

Circle::Circle(int x, int y, int radius, uint16_t color, bool fill)
    : _x(x), _y(y), _radius(radius), _color(color), _fill(fill) {}

void Circle::draw(Ili9341Display& display) const {
    display.drawCircle(_x, _y, _radius, _color, _fill);
}