#include "../../../include/view/components/UtilitySquare.hpp"

UtilitySquare::UtilitySquare(const sf::Vector2f &pos, const std::string &name, int id, BoardSide side): BoardSquare(
    pos, name, id, side) {
    setTexts();
}


void UtilitySquare::setTexts() {
    name_text.setString(name);
    name_text.setFont(font);
    name_text.setCharacterSize(23);
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    lower_text.setString("PRICE $150");
    lower_text.setFont(font);
    lower_text.setCharacterSize(19);
    lower_text.setFillColor(sf::Color::Black);
    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.05f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.85f));
            lower_text.setRotation(0);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Left:
            name_text.setPosition(position.x + (size.x * 0.95f), position.y + (size.y * 0.5f));
            name_text.setRotation(90);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.15f), position.y + (size.y * 0.5f));
            lower_text.setRotation(90);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Top:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.95f));
            name_text.setRotation(180);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.15f));
            lower_text.setRotation(180);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Right:
            name_text.setPosition(position.x + (size.x * 0.05f), position.y + (size.y * 0.5f));
            name_text.setRotation(270);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.85f), position.y + (size.y * 0.5f));
            lower_text.setRotation(270);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;
    }
}


void UtilitySquare::draw(sf::RenderWindow &window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(name_text);
    window.draw(lower_text);
}

bool UtilitySquare::handleEvent(const sf::Event &event) {
    return false;
}

void UtilitySquare::updateView() {
}
