#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"

class UtilityBar {
private:
    sf::RectangleShape m_bg;
public:
    void update_layout(sf::Vector2f winsize);

    sf::Vector2f get_size() {
        return m_bg.getSize();
    }
};

class StatusBar {
private:
    sf::RectangleShape m_bg;
public:
    void update_layout(sf::Vector2f winsize);

    sf::Vector2f get_size() {
        return m_bg.getSize();
    }
};

class SpectogramCanvas {
private:
    sf::View m_view;
    sf::RectangleShape m_bg;
public:
    void update_layout(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f winsize);
};

class Visualizer {
private:
    sf::RenderWindow m_window;
    SpectogramCanvas m_canvas;
    UtilityBar m_ubar;
    StatusBar m_sbar;

    void maximize();
    void update_layout() {
        const sf::Vector2f winsize = static_cast<sf::Vector2f>(m_window.getSize());

        m_ubar.update_layout(winsize);
        m_sbar.update_layout(winsize);

        m_canvas.update_layout(
            {0, winsize.y + m_ubar.get_size().y},
            {winsize.x, winsize.y - m_ubar.get_size().y - m_sbar.get_size().y},
            winsize
        );
    }
public:
    /// @brief  Initializes the window's properties.
    /// @return True if the window was successfully initialized. False if not.
    bool init(const Config& config);

    /// @brief Constitutes the window's event loop.
    void loop();
};
