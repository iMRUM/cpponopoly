#pragma once
#include <functional>
#include <memory>
#include <string>
#include "UIComponent.hpp"

class Button : public UIComponent {
private:
    sf::RectangleShape background;
    sf::Text text;
    std::function<void()> onClick;

    sf::Color normalColor{sf::Color(100, 100, 100)};
    sf::Color hoverColor{sf::Color(150, 150, 150)};
    sf::Color clickedColor{sf::Color::Red};
    sf::Color disabledColor{sf::Color(70, 70, 70)};
    bool isHovered = false;
    bool isClicked = false;

public:
    Button(const sf::Vector2f& pos, const sf::Vector2f& sz,
           const std::string& label, std::shared_ptr<sf::Font> font);

    void setOnClick(std::function<void()> callback);
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void updateView() override { centerText(); }
private:
    void centerText();
};
