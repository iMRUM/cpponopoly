#pragma once
#include "SFComposite.hpp"
//composes current turn-relevant components (right panel).
namespace monopoly {
    class UserView: public SFComponent {
        sf::RectangleShape prompt_box;
        sf::RectangleShape balance_box;
        sf::RectangleShape name_box;

        sf::Font font;
        sf::Text prompt_text;
        sf::Text balance_text;
        sf::Text name_text;
        std::string current_prompt;
    public:
        UserView(const sf::Vector2f& pos, const sf::Vector2f& sz);

        void draw(sf::RenderWindow &window) override;

        bool handleEvent(const sf::Event &event) override;

        void updateBalance(int balance);
        void updateNameBox(std::string &name);
        void updatePromptText(const std::string& prompt);

        void updateView() override;
    };
}