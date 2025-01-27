#include "../../../include/view/components/StreetSquare.hpp"

StreetSquare::StreetSquare(const sf::Vector2f &pos, const std::string &name, int id,
                           const sf::Color &color): BoardSquare(pos, sf::Vector2f(REGULAR_WIDTH, REGULAR_HEIGHT), name,
                                                                id),
                                                    group_color(color),
                                                    num_houses(0) {
    setColorBand();

    for (auto &house: house_shapes) {
        house.setSize(sf::Vector2f(12.f, 12.f));
        house.setFillColor(sf::Color::Green);
    }

    hotel_shape.setSize(sf::Vector2f(15.f, 15.f));
    hotel_shape.setFillColor(sf::Color::Red);

    // Update positions
    StreetSquare::updateView();
}

void StreetSquare::setColorBand() {
    sf::Vector2f colorBandSize(REGULAR_WIDTH, REGULAR_HEIGHT * 0.2f);
    color_band.setSize(colorBandSize);
    color_band.setFillColor(group_color);
    color_band.setOrigin(0, colorBandSize.y);

    // Set position based on board side
    switch (board_side) {
        case BoardSide::Bottom:
            color_band.setPosition(position.x, position.y + REGULAR_HEIGHT * 0.8f);
        color_band.setRotation(0);
        break;
        case BoardSide::Left:
            color_band.setPosition(position.x, position.y);
        color_band.setRotation(90);
        break;
        case BoardSide::Top:
            color_band.setPosition(position.x, position.y);
        color_band.setRotation(0);
        break;
        case BoardSide::Right:
            color_band.setPosition(position.x + REGULAR_HEIGHT, position.y);
        color_band.setRotation(90);
        break;
    }
}

void StreetSquare::setHouses(int houses) {
    num_houses = houses;
    updateView();
}

void StreetSquare::draw(sf::RenderWindow& window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(color_band);
    window.draw(text);

    if (num_houses == 5) {
        window.draw(hotel_shape);
    } else {
        for (int i = 0; i < num_houses; ++i) {
            window.draw(house_shapes[i]);
        }
    }
}

bool StreetSquare::handleEvent(const sf::Event &event) {
    return false;
}

void StreetSquare::updateView() {
}
