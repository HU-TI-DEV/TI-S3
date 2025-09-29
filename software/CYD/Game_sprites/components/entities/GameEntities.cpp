/*! \brief Implementation for Game Entities
 *
 *  
 */
#include "GameEntities.hpp"
#include "SharkEntity.hpp"
#include "Sprites.hpp" // for sprites::Shark

// Single static instance owned by this component (no heap).
static SharkEntity g_playerShark(sprites::Shark);

PlayerHandle acquirePlayerShark() {
    PlayerHandle h;
    h.entity = static_cast<Entity*>(&g_playerShark);
    h.input  = static_cast<InputListener*>(&g_playerShark);
    return h;
}

void centerPlayerShark(int screenW, int screenH) {
    const int w = sprites::Shark.w;
    const int h = sprites::Shark.h;
    const int x = (screenW - w) / 2;
    const int y = (screenH - h) / 2;
    g_playerShark.setPosition(float(x), float(y));
}

void initPlayerSharkPosition(int x, int y) {
    g_playerShark.setPosition(float(x), float(y));
}

void initPlayerSharkVelocity(float vx, float vy) {
    g_playerShark.setVelocity(vx, vy);
}
