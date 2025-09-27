/*! \brief Shark Entity
*
* A sprite class that (1) owns its position/velocity, (2) updates its state with time (dt), (3) draws itself using existing display primitives.
* Added with onButton method. The MovingRect is now obsolete it is replaced by this SharkEntity (player).
*/
#pragma once
#include "Entity.hpp"
#include "InputListener.hpp"
#include "Sprites.hpp"   // sprites::Sprite

class SharkEntity : public Entity, public InputListener {
public:
    // Single-argument constructor keeps GameEntities simple (no need for screen size here).
    explicit SharkEntity(const sprites::Sprite& sprite)
    : sprite_(&sprite), x_(0.0f), y_(0.0f), vx_(80.0f), vy_(50.0f) {}

    void setPosition(float x, float y) { x_ = x; y_ = y; }
    void setVelocity(float vx, float vy) { vx_ = vx; vy_ = vy; }

    // Entity
    void update(float dt, int screenW, int screenH) override;
    void draw(Ili9341Display& d) const override;

    // InputListener
    void onButton(Button b) override;

private:
    const sprites::Sprite* sprite_;
    float x_;
    float y_;
    float vx_;
    float vy_;
};
