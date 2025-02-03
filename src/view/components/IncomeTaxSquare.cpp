#include "../../../include/view/components/IncomeTaxSquare.hpp"

void IncomeTaxSquare::setTexts() {
    float nameCharSize = size.y * 0.10f;
    name_text.setString(name);
    name_text.setFont(font);
    name_text.setCharacterSize(static_cast<unsigned int>(nameCharSize));
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    float taxCharSize = size.y * 0.07f;
    lower_text.setString("PAY 10%\n   OR\n  $1200");
    lower_text.setFont(font);
    lower_text.setCharacterSize(static_cast<unsigned int>(taxCharSize));
    lower_text.setFillColor(sf::Color::Black);
    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.12f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.52f));
            lower_text.setRotation(0);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;
        //TODO complete other sides for dynamic add even though in "real life" it exists only on bottom side
        case BoardSide::Left:
            name_text.setPosition(position.x + (size.x * 0.95f), position.y + (size.y * 0.5f));
            name_text.setRotation(90);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.28f), position.y + (size.y * 0.5f));
            lower_text.setRotation(90);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Top:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.95f));
            name_text.setRotation(180);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.28f));
            lower_text.setRotation(180);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

        case BoardSide::Right:
            name_text.setPosition(position.x + (size.x * 0.05f), position.y + (size.y * 0.5f));
            name_text.setRotation(270);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.72f), position.y + (size.y * 0.5f));
            lower_text.setRotation(270);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;
    }
}

IncomeTaxSquare::IncomeTaxSquare(const sf::Vector2f &pos, int id, BoardSide side): BoardSquareComponent(
    pos, "INCOME\n   TAX", id, side) {
    setTexts();
}

void IncomeTaxSquare::draw(sf::RenderWindow &window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(name_text);
    window.draw(lower_text);
    BoardSquareComponent::draw(window);
}

bool IncomeTaxSquare::handleEvent(const sf::Event &event) {
    return false;
}

void IncomeTaxSquare::updateView() {
}
