#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Button.hpp"
#include "include/textarea.hpp"

// Initialize global variables
sf::Font defaultFont;
sf::Vector2f defaultPadding = sf::Vector2f(0, 0);
sf::Cursor cursor;

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "Window");

    if (!defaultFont.loadFromFile("fonts/ARIAL.TTF")) {
        std::cout << "Default font not loaded" << std::endl;
    }

    Button btn("Click Me Now", sf::Vector2f(0, 0));
    btn.setPadding(20, 20);
    btn.setBorderRadius(30);

    textArea textarea(&window,200,200,sf::Vector2f(0,0));

    std::cout<<textarea.getContent()<<std::endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        if (btn.click(event)) {
            std::cout << "Clk" << std::endl;
        }

        btn.draw(&window, event);
        window.display();
    }

    return 0;
}
