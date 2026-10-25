#include <TGUI/TGUI.hpp>

#include <spectogram/canvas.hpp>

SpectogramCanvas::SpectogramCanvas() : m_texture{}, m_sprite{m_texture} {}

void SpectogramCanvas::update_layout(sf::Vector2f pos, sf::Vector2f size) {
    m_pos = pos;
    m_size = size;
    m_sprite.setPosition(m_pos);
    // todo: actually change size
}

void SpectogramCanvas::draw(sf::RenderWindow& win) {
    win.draw(m_sprite);
}

