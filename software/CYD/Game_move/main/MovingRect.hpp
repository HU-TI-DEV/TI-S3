/*! \brief Moving Rectangle
*
* A sprite class that (1) owns its position/velocity, (2) updates its state with time (dt), (3) draws itself using existing display primitives.
*
*/
#pragma once

#include <cstdint>
#include "Entity.hpp"
#include "Ili9341Display.hpp"

class MovingRect final : public Entity {
public:
    MovingRect(float x, float y, int w, int h,
                         uint16_t color, float vx, float vy)
        : x_(x), y_(y), w_(w), h_(h), color_(color), vx_(vx), vy_(vy) {}

    void update(float dt, int screenW, int screenH) override;
    void draw(Ili9341Display& d) const override;

    // Optional getters/setters for debugging
    float x() const { return x_; }
    float y() const { return y_; }

private:
    float x_, y_;            // position (top-left)
    int   w_, h_;            // size
    uint16_t color_;         // RGB565
    float vx_, vy_;          // velocity (px/s)
};