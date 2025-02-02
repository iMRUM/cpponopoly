#pragma once
#include <functional>
#include <memory>
#include <string>
#include "SFComponent.hpp"

class MonopolyBoard : public SFComponent {
    sf::RectangleShape background;
    sf::RectangleShape logo_background;
    sf::Text logo_text;
    sf::Font font;

public:
    MonopolyBoard();
    ~MonopolyBoard() override;

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};
