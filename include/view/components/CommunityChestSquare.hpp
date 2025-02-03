#pragma once
#include "BoardSquareComponent.hpp"

class CommunityChestSquare : public BoardSquareComponent {
private:
    void setTexts() override;
    //chest, apparently Sprite instance
public:
    CommunityChestSquare(const sf::Vector2f &pos, int id, BoardSide side);

    void draw(sf::RenderWindow &window) override;

    bool handleEvent(const sf::Event &event) override;

    void updateView() override;
};
