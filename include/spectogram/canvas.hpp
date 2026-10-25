#pragma once

#include <SFML/Graphics.hpp>

class SpectogramCanvas {
private:
    sf::Vector2f m_pos;
    sf::Vector2f m_size;
    sf::Texture  m_texture;
    sf::Sprite   m_sprite;
public:
    SpectogramCanvas();
    void update_layout(sf::Vector2f pos, sf::Vector2f size);
    void draw(sf::RenderWindow& win);
};
