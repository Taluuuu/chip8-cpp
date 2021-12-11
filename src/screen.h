#pragma once

#include "constants.h"
#include "memory.h"
#include "types.h"

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>

namespace c8
{
    class Screen
    {
    public:
        Screen();
        /**
         * @brief Draw n * 8 pixels from start_index with an x and y offset. Pixels are XORed onto the screen.
         * 
         * @param memory The memory to draw from
         * @param start_index The byte index in memory to start drawing from
         * @param n The number of bytes to draw
         * @param x Offset on the x-axis
         * @param y Offset on the y-axis
         */
        void draw_from_array(const Memory& memory, u32 start_index, u8 n, u8 x, u8 y);
        void draw(std::shared_ptr<sf::RenderWindow>& window);

    private:
        void update_texture();

    private:
        // Bitmap RGBA pixels
        std::unique_ptr<std::array<u8, PIXEL_COUNT * 4>> m_pixels;
        sf::Image   m_image;
        sf::Texture m_texture;
        sf::Sprite  m_sprite;
    };
}