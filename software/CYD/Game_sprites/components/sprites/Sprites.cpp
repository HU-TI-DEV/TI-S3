/*! \brief Sprites implementation
 *
 */
#include "Sprites.hpp"

// We only need the raw arrays exported by the LVGL converter. https://lvgl.io/tools/imageconverter
// They are defined in C files (fish_01.c, etc.).
// No lvgl.h include is needed here.
extern "C" {
    extern const uint8_t shark_map[];     // from shark.c
}

namespace sprites {

// NOTE: widths/heights are copied from lv_image_dsc_t headers (LVGL v9).
// Format is RGB565 (2 bytes per pixel), little-endian.

// Shark
static constexpr uint16_t kSharkW = 104;
static constexpr uint16_t kSharkH = 49;

const Sprite Shark{ kSharkW, kSharkH, shark_map };

}