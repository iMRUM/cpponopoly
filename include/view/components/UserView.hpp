#pragma once
#include "SFComposite.hpp"
//composes current turn-relevant components (right panel).
namespace monopoly {
    class UserView: public SFComponent {
        sf::RectangleShape current_player_info;
        sf::RectangleShape buy_button;
        sf::RectangleShape end_turn_button;
    public:
        UserView(const sf::Vector2f& pos, const sf::Vector2f& sz);

        void draw(sf::RenderWindow &window) override;

        bool handleEvent(const sf::Event &event) override;

        void updatePrompt(std::string& prompt);

        void updateView() override;
    };
}