#include "../../../include/view/components/GoSquare.hpp"

void GoSquare::setTexts() {
    // Initialize all text elements with the same font as parent
    GO_text.setFont(font);
    collect_text.setFont(font);
    salary_text.setFont(font);
    as_you_pass_text.setFont(font);

    // Set text strings
    GO_text.setString("GO");
    collect_text.setString("COLLECT");
    salary_text.setString("SALARY");
    as_you_pass_text.setString("AS YOU PASS");

    // Set colors
    sf::Color textColor = sf::Color::Black;
    GO_text.setFillColor(textColor);
    collect_text.setFillColor(textColor);
    salary_text.setFillColor(textColor);
    as_you_pass_text.setFillColor(textColor);

    // Set character sizes relative to square size
    float mainCharSize = CORNER_SIZE / 6.0f;  // Large size for GO
    float smallCharSize = CORNER_SIZE / 16.0f; // Smaller size for other text

    GO_text.setCharacterSize(static_cast<unsigned int>(mainCharSize));
    collect_text.setCharacterSize(static_cast<unsigned int>(smallCharSize));
    salary_text.setCharacterSize(static_cast<unsigned int>(smallCharSize));
    as_you_pass_text.setCharacterSize(static_cast<unsigned int>(smallCharSize));

    // Get bounds for positioning
    sf::FloatRect goBounds = GO_text.getLocalBounds();
    sf::FloatRect collectBounds = collect_text.getLocalBounds();
    sf::FloatRect salaryBounds = salary_text.getLocalBounds();
    sf::FloatRect passBounds = as_you_pass_text.getLocalBounds();

    // Calculate diagonal rotation angle (315 degrees for bottom-right corner)
    float rotation = 315.0f;

    // Position GO text in center
    GO_text.setPosition(
        position.x + (CORNER_SIZE - goBounds.width) / 2.0f,
        position.y + (CORNER_SIZE - goBounds.height) / 2.0f
    );
    GO_text.setRotation(rotation);

    // Position "COLLECT SALARY AS YOU PASS" text along the top
    float topPadding = TEXT_PADDING;
    float textSpacing = smallCharSize / 2.0f;

    collect_text.setPosition(
        position.x + TEXT_PADDING,
        position.y + topPadding
    );
    collect_text.setRotation(rotation);

    salary_text.setPosition(
        position.x + TEXT_PADDING,
        position.y + topPadding + textSpacing + collectBounds.height
    );
    salary_text.setRotation(rotation);

    as_you_pass_text.setPosition(
        position.x + TEXT_PADDING,
        position.y + topPadding + (textSpacing + collectBounds.height) * 2
    );
    as_you_pass_text.setRotation(rotation);

    // Hide the parent's name_text as we're using our own layout
    name_text.setCharacterSize(0);
}

void GoSquare::draw(sf::RenderWindow& window) {
    if (!isComponentVisible()) return;

    // Draw the background (parent's background)
    window.draw(background);

    // Draw all text elements
    window.draw(GO_text);
    window.draw(collect_text);
    window.draw(salary_text);
    window.draw(as_you_pass_text);
}

bool GoSquare::handleEvent(const sf::Event& event) {
    if (!isComponentEnabled()) return false;

    // Handle any GO square specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void GoSquare::updateView() {
    // Update the view when the model changes
    // This might include updating colors or text based on game state
    // For now, this is empty as we haven't implemented the model yet
}