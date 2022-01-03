#pragma once

#include "types.h"

#include <array>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

namespace c8
{
    class Controller
    {
    public:
        Controller();

        void update();

        inline bool is_key_pressed(u8 index) const
        {
            return m_key_states[index];
        }

    private:
        std::unordered_map<u8, sf::Keyboard::Key> m_keys;
        std::array<bool, 16> m_key_states;
    };
}