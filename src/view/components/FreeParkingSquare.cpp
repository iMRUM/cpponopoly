#include "../../../include/view/components/FreeParkingSquare.hpp"

void FreeParkingSquare::setTexts() {
    // Initialize "FREE" and "PARKING" texts with the same font as parent
    FREE_text.setFont(font);
    PARKING_text.setFont(font);

    // Set text properties
    FREE_text.setString("FREE");
    PARKING_text.setString("PARKING");

    FREE_text.setFillColor(sf::Color::Black);
    PARKING_text.setFillColor(sf::Color::Black);

    // Set character size relative to square size
    float charSize = CORNER_SIZE / 12.0f;  // Adjust this ratio as needed
    FREE_text.setCharacterSize(static_cast<unsigned int>(charSize));
    PARKING_text.setCharacterSize(static_cast<unsigned int>(charSize));

    // Position the texts diagonally across the square
    sf::FloatRect freeBounds = FREE_text.getLocalBounds();
    sf::FloatRect parkingBounds = PARKING_text.getLocalBounds();

    // Calculate diagonal positioning
    float diagonalOffset = CORNER_SIZE / 6.0f;

    // Position "FREE" text at top-left
    FREE_text.setPosition(
        position.x + diagonalOffset,
        position.y + diagonalOffset
    );
    FREE_text.setRotation(45);  // Rotate to match diagonal layout

    // Position "PARKING" text below "FREE"
    PARKING_text.setPosition(
        position.x + diagonalOffset + freeBounds.width / 2.0f,
        position.y + diagonalOffset + freeBounds.height + TEXT_PADDING
    );
    PARKING_text.setRotation(45);  // Rotate to match diagonal layout

    // Set main text properties (using parent's name_text)
    name_text.setCharacterSize(0);  // Hide the parent's name_text as we're using our own layout
}

void FreeParkingSquare::draw(sf::RenderWindow& window) {
    if (!isComponentVisible()) return;

    // Draw the background (parent's background)
    window.draw(background);

    // Draw the texts
    window.draw(FREE_text);
    window.draw(PARKING_text);
}

bool FreeParkingSquare::handleEvent(const sf::Event& event) {
    if (!isComponentEnabled()) return false;

    // Handle any free parking specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void FreeParkingSquare::updateView() {
    // Update the view when the model changes
    // This might include updating colors or text based on game state
    // For now, this is empty as we haven't implemented the model yet
}
