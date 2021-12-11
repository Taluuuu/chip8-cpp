#pragma once

#include "types.h"

namespace c8
{
    static constexpr u32 SCREEN_WIDTH  = 64;
    static constexpr u32 SCREEN_HEIGHT = 32;
    static constexpr u32 PIXEL_COUNT = SCREEN_WIDTH * SCREEN_HEIGHT;

    static constexpr u32 WINDOW_SIZE_SCALING = 20;
    static constexpr u32 WINDOW_WIDTH  = SCREEN_WIDTH  * WINDOW_SIZE_SCALING;
    static constexpr u32 WINDOW_HEIGHT = SCREEN_HEIGHT * WINDOW_SIZE_SCALING;

    static constexpr u32 MEMORY_SIZE = 4096;
}