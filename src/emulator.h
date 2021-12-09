#pragma once

#include "screen.h"
#include "types.h"

#include <memory>
#include <SFML/Graphics.hpp>

namespace c8
{
    class Emulator
    {
    public:
        void run();

    private:
        void init();
        void update();
        void render();

    public:
        static constexpr u32 C8_SCREEN_WIDTH  = 64;
        static constexpr u32 C8_SCREEN_HEIGHT = 32;
        static constexpr u32 WINDOW_SIZE_SCALING = 20;
        static constexpr u32 WINDOW_WIDTH  = C8_SCREEN_WIDTH  * WINDOW_SIZE_SCALING;
        static constexpr u32 WINDOW_HEIGHT = C8_SCREEN_HEIGHT * WINDOW_SIZE_SCALING;

    private:
        Screen m_screen;
        std::shared_ptr<sf::RenderWindow> m_window;
    };
}