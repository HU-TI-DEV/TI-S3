/*! \brief Implementation for MovingRect
 *
 *  
 */

#include "MovingRect.hpp"
#include <cmath>

void MovingRect::update(float dt, int screenW, int screenH) {
    // Integrate position with velocity using Euler method: pos = pos + velocity * dt https://en.wikipedia.org/wiki/Euler_method

    // Your code. Implement this function.
}

void MovingRect::draw(Ili9341Display& d) const {
    // Convert float position to integer pixel coordinates at draw time
    d.drawRectangle(static_cast<int>(x_), static_cast<int>(y_), w_, h_, color_, true);
}