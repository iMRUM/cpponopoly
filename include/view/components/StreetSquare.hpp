#pragma once
#include "BoardSquare.hpp"
#include <array>

enum class StreetEvents {
    Stepped,
    Acquired,
    HouseBuilt
};
class StreetSquare : public BoardSquare {
private:
    sf::RectangleShape color_band;
    sf::Color group_color;
    sf::Color owner_color;
    std::array<sf::RectangleShape, 4> house_shapes;
    sf::RectangleShape hotel_shape;
    int num_houses;
    void setColorBand();
public:
    StreetSquare(const sf::Vector2f &pos,
                 const std::string &name,
                 int id,
                 const sf::Color &color);

    void setHouses(int houses);
    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event) override;
    void updateView() override;
};