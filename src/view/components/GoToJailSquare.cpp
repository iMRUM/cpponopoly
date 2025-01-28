#include "../../../include/view/components/GoToJailSquare.hpp"

void GoToJailSquare::setTexts() {
    // Initialize "GO TO" and "JAIL" texts with the same font as parent
    GO_TO_text.setFont(font);
    JAIL_text.setFont(font);
    
    // Set text properties
    GO_TO_text.setString("GO TO");
    JAIL_text.setString("JAIL");
    
    GO_TO_text.setFillColor(sf::Color::Black);
    JAIL_text.setFillColor(sf::Color::Black);
    
    // Set character size relative to square size
    float charSize = CORNER_SIZE / 12.0f;  // Adjust this ratio as needed
    GO_TO_text.setCharacterSize(static_cast<unsigned int>(charSize));
    JAIL_text.setCharacterSize(static_cast<unsigned int>(charSize * 1.2f));  // Make "JAIL" slightly larger
    
    // Position the texts
    sf::FloatRect goToBounds = GO_TO_text.getLocalBounds();
    sf::FloatRect jailBounds = JAIL_text.getLocalBounds();
    
    // Calculate center point for alignment
    float centerX = position.x + CORNER_SIZE / 2.0f;
    float centerY = position.y + CORNER_SIZE / 2.0f;
    
    // Position "GO TO" text in the upper portion
    GO_TO_text.setPosition(
        centerX - (goToBounds.width / 2.0f),
        centerY - goToBounds.height - TEXT_PADDING
    );
    GO_TO_text.setRotation(225);  // Rotate to match top-right corner orientation
    
    // Position "JAIL" text below "GO TO"
    JAIL_text.setPosition(
        centerX - (jailBounds.width / 2.0f),
        centerY + TEXT_PADDING
    );
    JAIL_text.setRotation(225);  // Rotate to match top-right corner orientation

    // Hide the parent's name_text as we're using our own layout
    name_text.setCharacterSize(0);
}

void GoToJailSquare::draw(sf::RenderWindow& window) {
    if (!isComponentVisible()) return;
    
    // Draw the background (parent's background)
    window.draw(background);
    
    // Draw the texts
    window.draw(GO_TO_text);
    window.draw(JAIL_text);
}

bool GoToJailSquare::handleEvent(const sf::Event& event) {
    if (!isComponentEnabled()) return false;
    
    // Handle any Go To Jail specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void GoToJailSquare::updateView() {
    // Update the view when the model changes
    // This might include updating colors or text based on game state
    // For now, this is empty as we haven't implemented the model yet
}