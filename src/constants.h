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

    static constexpr u32 MEMORY_SIZE = 0xFFF;
    static constexpr u32 PROGRAM_START = 0x200;
    static constexpr u32 MAX_PROGRAM_SIZE = MEMORY_SIZE - PROGRAM_START;
}