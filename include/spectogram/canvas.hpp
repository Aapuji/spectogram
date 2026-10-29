#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SpectogramCanvas {
private:
    sf::Vector2u m_size; // size of the texture and image, not sprite
    int m_ratio = 1; // number of FFT windows per pixel column
    sf::Texture m_texture;
    sf::Image m_image;
    sf::Sprite m_sprite;
    tgui::CanvasSFML::Ptr m_canvas;
public:
    SpectogramCanvas(sf::Vector2u size);
    void update_layout(sf::Vector2f pos, sf::Vector2f size);
    void draw();
    void update_plot(std::vector<uint8_t>& data);
    tgui::CanvasSFML::Ptr widget() const;
};
