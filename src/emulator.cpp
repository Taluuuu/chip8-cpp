#include "emulator.h"

#include <iostream>

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
        std::cout << "[EMULATOR] Starting initialization." << std::endl;

        // Create window
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "chip8-emu", 
            sf::Style::Titlebar | sf::Style::Close);
        m_window->setVerticalSyncEnabled(true);

        // Create screen
        m_screen = std::make_shared<Screen>();

        // Create memory and load rom
        m_memory = std::make_shared<Memory>();
        m_memory->load_rom("../roms/fishie.ch8");

        // Create interpreter
        m_interpreter = std::make_shared<Interpreter>(*this);
        
        std::cout << "[EMULATOR] Finished initialization." << std::endl;
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

        m_interpreter->step();
    }

    void Emulator::render()
    {
        m_window->clear(sf::Color::Black);

        // Render the screen
        m_screen->draw(m_window);

        m_window->display();
    }
}