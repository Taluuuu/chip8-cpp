#include "screen.h"

#include "emulator.h"

namespace c8
{
    Screen::Screen()
        :m_pixel_count(Emulator::C8_SCREEN_WIDTH * Emulator::C8_SCREEN_HEIGHT)
    {
        // Create pixel buffer
        m_pixels = std::make_unique<u8[]>(4 * m_pixel_count);

        // Create texture
        m_texture.create(Emulator::C8_SCREEN_WIDTH, Emulator::C8_SCREEN_HEIGHT);
        m_sprite.setTexture(m_texture);
        m_sprite.setScale(v2(Emulator::WINDOW_SIZE_SCALING, Emulator::WINDOW_SIZE_SCALING));

        // Fill screen with green pixels with zero opacity
        for(u32 i = 0; i < 4 * m_pixel_count; i+= 4)
        {
            m_pixels[i + 0] = 0;
            m_pixels[i + 1] = 255;
            m_pixels[i + 2] = 0;
            m_pixels[i + 3] = 0;
        }

        // Set texture pixels
        sf::Image img;
        img.create(Emulator::C8_SCREEN_WIDTH, Emulator::C8_SCREEN_HEIGHT, m_pixels.get());
        m_texture.loadFromImage(img);
    }

    void Screen::draw_from_array(const u8* start_index, u8 n, u8 x, u8 y)
    {
        // TODO: Figure out x and y offsets

        // Loop through every byte
        for(u32 i = 0; i < n; i++)
        {
            u8 data = *(start_index + i);
            u8 mask = 0x80;

            // Loop through every bit in the byte
            for(u32 j = 0; j < 8; j++)
            {
                u32 alpha_index = 4 * (i * 8 + j) + 3;
                // Logical or with the previous pixel value
                if(!(data & mask) != !m_pixels[alpha_index])
                {
                    m_pixels[alpha_index] = 255;
                }

                mask >>= 1;
            }
        }

        // Set texture pixels
        sf::Image img;
        img.create(Emulator::C8_SCREEN_WIDTH, Emulator::C8_SCREEN_HEIGHT, m_pixels.get());
        m_texture.loadFromImage(img);
    }

    void Screen::render(std::shared_ptr<sf::RenderWindow>& window)
    {
        window->draw(m_sprite);
    }
}