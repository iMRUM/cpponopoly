#pragma once
#include <SFML/Graphics.hpp>
#include "components/BoardView.hpp"
#include "components/UserView.hpp"

namespace monopoly {
    class GameView {
    private:
        sf::RenderWindow window;
        BoardView board;
        UserView panel;
        static std::unique_ptr<GameView> instance;

        GameView(sf::VideoMode mode, const std::string &title, float boardSize,
                 const sf::Vector2f &panelPos, const sf::Vector2f &panelSize);

    public:
        static std::unique_ptr<GameView> getInstance(sf::VideoMode mode,
                                                     const std::string &title, float boardSize,
                                                     const sf::Vector2f &panelPos, const sf::Vector2f &panelSize);

        void start();
        void close() { window.close(); }
        bool isOpen() const { return window.isOpen(); }
        bool pollEvent(sf::Event &event) { return window.pollEvent(event); }

        void showPrompt(std::string &prompt);

        void update();

        void render();

        void updateBoardDisplay();

        void showDiceRoll(int value);

        void displayPropertyCard(int propertyId);

        void askPurchaseDecision(int propertyId, int price);

        void handleEvent(const sf::Event & event);
    };
}
