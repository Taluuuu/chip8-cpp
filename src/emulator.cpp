#include "emulator.h"

namespace c8
{
    void Emulator::run()
    {
        init();

        // Main loop
        while(m_window->isOpen())
        {
            update();
            render();
        }
    }

    void Emulator::init()
    {
        // Create window
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "chip8-emu", sf::Style::Titlebar | sf::Style::Close);

        const u8 test_data[] = { 0b11110001 };
        m_screen.draw_from_array(&test_data[0], 1, 0, 0);
    }

    void Emulator::update()
    {
        // Poll events
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();
        }
    }

    void Emulator::render()
    {
        m_window->clear(sf::Color::Black);

        // Render the screen
        m_screen.render(m_window);

        m_window->display();
    }
}