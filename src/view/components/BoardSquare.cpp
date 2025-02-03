#include "../../../include/view/components/BoardSquare.hpp"

BoardSquare::BoardSquare(const sf::Vector2f &pos, const std::string &squareName, const int id,
                         const BoardSide side,
                         const sf::Color bg): SFComponent(pos), board_side(side), background_color(bg),
                                              name(squareName), square_id(id) {
    setupSize();
    initText();
    setBackground();
}

bool BoardSquare::isCornerSquare() {
    return board_side == BoardSide::BottomLeft ||
           board_side == BoardSide::BottomRight ||
           board_side == BoardSide::TopLeft ||
           board_side == BoardSide::TopRight;
}

void BoardSquare::setupSize() {
    if (isCornerSquare()) {
        this->setSize(sf::Vector2f(CORNER_SIZE, CORNER_SIZE));
    } else {
        switch (board_side) {
            case BoardSide::Bottom:
            case BoardSide::Top:
                this->setSize(sf::Vector2f(REGULAR_WIDTH, REGULAR_HEIGHT));
                break;
            case BoardSide::Left:
            case BoardSide::Right:
                this->setSize(sf::Vector2f(REGULAR_HEIGHT, REGULAR_WIDTH));
                break;
        }
    }
}

void BoardSquare::setBackground() {
    background.setPosition(position);
    background.setFillColor(background_color);
    background.setOutlineThickness(3.0f);
    background.setOutlineColor(sf::Color::Black);
    background.setSize(getSize());
}


void BoardSquare::initText() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font from assets/arial.ttf");
    }
    name_text.setFont(font);
    name_text.setFillColor(sf::Color::Black);
    //set text rotation:
    setTextRotation();
}

void BoardSquare::setTextRotation() {
    switch (board_side) {
        case BoardSide::Bottom:
            name_text.setRotation(0);
            break;
        case BoardSide::Left:
            name_text.setRotation(90);
            break;
        case BoardSide::Top:
            name_text.setRotation(180);
            break;
        case BoardSide::Right:
            name_text.setRotation(270);
            break;
        case BoardSide::BottomLeft:
            name_text.setRotation(45);
            break;
        case BoardSide::BottomRight:
            name_text.setRotation(315);
            break;
        case BoardSide::TopLeft:
            name_text.setRotation(135);
            break;
        case BoardSide::TopRight:
            name_text.setRotation(225);
            break;
    }
}
/*
void BoardSquare::setTextPosition() {
    //TODO,(TO BE DEPRECATED) generated by claude
    // Get text bounds for centering
    sf::FloatRect textBounds = name_text.getLocalBounds();

    if (isCornerSquare()) {
        // For corner squares, position text diagonally
        float centerX = position.x + CORNER_SIZE / 2;
        float centerY = position.y + CORNER_SIZE / 2;

        // Adjust based on which corner
        switch (board_side) {
            case BoardSide::BottomLeft:
                name_text.setPosition(centerX - textBounds.width / 2, centerY);
                break;
            case BoardSide::BottomRight:
                name_text.setPosition(centerX + textBounds.width / 2, centerY);
                break;
            case BoardSide::TopLeft:
                name_text.setPosition(centerX - textBounds.width / 2, centerY - textBounds.height);
                break;
            case BoardSide::TopRight:
                name_text.setPosition(centerX + textBounds.width / 2, centerY - textBounds.height);
                break;
        }
    } else {
        // For regular squares, center text based on side
        switch (board_side) {
            case BoardSide::Bottom:
                name_text.setPosition(
                    position.x + (size.x - textBounds.width) / 2,
                    position.y + TEXT_PADDING
                );
                break;
            case BoardSide::Top:
                name_text.setPosition(
                    position.x + (size.x + textBounds.width) / 2,
                    position.y + size.y - TEXT_PADDING
                );
                break;
            case BoardSide::Left:
            case BoardSide::Right:
                name_text.setPosition(
                    position.x + TEXT_PADDING,
                    position.y + (size.y + textBounds.width) / 2
                );
                break;
        }
    }
}
*/