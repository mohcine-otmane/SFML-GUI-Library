#ifndef TEXTAREA_HPP
#define TEXTAREA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>



extern sf::Font defaultFont; // Declared as external to use the defaultFont defined in main
extern sf::Vector2f defaultPadding; 
extern sf::Cursor cursor; // Global cursor



class textArea {
    public:
        textArea(sf::RenderWindow* window, float width, float height, sf::Vector2f position) {
            this->position = position;
            this->width = width;
            this->height = height;
            this->content.init("../../SF_LiB/fonts/HARNGTON.TTF", position);
            this->content.setText("Content of textArea");
            this->textareaShape.setSize(sf::Vector2f(width, height));
            this->textareaShape.setPosition(position);
        }

        std::string getContent() {
            return this->content.text.getString();
        }

        void setContent(std::string txt) {
            this->content.setText(txt);
        }

        void onHover(sf::RenderWindow* window, const sf::Color& hoverbgColor, const sf::Color& hoverColor) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (mousePos.x < this->width + this->position.x && mousePos.x > this->position.x &&
            mousePos.y < this->height + this->position.y && mousePos.y > this->position.y) {
            this->hovering = true;
            textareaShape.setFillColor(hoverbgColor);
            this->content.text.setFillColor(hoverColor);
            if (cursor.loadFromSystem(sf::Cursor::Text))
                window->setMouseCursor(cursor);
        } else {
            this->hovering = false;
            textareaShape.setFillColor(bgColor);
            this->content.text.setFillColor(color);
            if (cursor.loadFromSystem(sf::Cursor::Arrow))
                window->setMouseCursor(cursor);
        }
    }

    void draw(sf::RenderWindow* window, const sf::Event& event) {
        // this->width = content.text.getLocalBounds().width + this->padding.x;
        // this->height = 2 * content.text.getLocalBounds().height + this->padding.y;

        textareaShape.setSize(sf::Vector2f(this->width, this->height));
        textareaShape.setPosition(this->position);

        sf::FloatRect buttonBounds = textareaShape.getLocalBounds();
        sf::Vector2f buttonCenter(buttonBounds.left + buttonBounds.width / 2, buttonBounds.top + buttonBounds.height / 2);

        this->content.text.setPosition(this->position.x + textareaShape.getSize().x / 2, this->position.y + textareaShape.getSize().y / 2);
        sf::FloatRect textBounds = this->content.text.getLocalBounds();
        this->content.text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

        onHover(window, hoverbgColor, hoverColor);
        this->clicked = click(event);
        window->draw(this->textareaShape);
        window->draw(this->content.text);
    }

    bool click(const sf::Event& event) {
        return hovering && event.type == sf::Event::MouseButtonReleased;
    }

    private:
        float width;
        float height;
        sf::Vector2f padding = sf::Vector2f(0,0);
        sf::Vector2f position;
        Text content;
        sf::Texture* texture;
        sf::RectangleShape textareaShape;
        sf::Color bgColor = sf::Color(200, 200, 200);
        sf::Color hoverbgColor = sf::Color(255, 255, 255);
        sf::Color color = sf::Color(0, 0, 0);
        sf::Color hoverColor = sf::Color(0, 0, 0);
        bool hovering = false;
        bool clicked = false;
};



#endif