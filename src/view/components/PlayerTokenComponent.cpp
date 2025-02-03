#include "../../../include/view/components/PlayerTokenComponent.hpp"

void PlayerTokenComponent::updateView() {
    // Update token and text positions if needed
    token.setPosition(position);

    sf::FloatRect textBounds = id_text.getLocalBounds();
    id_text.setPosition(
        position.x + TOKEN_RADIUS - textBounds.width/2,
        position.y + TOKEN_RADIUS - textBounds.height/2
    );
}