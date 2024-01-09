#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "app window");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Handling event close" << std::endl;
            }
        }

        window.clear();

        // Draw the blue circle on the window
        window.draw(shape);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
