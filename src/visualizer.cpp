#include <spectogram/visualizer.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Include native OS headers
#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    // Requires linking against X11: -lX11
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
#elif defined(__APPLE__)
    // Requires an Objective-C++ file (.mm) or linking Cocoa
    extern void maximizeMacWindow(sf::WindowHandle handle);
#endif

namespace {
    inline constexpr float UBAR_HEIGHT = 50.f;
    inline constexpr float SBAR_HEIGHT = 50.f;
}

void Visualizer::maximize() {
    sf::WindowHandle handle = m_window.getNativeHandle();

    #if defined(_WIN32)
        // Windows API native maximize
        ShowWindow(handle, SW_MAXIMIZE);
    #elif defined(__linux__)
        // X11 native maximize
        Display* display = XOpenDisplay(nullptr);
        if (display) {
            Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
            Atom wmMaxHorz = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
            Atom wmMaxVert = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

            XEvent xev;
            xev.type = ClientMessage;
            xev.xclient.window = handle;
            xev.xclient.message_type = wmState;
            xev.xclient.format = 32;
            xev.xclient.data.l[0] = 1; // 1 = _NET_WM_STATE_ADD
            xev.xclient.data.l[1] = wmMaxHorz;
            xev.xclient.data.l[2] = wmMaxVert;
            xev.xclient.data.l[3] = 1;

            XSendEvent(display, DefaultRootWindow(display), False,
                    SubstructureNotifyMask | SubstructureRedirectMask, &xev);
            XFlush(display);
            XCloseDisplay(display);
        }
    #elif defined(__APPLE__)
        // Call out to macOS Cocoa functionality if needed
        maximizeMacWindow(handle);
    #endif
}

bool Visualizer::init(const Config& config) {
    m_window.create(config.initial_winsize, "Spectogram");

    if (config.auto_maximize)
        maximize();

    update_layout();
    return true;
}

void Visualizer::loop() {
    while (m_window.isOpen()) {
        while (const std::optional event = m_window.pollEvent()) {
            // close window
            if (event->is<sf::Event::Closed>())
                m_window.close();
            
            // resize
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::FloatRect visible_area{{0.f, 0.f}, sf::Vector2f(resized->size)};
                m_window.setView(sf::View(visible_area));
                update_layout();
            }

            // key presses
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                // Quit
                if (key->code == sf::Keyboard::Key::Q && key->control)
                    m_window.close();
            }
        }

        m_window.clear(sf::Color::Black);
        draw();

        m_window.display();
    }
}

void SpectogramCanvas::update_layout(sf::Vector2f size, sf::Vector2f winsize) {
    const sf::Vector2f pos = {0, 0};
    m_bg.setPosition(pos);
    m_bg.setSize(size);
    m_bg.setFillColor(sf::Color::Yellow);

    m_view = sf::View(sf::FloatRect(pos, size));
    m_view.setViewport(sf::FloatRect(
        {pos.x / winsize.x, pos.y / winsize.y},
        {size.x / winsize.x, size.y / winsize.y}
    ));
}

void StatusBar::update_layout(sf::Vector2f winsize) {
    m_bg.setPosition({0, winsize.y - SBAR_HEIGHT});
    m_bg.setSize({winsize.x, SBAR_HEIGHT});
    m_bg.setFillColor(sf::Color::Red);
}
