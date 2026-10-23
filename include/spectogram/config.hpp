#pragma once

#include <SFML/Window.hpp>

struct Config {
    sf::VideoMode initial_winsize = sf::VideoMode::getDesktopMode();
    bool auto_maximize = true;
    bool collapse_sidebar = false;
};
