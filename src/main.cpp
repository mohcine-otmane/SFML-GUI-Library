#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Default values
sf::Font defaultFont;
sf::Vector2f defaultPadding = sf::Vector2f(0,0);
sf::Cursor cursor;

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
        this->buttonLabel.init("fonts/ARIAL.TTF", position);
        this->buttonLabel.setText(label);

        buttonIcon = new sf::Texture();
        if (!buttonIcon->loadFromFile("GUI/button.png")) {
            std::cout << "Button icon not loaded" << std::endl;
        }
        this->buttonShape.setTexture(buttonIcon);

        this->color = sf::Color::White; // Default text color
    }

    void setBorderRadius(float radius) {
        // buttonShape.setRadius(radius); // Implementation not provided
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

        onHover(window, sf::Color(255, 0, 0), sf::Color(0, 255, 0));
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

private:
    float width = 100;
    float height = 50;
    sf::Vector2f padding = defaultPadding;
    std::string label;
    sf::Vector2f position;
    sf::Color bgColor = sf::Color(50, 50, 50);
    sf::Color color;
    sf::Color hoverColor = sf::Color(0, 0, 0);
    sf::RectangleShape buttonShape;
    Text buttonLabel;
    bool hovering = false;
    bool clicked = false;

    sf::Texture* buttonIcon;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 300), "Window");

    if (!defaultFont.loadFromFile("fonts/ARIAL.TTF")) {
        std::cout << "Default font not loaded" << std::endl;
    }

    Button btn("Click Me Now", sf::Vector2f(0, 0));
    btn.setPadding(20, 20);
    btn.setBorderRadius(30);

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
