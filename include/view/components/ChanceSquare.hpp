#pragma once
#include "BoardSquareComponent.hpp"

class ChanceSquare : public BoardSquareComponent {
private:
    void setTexts() override;
    sf::Color qmark_color;
public:
    ChanceSquare(const sf::Vector2f &pos, int id, BoardSide side, sf::Color color);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};
