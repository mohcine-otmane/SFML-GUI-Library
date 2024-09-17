#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

extern sf::Font defaultFont; // Declared as external to use the defaultFont defined in main
extern sf::Vector2f defaultPadding; 
extern sf::Cursor cursor; // Global cursor

struct Text {
    void init(const std::string& fontPath, const sf::Vector2f& textPosition) {
        if (font.loadFromFile(fontPath)) {
            this->text.setFont(this->font);
        } else {
            std::cout << "Font not loaded" << std::endl;
            this->text.setFont(defaultFont);
        }
        sf::FloatRect rc = text.getLocalBounds();
        text.setOrigin(rc.width / 2, rc.height / 2);
        text.setPosition(textPosition);
    }
    void setText(const std::string& txt) {
        this->text.setString(txt);
    }

    sf::Text text;
    sf::Font font;
};

class Button {
public:
    Button(const std::string& label, const sf::Vector2f& position) {
        this->label = label;
        this->position = position;
        this->buttonLabel.init("../../SF_LiB/fonts/HARNGTON.TTF", position);
        this->buttonLabel.setText(label);

        buttonIcon = new sf::Texture();
        if (!buttonIcon->loadFromFile("../../SF_LiB/GUI/button.png")) {
            std::cout << "Button icon not loaded" << std::endl;
        }
        this->buttonShape.setTexture(buttonIcon);

        this->color = sf::Color::White;
    }

    void setBorderRadius(float radius) {
        // For rounded buttons
    }

    void onHover(sf::RenderWindow* window, const sf::Color& hoverbgColor, const sf::Color& hoverColor) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (mousePos.x < this->width + this->position.x && mousePos.x > this->position.x &&
            mousePos.y < this->height + this->position.y && mousePos.y > this->position.y) {
            this->hovering = true;
            buttonShape.setFillColor(hoverbgColor);
            this->buttonLabel.text.setFillColor(hoverColor);
            if (cursor.loadFromSystem(sf::Cursor::Hand))
                window->setMouseCursor(cursor);
        } else {
            this->hovering = false;
            buttonShape.setFillColor(bgColor);
            this->buttonLabel.text.setFillColor(color);
            if (cursor.loadFromSystem(sf::Cursor::Arrow))
                window->setMouseCursor(cursor);
        }
    }

    bool click(const sf::Event& event) {
        return hovering && event.type == sf::Event::MouseButtonReleased;
    }

    void draw(sf::RenderWindow* window, const sf::Event& event) {
        this->width = buttonLabel.text.getLocalBounds().width + this->padding.x;
        this->height = 2 * buttonLabel.text.getLocalBounds().height + this->padding.y;

        buttonShape.setSize(sf::Vector2f(this->width, this->height));
        buttonShape.setPosition(this->position);

        sf::FloatRect buttonBounds = buttonShape.getLocalBounds();
        sf::Vector2f buttonCenter(buttonBounds.left + buttonBounds.width / 2, buttonBounds.top + buttonBounds.height / 2);

        this->buttonLabel.text.setPosition(this->position.x + buttonShape.getSize().x / 2, this->position.y + buttonShape.getSize().y / 2);
        sf::FloatRect textBounds = this->buttonLabel.text.getLocalBounds();
        this->buttonLabel.text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

        onHover(window, hoverbgColor, hoverColor);
        this->clicked = click(event);
        window->draw(this->buttonShape);
        window->draw(this->buttonLabel.text);
    }

    void setPadding(float paddingX, float paddingY) {
        this->padding = sf::Vector2f(paddingX, paddingY);
        this->width = buttonLabel.text.getLocalBounds().width + paddingX;
        this->height = 2 * buttonLabel.text.getLocalBounds().height + paddingY;

        buttonShape.setSize(sf::Vector2f(this->width + this->padding.x, this->height + this->padding.y));

        this->buttonLabel.text.setPosition(this->position.x + buttonShape.getSize().x / 2, this->position.y + buttonShape.getSize().y / 2);
    }

    ~Button() {
        delete buttonIcon; // Clean up dynamic memory
    }

private:
    float width = 100;
    float height = 50;
    float borderradius[4] = {0, 0, 0, 0};
    sf::Vector2f padding = defaultPadding;
    std::string label;
    sf::Vector2f position;
    sf::Color bgColor = sf::Color(200, 200, 200);
    sf::Color hoverbgColor = sf::Color(255, 255, 255);
    sf::Color color = sf::Color(200, 200, 200);
    sf::Color hoverColor = sf::Color(255, 255, 255);
    sf::RectangleShape buttonShape;
    Text buttonLabel;
    bool hovering = false;
    bool clicked = false;

    sf::Texture* buttonIcon;
};

#endif
