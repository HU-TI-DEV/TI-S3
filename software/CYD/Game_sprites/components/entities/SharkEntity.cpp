/*! \brief Implementation for SharkEntity
 *
 *  
 */
#include "SharkEntity.hpp"
#include "Ili9341Display.hpp"
#include <cmath> // std::abs

void SharkEntity::update(float dt, int screenW, int screenH) {
    x_ += vx_ * dt;
    y_ += vy_ * dt;

    const int w = sprite_->w;
    const int h = sprite_->h;

    if (x_ < 0.0f)           { x_ = 0.0f;               vx_ =  std::abs(vx_); }
    if (x_ + w > screenW)    { x_ = float(screenW - w); vx_ = -std::abs(vx_); }
    if (y_ < 0.0f)           { y_ = 0.0f;               vy_ =  std::abs(vy_); }
    if (y_ + h > screenH)    { y_ = float(screenH - h); vy_ = -std::abs(vy_); }
}

void SharkEntity::draw(Ili9341Display& d) const {
    d.drawBitmapRGB565(int(x_), int(y_), sprite_->w, sprite_->h, sprite_->pixels);
}

void SharkEntity::onButton(Button b) {
    const float S = 20.0f;
    switch (b) {
        case Button::LEFT:  vx_ = -S; break;
        case Button::RIGHT: vx_ =  S; break;
        case Button::UP:    vy_ = -S; break;
        case Button::DOWN:  vy_ =  S; break;
        case Button::FIRE:  vx_ = 0.0f; vy_ = 0.0f; break;
        case Button::NONE:  break;
    }
}