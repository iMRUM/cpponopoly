#pragma once
#include "BoardSquareComponent.hpp"

class IncomeTaxSquare : public BoardSquareComponent {
private:
    void setTexts() override;

public:
    IncomeTaxSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::Bottom);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};
