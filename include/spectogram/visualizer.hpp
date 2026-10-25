#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "canvas.hpp"
#include "config.hpp"

class Visualizer {
private:
    sf::RenderWindow m_window;
    SpectogramCanvas m_canvas;

    tgui::Gui m_gui;
    tgui::Panel::Ptr m_sidebar;
    tgui::Button::Ptr m_sidebar_toggle;
    tgui::Label::Ptr m_statusbar;
    bool m_is_sidebar_open;
    float m_sidebar_width;
    float m_statusbar_height;
    bool m_ready = false; // true once init() has built all widgets
    bool m_in_native_resize = false;

    void draw_frame();
    void maximize();
    void update_layout();
    void render();
    void toggle_sidebar();
    void handle_event(const sf::Event& event);
public:
    Visualizer(const Config& config);
    ~Visualizer();

    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;

    void init(const Config& config);
    void loop();

    /// @brief Called from the native window proc while the user drags a resize edge. 
    /// 
    /// Needed because there isn't a way to cross-platform render/change layout while the window is resizing. Only afterwards.
    void on_native_resize();
};
