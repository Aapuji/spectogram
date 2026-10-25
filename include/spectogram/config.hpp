#pragma once

#include <SFML/Window.hpp>

struct Config {
    sf::VideoMode initial_winsize{{1280, 720}};
    bool auto_maximize = true;
    bool collapse_sidebar = false;
    float sidebar_width = 250.f;
    sf::Vector2f sidebar_toggle_size = {30.f, 30.f};
    float statusbar_height = 30.f;
};
