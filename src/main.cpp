#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/Button.hpp"
#include "include/textarea.hpp"

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

    textArea textarea(&window,300,200,sf::Vector2f(0,0));
    textarea.setContent("Text must wrap");

    // std::cout<<textarea.getContent()<<std::endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear();

        if (btn.click(event)) {
            std::cout << "Clk" << std::endl;
        }

        textarea.draw(&window,event);
        // btn.draw(&window, event);
        window.display();
    }

    return 0;
}
