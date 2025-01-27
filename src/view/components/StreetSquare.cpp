#include "../../../include/view/components/StreetSquare.hpp"

StreetSquare::StreetSquare(const sf::Vector2f &pos, const std::string &name, int id, const std::string &cost,
                           const sf::Color &color, BoardSide side): BoardSquare(
                                                                        pos,
                                                                        name, id, side), group_color(color),
                                                                    price("price: " + cost + "$"),
                                                                    num_houses(0) {
    setColorBand();
    setTexts();
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
    sf::Vector2f colorBandSize;
    switch (board_side) {
        case BoardSide::Bottom:
            color_band.setPosition(position.x, position.y);
            color_band.setSize(sf::Vector2f(size.x, size.y * 0.3f));
            break;
        case BoardSide::Left:
            color_band.setPosition(position.x + size.x * 0.7f, position.y);
            color_band.setSize(sf::Vector2f(size.x * 0.3f, size.y));
            break;
        case BoardSide::Top:
            color_band.setPosition(position.x, position.y + size.y * 0.7f);
            color_band.setSize(sf::Vector2f(size.x, size.y * 0.3f));
            break;
        case BoardSide::Right:
            color_band.setPosition(position.x, position.y);
            color_band.setSize(sf::Vector2f(size.x * 0.3f, size.y));
            break;
    }
    color_band.setFillColor(group_color);
    color_band.setOutlineThickness(3.0f);
    color_band.setOutlineColor(sf::Color::Black);
}

void StreetSquare::setTexts() {
    name_text.setString(getName());
    name_text.setFont(font);
    name_text.setCharacterSize(18);
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    price_text.setString(price);
    price_text.setFont(font);
    price_text.setCharacterSize(20);
    price_text.setFillColor(sf::Color::Black);

    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.35f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            price_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.85f));
            price_text.setRotation(0);
            price_text.setOrigin(price_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Left:
            name_text.setPosition(position.x + (size.x * 0.65f), position.y + (size.y * 0.5f));
            name_text.setRotation(90);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            price_text.setPosition(position.x + (size.x * 0.15f), position.y + (size.y * 0.5f));
            price_text.setRotation(90);
            price_text.setOrigin(price_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Top:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.65f));
            name_text.setRotation(180);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            price_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.15f));
            price_text.setRotation(180);
            price_text.setOrigin(price_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Right:
            name_text.setPosition(position.x + (size.x * 0.35f), position.y + (size.y * 0.5f));
            name_text.setRotation(270);
        name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            price_text.setPosition(position.x + (size.x * 0.85f), position.y + (size.y * 0.5f));
            price_text.setRotation(270);
            price_text.setOrigin(price_text.getLocalBounds().width / 2, 0);
            break;
    }
}

void StreetSquare::setHouses(int houses) {
    num_houses = houses;
    updateView();
}

void StreetSquare::draw(sf::RenderWindow &window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(color_band);
    window.draw(name_text);
    window.draw(price_text);
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
