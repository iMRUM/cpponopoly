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
    name_text.setString(name);
    name_text.setFont(font);
    float nameCharSize = size.y * 0.10f; // 10% of height
    name_text.setCharacterSize(static_cast<unsigned int>(nameCharSize));
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    lower_text.setString(price);
    lower_text.setFont(font);
    float priceCharSize = size.y * 0.08f; // 8% of height
    lower_text.setCharacterSize(static_cast<unsigned int>(priceCharSize));
    lower_text.setFillColor(sf::Color::Black);

    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.32f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.8f));
            lower_text.setRotation(0);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Left:
            name_text.setPosition(position.x + (size.x * 0.68f), position.y + (size.y * 0.5f));
            name_text.setRotation(90);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.2f), position.y + (size.y * 0.5f));
            lower_text.setRotation(90);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Top:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.68f));
            name_text.setRotation(180);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.2f));
            lower_text.setRotation(180);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Right:
            name_text.setPosition(position.x + (size.x * 0.32f), position.y + (size.y * 0.5f));
            name_text.setRotation(270);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.8f), position.y + (size.y * 0.5f));
            lower_text.setRotation(270);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
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
    window.draw(lower_text);
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
