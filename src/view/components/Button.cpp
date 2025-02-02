#include "../../../include/view/components/Button.hpp"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& sz,
           const std::string& label, std::shared_ptr<sf::Font> font)
        : SFComponent(pos, sz) {
    background.setPosition(pos);
    background.setSize(sz);
    background.setFillColor(normalColor);

    text.setFont(*font);
    text.setString(label);
    text.setCharacterSize(20);
    centerText();
}

void Button::setOnClick(std::function<void()> callback) {
    onClick = std::move(callback);
}

void Button::draw(sf::RenderWindow &window) {
    if (!isVisible) return;
    window.draw(background);
    window.draw(text);
}

bool Button::handleEvent(const sf::Event &event) {
    if (!isEnabled || !isVisible) return false;

    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
        isHovered = contains(mousePos);
        if (!isClicked) {
            background.setFillColor(isHovered ? hoverColor : normalColor);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (contains(mousePos)) {
            isClicked = true;
            background.setFillColor(clickedColor);
            if (onClick) {
                onClick();
            }
            return true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isClicked = false;
        background.setFillColor(isHovered ? hoverColor : normalColor);
    }
    return false;

}

void Button::centerText() {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2
    );
}