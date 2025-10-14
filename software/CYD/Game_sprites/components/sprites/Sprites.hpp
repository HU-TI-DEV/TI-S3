/*! \brief A sprites API
 *
 */
#pragma once
#include <cstdint>

namespace sprites {

// Minimal POD that any renderer can consume.
// pixels: RGB565 byte stream (little-endian), row-major, 2 bytes per pixel.
struct Sprite {
    uint16_t w;
    uint16_t h;
    const uint8_t* pixels; // RGB565, little-endian, row-major
};

// Declarations only
extern const Sprite Shark;
} 