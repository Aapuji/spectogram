#include <spectogram/visualizer.hpp>

bool Visualizer::init(const Config& config) {
    m_window.create(config.initial_winsize, "Spectogram");

    return true;
}

void Visualizer::loop() {
    while (m_window.isOpen()) {
        while (const std::optional event = m_window.pollEvent()) {
            // close window
            if (event->is<sf::Event::Closed>())
                m_window.close();
        }

        m_window.display();
    }
}
