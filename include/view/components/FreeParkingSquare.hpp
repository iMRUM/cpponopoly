#pragma once
#include "BoardSquare.hpp"

class FreeParkingSquare : public BoardSquare {
private:
    sf::Text FREE_text;
    sf::Text PARKING_text;
    void setTexts() override;

public:
    FreeParkingSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::TopLeft)
        : BoardSquare(pos, "FREE\nPARKING", id, side) {
        setTexts();
    }

    void draw(sf::RenderWindow &window) override;
    bool handleEvent(const sf::Event &event) override;
    void updateView() override;
};