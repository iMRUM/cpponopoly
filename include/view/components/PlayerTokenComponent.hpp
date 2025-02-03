#pragma once
#include <functional>
#include <memory>
#include <string>
#include "SFComponent.hpp"
class PlayerTokenComponent : public SFComponent {
private:
    static constexpr float TOKEN_RADIUS = 7.5f;  // Size of player token
    static constexpr float TOKEN_TEXT_SIZE = 11.0f;  // Size of player ID text

    sf::CircleShape token;
    sf::Text id_text;
    sf::Font font;
    int player_id;

public:
    PlayerTokenComponent(const sf::Vector2f &pos, int id)
        : SFComponent(pos, sf::Vector2f(TOKEN_RADIUS * 2, TOKEN_RADIUS * 2)),
          player_id(id) {

        if (!font.loadFromFile("assets/arial.ttf")) {
            throw std::runtime_error("Failed to load font from assets/arial.ttf");
        }

        // Setup token
        token.setRadius(TOKEN_RADIUS);
        token.setFillColor(sf::Color::Black);
        token.setPosition(position);

        // Setup text
        id_text.setFont(font);
        id_text.setString(std::to_string(player_id));
        id_text.setCharacterSize(static_cast<unsigned int>(TOKEN_TEXT_SIZE));
        id_text.setFillColor(sf::Color::White);

        // Center the text in token
        sf::FloatRect textBounds = id_text.getLocalBounds();
        id_text.setPosition(
            position.x + TOKEN_RADIUS - textBounds.width/2,
            position.y + TOKEN_RADIUS - textBounds.height/2
        );
    }
    [[nodiscard]] int getPlayerId() const { return player_id; }
    void draw(sf::RenderWindow &window) override {
        if (!isComponentVisible()) return;

        window.draw(token);
        window.draw(id_text);
    }

    bool handleEvent(const sf::Event &event) override {
        if (!isComponentEnabled()) return false;

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            return contains(mousePos);
        }
        return false;
    }

    void updateView() override;


    static float getTokenDiameter() { return TOKEN_RADIUS * 2; }
};