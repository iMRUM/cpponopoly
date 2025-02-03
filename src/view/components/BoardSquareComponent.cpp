#include "../../../include/view/components/BoardSquareComponent.hpp"

void BoardSquareComponent::draw(sf::RenderWindow &window) {
    drawPlayers(window);
}

void BoardSquareComponent::drawPlayers(sf::RenderWindow &window) {
    for (const auto &token: player_tokens) {
        token->draw(window);
    }
}

BoardSquareComponent::BoardSquareComponent(const sf::Vector2f &pos, const std::string &squareName, const int id,
                                           const BoardSide side,
                                           const sf::Color bg): SFComponent(pos), board_side(side),
                                                                background_color(bg),
                                                                name(squareName), square_id(id) {
    setupSize();
    initText();
    setBackground();
}

bool BoardSquareComponent::isCornerSquare() {
    return board_side == BoardSide::BottomLeft ||
           board_side == BoardSide::BottomRight ||
           board_side == BoardSide::TopLeft ||
           board_side == BoardSide::TopRight;
}

void BoardSquareComponent::setupSize() {
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

void BoardSquareComponent::setBackground() {
    background.setPosition(position);
    background.setFillColor(background_color);
    background.setOutlineThickness(3.0f);
    background.setOutlineColor(sf::Color::Black);
    background.setSize(getSize());
}


void BoardSquareComponent::initText() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font from assets/arial.ttf");
    }
    name_text.setFont(font);
    name_text.setFillColor(sf::Color::Black);
    //set text rotation:
    setTextRotation();
}

void BoardSquareComponent::setTextRotation() {
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

void BoardSquareComponent::addPlayer(int player_id) {
    player_tokens.push_back(
        std::make_unique<PlayerTokenComponent>(position, player_id)
    );
    repositionTokens();
}

void BoardSquareComponent::removePlayer(int player_id) {
    auto it = std::remove_if(player_tokens.begin(), player_tokens.end(),
                             [player_id](const auto &token) {
                                 return token->getPlayerId() == player_id;
                             });

    if (it != player_tokens.end()) {
        player_tokens.erase(it, player_tokens.end());
        repositionTokens();
    }
}

void BoardSquareComponent::clearPlayers() {
    player_tokens.clear();
}

void BoardSquareComponent::repositionTokens() {
    if (player_tokens.empty()) return;

    // Calculate total width needed for all tokens
    float token_diameter = PlayerTokenComponent::getTokenDiameter();
    float totalWidth = player_tokens.size() * token_diameter +
                       (player_tokens.size() - 1) * TOKEN_SPACING;

    // Calculate starting X position to center the tokens
    float startX = position.x + (getSize().x - totalWidth) / 2;
    // Y position is at bottom of square with padding
    float tokenY = position.y + getSize().y - token_diameter - TOKEN_BOTTOM_PADDING;

    // Update positions of all tokens
    for (size_t i = 0; i < player_tokens.size(); ++i) {
        player_tokens[i]->setPosition(sf::Vector2f(
            startX + i * (token_diameter + TOKEN_SPACING),
            tokenY
        ));
    }
}
