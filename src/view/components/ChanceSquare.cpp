#include "../../../include/view/components/ChanceSquare.hpp"


ChanceSquare::ChanceSquare(const sf::Vector2f &pos, int id, BoardSide side, sf::Color color): BoardSquare(
    pos, "CHANCE", id, side), qmark_color(color) {
    setTexts();
}

void ChanceSquare::setTexts() {
    float nameCharSize = size.y * 0.10f;
    name_text.setString(name);
    name_text.setFont(font);
    name_text.setCharacterSize(static_cast<unsigned int>(nameCharSize));
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    float qmarkSize = size.y * 0.45f;
    lower_text.setString("?");
    lower_text.setFont(font);
    lower_text.setCharacterSize(static_cast<unsigned int>(qmarkSize));
    lower_text.setFillColor(qmark_color);
    lower_text.setOutlineColor(sf::Color::Black);
    lower_text.setOutlineThickness(1.0f);

    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.1f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.05f));
            lower_text.setRotation(0);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Left:
            name_text.setPosition(position.x + (size.x * 0.9f), position.y + (size.y * 0.5f));
            name_text.setRotation(90);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.95f), position.y + (size.y * 0.5f));
            lower_text.setRotation(90);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Top:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.9f));
            name_text.setRotation(180);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.95f));
            lower_text.setRotation(180);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Right:
            name_text.setPosition(position.x + (size.x * 0.1f), position.y + (size.y * 0.5f));
            name_text.setRotation(270);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.05f), position.y + (size.y * 0.5f));
            lower_text.setRotation(270);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;
    }
}


void ChanceSquare::draw(sf::RenderWindow &window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(name_text);
    window.draw(lower_text);
}

bool ChanceSquare::handleEvent(const sf::Event &event) {
    return false;
}

void ChanceSquare::updateView() {
}
