#pragma once

#include <SFML/Window.hpp>

struct Config {
    sf::VideoMode initial_winsize = sf::VideoMode::getDesktopMode(); // default fullscreen
};
