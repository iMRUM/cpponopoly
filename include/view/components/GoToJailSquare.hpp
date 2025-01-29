#pragma once
#include "BoardSquare.hpp"

class GoToJailSquare : public BoardSquare {
private:
    sf::Text GO_TO_text;
    sf::Text JAIL_text;
    void setTexts();

public:
    GoToJailSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::TopRight)
        : BoardSquare(pos, "GO TO\nJAIL", id, side) {
        setTexts();
    }

    void draw(sf::RenderWindow &window) override;
    bool handleEvent(const sf::Event &event) override;
    void updateView() override;
};