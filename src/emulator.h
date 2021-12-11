#pragma once

#include "constants.h"
#include "memory.h"
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

    private:
        Memory m_memory;
        Screen m_screen;
        std::shared_ptr<sf::RenderWindow> m_window;

        // Temporary
        u32 test_x = 0, test_y = 0;
    };
}