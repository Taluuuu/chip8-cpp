#pragma once

#include "constants.h"
#include "interpreter.h"
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

        inline std::shared_ptr<Memory>& memory() { return m_memory; }
        inline std::shared_ptr<Screen>& screen() { return m_screen; }

    private:
        void init();
        void update();
        void render();

    private:
        std::shared_ptr<Memory> m_memory;
        std::shared_ptr<Screen> m_screen;
        std::shared_ptr<Interpreter> m_interpreter;
        std::shared_ptr<sf::RenderWindow> m_window;
    };
}