#pragma once
#include "BoardSquare.hpp"

class JailSquare : public BoardSquare {
private:
    sf::Text JUST_text;
    sf::Text VISITING_text;
    void setTexts() override;
public:
    JailSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::BottomLeft): BoardSquare(pos, "IN\n\n\n\n\nJAIL",id, side) {
        setTexts();
    }

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};