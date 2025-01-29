#pragma once
#include "BoardSquare.hpp"

class IncomeTaxSquare : public BoardSquare {
private:
    void setTexts();

public:
    IncomeTaxSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::Bottom);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};
