#pragma once
#include "BoardSquare.hpp"

class GoSquare : public BoardSquare {
private:
    sf::Text GO_text;
    sf::Text collect_text;
    sf::Text salary_text;
    sf::Text as_you_pass_text;
    void setTexts() override;

public:
    GoSquare(const sf::Vector2f &pos, int id, BoardSide side = BoardSide::BottomRight)
        : BoardSquare(pos, "GO", id, side) {
        setTexts();
    }

    void draw(sf::RenderWindow &window) override;
    bool handleEvent(const sf::Event &event) override;
    void updateView() override;
};