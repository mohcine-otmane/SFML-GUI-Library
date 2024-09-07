#include <SFML/Graphics.hpp>
#include <iostream>




class Tools {
    public:
        void getFont(std::string fontPath) {
            sf::Font font;
            if(!font.loadFromFile(fontPath)){
                std::cout<<"Font not loaded"<<std::endl;
            }
        }
        void drawText() {
            sf::Text text;
        }

};








class Button {
    public:
        Button(float width, float height, std::string label) {
            this->width = width;
            this->height = height;
            this->label = label;
            buttonShape.setSize(sf::Vector2f(width,height));
            buttonShape.setPosition(this->position);
        }


         void hover(sf::RenderWindow* window, sf::Color hoverbgColor, sf::Color hoverColor) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if(mousePos.x<width+position.x && mousePos.x>position.x && mousePos.y<height+position.y && mousePos.y>position.y) {
                buttonShape.setFillColor(hoverbgColor);
            } else {
                buttonShape.setFillColor(bgColor);
            }
        }

        void draw(sf::RenderWindow* window) {
            hover(window, sf::Color(255, 0,0), sf::Color(0, 255,0));
            window->draw(this->buttonShape);
        }

       


    private:
        float width;
        float height;
        std::string label;
        bool state;
        sf::Vector2f position;
        sf::Color bgColor = sf::Color(50, 50, 50);
        sf::Color color;
        sf::RectangleShape buttonShape;
};



int main() {
    sf::RenderWindow window(sf::VideoMode(300,300),"Window");
    

    Button btn(100.f,50.f, "Click");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255,255, 255));
        btn.draw(&window);
        window.display();
    }

    
   

    return 0;
}