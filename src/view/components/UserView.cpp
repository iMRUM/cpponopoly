#include "../../../include/view/components/UserView.hpp"

monopoly::UserView::UserView(const sf::Vector2f &pos, const sf::Vector2f &sz): SFComponent(pos, sz) {
    current_player_info.setSize(sf::Vector2f(300.f, 150.f));
    current_player_info.setPosition(pos);
    current_player_info.setFillColor(sf::Color::White);
    current_player_info.setOutlineThickness(2.f);
    current_player_info.setOutlineColor(sf::Color::Black);

    buy_button.setSize(sf::Vector2f(120.f, 40.f));
    buy_button.setPosition(pos.x +32.5f, pos.y+155.f);
    buy_button.setFillColor(sf::Color(100, 250, 100));

    end_turn_button.setSize(sf::Vector2f(120.f, 40.f));
    end_turn_button.setPosition(pos.x+155.f, pos.y+155.f);
    end_turn_button.setFillColor(sf::Color(250, 100, 100));
}

void monopoly::UserView::draw(sf::RenderWindow &window) {
    window.draw(buy_button);
    window.draw(end_turn_button);
    window.draw(current_player_info);
}

bool monopoly::UserView::handleEvent(const sf::Event &event) {
    if (!isComponentEnabled()) return false;

    // Handle any Go To Jail specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void monopoly::UserView::updateView() {
}
