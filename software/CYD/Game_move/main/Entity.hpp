/*! \brief Headerfile for entity
*
* Minimal base for “things" in the world.
*
* Entity is an abstract interface with pure virtual functions and an inline defaulted destructor.
*/
#pragma once
#include <cstdint>

class Ili9341Display;

class Entity {
public:
    virtual ~Entity() = default;
    virtual void update(float dt, int screenW, int screenH) = 0;
    virtual void draw(Ili9341Display& d) const = 0;
};