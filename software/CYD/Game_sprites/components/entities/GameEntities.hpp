/*! \brief Handle all game entities
*
*/
#pragma once

#include "Entity.hpp"
#include "InputListener.hpp"

// Simple handle: pointers only, no ownership semantics.
struct PlayerHandle {
    Entity* entity;
    InputListener* input;
};

// Acquire a reference to the single, statically-allocated player Shark.
PlayerHandle acquirePlayerShark();

// Center player on the given screen size
void centerPlayerShark(int screenW, int screenH);

// Optional helpers to initialize the static player Shark.
void initPlayerSharkPosition(int x, int y);
void initPlayerSharkVelocity(float vx, float vy);
