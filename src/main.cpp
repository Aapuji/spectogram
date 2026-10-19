#include <iostream>
#include <SFML/Window.hpp>

int main() {
    std::cout << "START" << std::endl;

    sf::Window window(sf::VideoMode({800, 600}), "My window");

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // REQUIRED: Refresh and display the window contents
        window.display();
    }

    std::cout << "END" << std::endl;
}
