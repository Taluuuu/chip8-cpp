#pragma once

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
        void draw_from_array(const u8* start_index, u8 n, u8 x, u8 y);
        void render(std::shared_ptr<sf::RenderWindow>& window);

    private:
        std::unique_ptr<u8[]> m_pixels;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        const u32 m_pixel_count;
    };
}