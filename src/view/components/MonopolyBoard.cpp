#include "../../../include/view/components/MonopolyBoard.hpp"

MonopolyBoard::MonopolyBoard(): UIComponent(sf::Vector2f(0,0),
                   sf::Vector2f(REGULAR_WIDTH*9.0f + 2.0f*CORNER_SIZE,
                               REGULAR_WIDTH*9.0f + 2.0f*CORNER_SIZE)) {
    background.setPosition(position);
    background.setFillColor(sf::Color(210, 230, 210));
    background.setOutlineThickness(3.0f);
    background.setOutlineColor(sf::Color::Black);
    background.setSize(size);

    // Setup logo background
    logo_background.setSize(sf::Vector2f(500.f, 100.f));
    logo_background.setPosition(sf::Vector2f(
        position.x + (size.x - 500.f) / 2,
        position.y + (size.y - 100.f) / 2
    ));
    logo_background.setFillColor(sf::Color::Red);
    logo_background.setOutlineThickness(2.0f);
    logo_background.setOutlineColor(sf::Color::White);

    // Setup logo text
    if (!font.loadFromFile("../../assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    logo_text.setFont(font);
    logo_text.setString("M O N O P O L Y");
    logo_text.setCharacterSize(60);
    logo_text.setFillColor(sf::Color::White);
    logo_text.setStyle(sf::Text::Bold);

    // Center the text
    sf::FloatRect textBounds = logo_text.getLocalBounds();
    logo_text.setOrigin(textBounds.width/2, textBounds.height/2);
    logo_text.setPosition(
        logo_background.getPosition().x + 250.f,
        logo_background.getPosition().y + 40.f
    );
}

MonopolyBoard::~MonopolyBoard() = default;

void MonopolyBoard::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(logo_background);
    window.draw(logo_text);
}

bool MonopolyBoard::handleEvent(const sf::Event &event) {
    return true;
}

void MonopolyBoard::updateView() {
}
