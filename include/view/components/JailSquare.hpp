#pragma once
#include "BoardSquareComponent.hpp"

class JailSquare : public BoardSquareComponent {
private:
    sf::Text JUST_text;
    sf::Text VISITING_text;
    void setTexts() override;
public:
    JailSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::BottomLeft): BoardSquareComponent(pos, "IN\n\n\n\n\nJAIL",id, side) {
        setTexts();
    }

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};