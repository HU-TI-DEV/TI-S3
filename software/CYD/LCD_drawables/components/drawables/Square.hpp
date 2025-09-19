#include "Rectangle.hpp"

class Square : public Rectangle {
public:
    Square(int x, int y, int size, uint16_t color, bool fill = false);
};
