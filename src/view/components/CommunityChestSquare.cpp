#include "../../../include/view/components/CommunityChestSquare.hpp"

CommunityChestSquare::CommunityChestSquare(const sf::Vector2f &pos,  int id, BoardSide side): BoardSquareComponent(
    pos, "Community\n    Chest", id, side) {
    setTexts();
}


void CommunityChestSquare::setTexts() {
    float nameCharSize = size.y * 0.10f;
    name_text.setString(name);
    name_text.setFont(font);
    name_text.setCharacterSize(static_cast<unsigned int>(nameCharSize));
    name_text.setFillColor(sf::Color::Black);
    name_text.setStyle(sf::Text::Bold);

    float instructionCharSize = size.y * 0.07f;
    lower_text.setString("      FOLLOW\nINSTRUCTIONS\n ON TOP CARD");
    lower_text.setFont(font);
    lower_text.setCharacterSize(static_cast<unsigned int>(instructionCharSize));
    lower_text.setFillColor(sf::Color::Black);
    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.05f));
            name_text.setRotation(0);
            name_text.setOrigin(name_text.getLocalBounds().width / 2, 0);

            lower_text.setPosition(position.x + (size.x * 0.5f), position.y + (size.y * 0.72f));
            lower_text.setRotation(0);
            lower_text.setOrigin(lower_text.getLocalBounds().width / 2, 0);
            break;

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


void CommunityChestSquare::draw(sf::RenderWindow &window) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(name_text);
    window.draw(lower_text);
    BoardSquareComponent::draw(window);
}

bool CommunityChestSquare::handleEvent(const sf::Event &event) {
    return false;
}

void CommunityChestSquare::updateView() {
}
