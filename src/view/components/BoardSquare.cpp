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
void BoardSquare::addPlayer(int player_id) {
    players_present.insert(player_id);
}

void BoardSquare::removePlayer(int player_id) {
    players_present.erase(player_id);
}

void BoardSquare::clearPlayers() {
    players_present.clear();
}

bool BoardSquare::hasPlayer(int player_id) const {
    return players_present.find(player_id) != players_present.end();
}

sf::Vector2f BoardSquare::calculatePlayerPosition(size_t index) const {
    const float SQUARE_SIZE = background.getSize().x;
    const float DOT_SPACING = PLAYER_DOT_RADIUS * 2.5f;
    const float START_X = SQUARE_SIZE * 0.25f;
    const float START_Y = SQUARE_SIZE * 0.25f;

    // Calculate grid position (2x2 grid)
    size_t row = index / 2;
    size_t col = index % 2;

    return sf::Vector2f(
        background.getPosition().x + START_X + (col * DOT_SPACING),
        background.getPosition().y + START_Y + (row * DOT_SPACING)
    );
}

void BoardSquare::drawPlayers(sf::RenderWindow& window) {
    size_t index = 0;
    sf::CircleShape player_dot(PLAYER_DOT_RADIUS);
    sf::Text player_text;
    player_text.setFont(font);
    player_text.setCharacterSize(static_cast<unsigned int>(PLAYER_TEXT_SIZE));

    for (int player_id : players_present) {
        // Draw black dot
        sf::Vector2f pos = calculatePlayerPosition(index);
        player_dot.setFillColor(sf::Color::Black);
        player_dot.setPosition(pos);
        window.draw(player_dot);

        // Draw player ID
        player_text.setString(std::to_string(player_id));
        player_text.setFillColor(sf::Color::White);

        // Center text in dot
        sf::FloatRect textBounds = player_text.getLocalBounds();
        player_text.setPosition(
            pos.x + (PLAYER_DOT_RADIUS - textBounds.width/2),
            pos.y + (PLAYER_DOT_RADIUS - textBounds.height/2)
        );

        window.draw(player_text);
        index++;
    }
}

void BoardSquare::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(name_text);
    window.draw(lower_text);
    drawPlayers(window);
}

