#pragma once
#include "BoardSquare.hpp"

class RailroadSquare : public BoardSquare {
private:
    void setTexts();
    //railroad, apparently Sprite instance
public:
    RailroadSquare(const sf::Vector2f &pos, const std::string &name, int id, BoardSide side);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};

