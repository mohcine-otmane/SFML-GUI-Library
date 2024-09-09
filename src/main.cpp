#include <SFML/Graphics.hpp>
#include <iostream>



sf::Font font;


struct Text {
        void init(std::string fontPath, sf::Vector2f textPosition) {
            if(font.loadFromFile(fontPath)){
                this->text.setFont(this->font);
            } else {
                std::cout<<"Font not loaded"<<std::endl;
            }
            text.setPosition(textPosition);
        }
        void setText(std::string txt) {
            this->text.setString(txt);
        }

        sf::Text text;
        sf::Font font;
};


class Button {
    public:
        Button(std::string label, sf::Vector2f position) {
            this->label = label;
            this->position = position;
            this->buttonLabel.init("fonts/ARIAL.TTF", sf::Vector2f(position.x, position.y));
            this->buttonLabel.setText(label);

            this->width = buttonLabel.text.getLocalBounds().width;
            this->height = 2*buttonLabel.text.getLocalBounds().height;

            buttonShape.setSize(sf::Vector2f(this->width, this->height));
            buttonShape.setPosition(position);
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
            window->draw(this->buttonLabel.text);
        }

        // Extra settings

        void setPadding(float paddingX, float paddingY) {
            this->padding = sf::Vector2f(paddingX,paddingY);
            buttonShape.setSize(sf::Vector2f(this->width + this->padding.x, this->height + this->padding.y));
        }

    private:
        float width;
        float height;
        sf::Vector2f padding = sf::Vector2f(0,0);
        std::string label;
        bool state;
        sf::Vector2f position;
        sf::Color bgColor = sf::Color(50, 50, 50);
        sf::Color color;
        sf::RectangleShape buttonShape;
        Text buttonLabel;
};



int main() {
    sf::RenderWindow window(sf::VideoMode(300,300),"Window");
    



    Button btn("Click", sf::Vector2f(100,0));
    btn.setPadding(100,100);

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