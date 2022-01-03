#include "controller.h"

namespace c8
{
    Controller::Controller()
    {
        m_keys[0x0] = sf::Keyboard::Num0;
        m_keys[0x1] = sf::Keyboard::Num1;
        m_keys[0x2] = sf::Keyboard::Num2;
        m_keys[0x3] = sf::Keyboard::Num3;
        m_keys[0x4] = sf::Keyboard::Num4;
        m_keys[0x5] = sf::Keyboard::Num5;
        m_keys[0x6] = sf::Keyboard::Num6;
        m_keys[0x7] = sf::Keyboard::Num7;
        m_keys[0x8] = sf::Keyboard::Num8;
        m_keys[0x9] = sf::Keyboard::Num9;
        m_keys[0xA] = sf::Keyboard::A;
        m_keys[0xB] = sf::Keyboard::B;
        m_keys[0xC] = sf::Keyboard::C;
        m_keys[0xD] = sf::Keyboard::D;
        m_keys[0xE] = sf::Keyboard::E;
        m_keys[0xF] = sf::Keyboard::F;
    }

    void Controller::update()
    {
        for(i32 i = 0; i < 16; i++)
            m_key_states[i] = sf::Keyboard::isKeyPressed(m_keys[i]);
    }
}