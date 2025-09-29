/*! \brief Headerfile for creating a scene
*
*/
#pragma once

#include <cstdint>
#include "Entity.hpp"
#include "InputListener.hpp"

class Ili9341Display;

class Scene {
public:
    Scene();

    // Returns true if added, false if full
    bool add(Entity* e);

    void update(float dt, int screenW, int screenH);
    void draw(Ili9341Display& d) const;

    void setInputTarget(InputListener* t);
    void onButton(Button b);

private:
    static constexpr int kMaxEntities = 8; // tune for your game
    Entity* entities_[kMaxEntities];
    int count_;
    InputListener* inputTarget_;
};
