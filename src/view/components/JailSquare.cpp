#include "../../../include/view/components/JailSquare.hpp"

void JailSquare::setTexts() {
    // Initialize "JUST" and "VISITING" texts with the same font as parent
    JUST_text.setFont(font);
    VISITING_text.setFont(font);

    // Set text properties
    JUST_text.setString("JUST");
    VISITING_text.setString("VISITING");

    JUST_text.setFillColor(sf::Color::Black);
    VISITING_text.setFillColor(sf::Color::Black);

    // Set character size relative to square size
    float charSize = CORNER_SIZE / 12.0f;  // Adjust this ratio as needed
    JUST_text.setCharacterSize(static_cast<unsigned int>(charSize));
    VISITING_text.setCharacterSize(static_cast<unsigned int>(charSize));

    // Position the texts at the bottom of the square
    // Get bounds for centering
    sf::FloatRect justBounds = JUST_text.getLocalBounds();
    sf::FloatRect visitingBounds = VISITING_text.getLocalBounds();

    // Position "JUST" text
    JUST_text.setPosition(
        position.x + (CORNER_SIZE - justBounds.width) / 2,
        position.y + CORNER_SIZE - TEXT_PADDING - visitingBounds.height - justBounds.height
    );

    // Position "VISITING" text below "JUST"
    VISITING_text.setPosition(
        position.x + (CORNER_SIZE - visitingBounds.width) / 2,
        position.y + CORNER_SIZE - TEXT_PADDING - visitingBounds.height
    );

    // Set the main "IN JAIL" text properties (handled by parent class)
    name_text.setString("IN\nJAIL");
    name_text.setCharacterSize(static_cast<unsigned int>(charSize * 1.2f));  // Slightly larger

    // Position the "IN JAIL" text in top-right corner at 45 degree angle
    sf::FloatRect jailBounds = name_text.getLocalBounds();
    float diagonalOffset = CORNER_SIZE / 6.0f;  // Adjust this for diagonal positioning
    name_text.setPosition(
        position.x + CORNER_SIZE - diagonalOffset,
        position.y + diagonalOffset
    );
}

void JailSquare::draw(sf::RenderWindow& window) {
    if (!isComponentVisible()) return;

    // Draw the background (parent's background)
    window.draw(background);

    // Draw all texts
    window.draw(name_text);
    window.draw(JUST_text);
    window.draw(VISITING_text);
}

bool JailSquare::handleEvent(const sf::Event& event) {
    if (!isComponentEnabled()) return false;

    // Handle any jail-specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void JailSquare::updateView() {
    // Update the view when the model changes
    // This might include updating colors or text based on game state
    // For now, this is empty as we haven't implemented the model yet
}