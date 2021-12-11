#include "screen.h"

#include "constants.h"

namespace c8
{
    Screen::Screen()
    {
        m_pixels = std::make_unique<std::array<u8, PIXEL_COUNT * 4>>();

        // Create texture
        m_texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
        m_sprite.setTexture(m_texture);
        m_sprite.setScale(v2(WINDOW_SIZE_SCALING, WINDOW_SIZE_SCALING));

        // Fill screen with green pixels with zero opacity
        for(u32 i = 0; i < 4 * PIXEL_COUNT; i+= 4)
        {
            m_pixels->operator[](i + 0) = 0;
            m_pixels->operator[](i + 1) = 255;
            m_pixels->operator[](i + 2) = 0;
            m_pixels->operator[](i + 3) = 0;
        }

        update_texture();
    }

    void Screen::clear()
    {
        for(u32 i = 0; i < 4 * PIXEL_COUNT; i+= 4)
            m_pixels->operator[](i + 3) = 0;

        update_texture();
    }

    bool Screen::draw_from_array(const std::shared_ptr<Memory>& memory, u32 start_index, u8 n, u8 x, u8 y)
    {
        bool collision = false;

        // Loop through every byte
        for(u32 i = 0; i < n; i++)
        {
            u8 data = memory->get(start_index + i);
            u8 mask = 0x80;

            // Loop through every bit in the byte
            for(u32 j = 0; j < 8; j++)
            {
                u32 alpha_index = 4 * (
                    (x + j) % SCREEN_WIDTH + 
                    (y + i) * SCREEN_WIDTH
                ) + 3;
                
                // XOR the new pixel value with the old one
                bool old_pixel = static_cast<bool>(m_pixels->operator[](alpha_index));
                bool new_pixel = static_cast<bool>(data & mask);
                bool xor_result = old_pixel ^ new_pixel;
                m_pixels->operator[](alpha_index) = 255 * xor_result;

                // Check for collision
                if(old_pixel && new_pixel)
                    collision = true;

                mask >>= 1;
            }
        }

        update_texture();
        return collision;
    }

    void Screen::draw(std::shared_ptr<sf::RenderWindow>& window)
    {
        window->draw(m_sprite);
    }

    void Screen::update_texture()
    {
        m_image.create(SCREEN_WIDTH, SCREEN_HEIGHT, m_pixels->data());
        m_texture.loadFromImage(m_image);
    }
}