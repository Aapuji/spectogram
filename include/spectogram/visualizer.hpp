#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"

class Visualizer {
private:
    sf::RenderWindow m_window;

public:
    /// @brief  Initializes the window's properties.
    /// @return True if the window was successfully initialized. False if not.
    bool init(const Config& config);

    /// @brief Constitutes the window's event loop.
    void loop();
};
