#include <TGUI/TGUI.hpp>

#include <spectogram/canvas.hpp>

SpectogramCanvas::SpectogramCanvas(sf::Vector2u size)
    : m_size{size},
      m_texture{},
      m_image{},
      m_sprite{m_texture},
      m_canvas{tgui::CanvasSFML::create({
        static_cast<float>(size.x),
        static_cast<float>(size.y)
      })}
{}

void SpectogramCanvas::update_layout(sf::Vector2f pos, sf::Vector2f size) {
    // is this causing some problems?
    m_sprite.setPosition({0, 0});

    if (m_size.x > 0 && m_size.y > 0) {
        m_sprite.setScale({
            size.x / static_cast<float>(m_size.x),
            size.y / static_cast<float> (m_size.y)
        });
    }

    // m_sprite.setScale({size.x / static_cast<float>(m_size.x), size.y / static_cast<float>(m_size.y)});
}

void SpectogramCanvas::draw() {
    m_canvas->clear(sf::Color::Yellow);
    m_canvas->draw(m_sprite);
    m_canvas->display();
}

void SpectogramCanvas::update_plot(std::vector<uint8_t>& data) {
    m_image.resize(m_size, sf::Color::Yellow);
    if (!m_texture.loadFromImage(m_image))
        exit(1);
    
    m_texture.setSmooth(true);
}

tgui::CanvasSFML::Ptr SpectogramCanvas::widget() const {
    return m_canvas;
}
