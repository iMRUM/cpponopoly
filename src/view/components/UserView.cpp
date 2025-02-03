#include "../../../include/view/components/UserView.hpp"

monopoly::UserView::UserView(const sf::Vector2f &pos, const sf::Vector2f &sz): SFComponent(pos, sz) {
    // Load font
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Setup boxes (existing code)
    prompt_box.setSize(sf::Vector2f(300.f, 150.f));
    prompt_box.setPosition(pos);
    prompt_box.setFillColor(sf::Color::White);
    prompt_box.setOutlineThickness(2.f);
    prompt_box.setOutlineColor(sf::Color::Black);

    balance_box.setSize(sf::Vector2f(120.f, 40.f));
    balance_box.setPosition(pos.x +32.5f, pos.y+155.f);
    balance_box.setFillColor(sf::Color(100, 250, 100));

    name_box.setSize(sf::Vector2f(120.f, 40.f));
    name_box.setPosition(pos.x+155.f, pos.y+155.f);
    name_box.setFillColor(sf::Color(250, 100, 100));

    // Setup text objects
    prompt_text.setFont(font);
    prompt_text.setCharacterSize(16);
    prompt_text.setFillColor(sf::Color::Black);
    prompt_text.setPosition(pos.x + 10.f, pos.y + 10.f);

    balance_text.setFont(font);
    balance_text.setCharacterSize(14);
    balance_text.setFillColor(sf::Color::Black);
    balance_text.setPosition(balance_box.getPosition().x + 10.f, balance_box.getPosition().y + 10.f);

    name_text.setFont(font);
    name_text.setCharacterSize(14);
    name_text.setFillColor(sf::Color::Black);
    name_text.setPosition(name_box.getPosition().x + 10.f, name_box.getPosition().y + 10.f);
}
void monopoly::UserView::updateBalance(int balance) {
    balance_text.setString("$" + std::to_string(balance));
}

void monopoly::UserView::updateNameBox(std::string &name) {
    name_text.setString(name);
}

void monopoly::UserView::updatePromptText(const std::string& prompt) {
    current_prompt = prompt;
    prompt_text.setString(prompt);
}
void monopoly::UserView::draw(sf::RenderWindow &window) {
    window.draw(balance_box);
    window.draw(name_box);
    window.draw(prompt_box);
    window.draw(prompt_text);
    window.draw(balance_text);
    window.draw(name_text);
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
