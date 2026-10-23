#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"

class StatusBar {
private:
    sf::RectangleShape m_bg;
public:
    void update_layout(sf::Vector2f winsize);
    
    void draw(sf::RenderWindow& win) {
        win.draw(m_bg);
    }

    sf::Vector2f get_size() {
        return m_bg.getSize();
    }
};

class SpectogramCanvas {
private:
    sf::View m_view;
    sf::RectangleShape m_bg;
public:
    void update_layout(sf::Vector2f size, sf::Vector2f winsize);

    void draw(sf::RenderWindow& win) {
        win.draw(m_bg);
        // win.setView(m_view);
    }
};

class Visualizer {
private:
    sf::RenderWindow m_window;
    SpectogramCanvas m_canvas;
    StatusBar m_sbar;

    void maximize();
    void update_layout() {
        const sf::Vector2f winsize = static_cast<sf::Vector2f>(m_window.getSize());

        m_sbar.update_layout(winsize);
        const float bottom = m_sbar.get_size().y;

        m_canvas.update_layout({winsize.x, winsize.y - bottom}, winsize);
    }
    void draw() {
        m_sbar.draw(m_window);
        m_canvas.draw(m_window);
    }

public:
    /// @brief  Initializes the window's properties.
    /// @return True if the window was successfully initialized. False if not.
    bool init(const Config& config);

    /// @brief Constitutes the window's event loop.
    void loop();
};
