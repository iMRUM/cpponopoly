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

        void updatePlayerAtBoardSquare(int player_id, int new_square_id, int old_square_id);

        void close() { window.close(); }
        bool isOpen() const { return window.isOpen(); }
        bool pollEvent(sf::Event &event) { return window.pollEvent(event); }

        void updateBalanceBox(int balance);
        void updateNameBox(std::string &name);
        void updatePlayerName(const std::string &name);
        void updatePanelMessage(std::string &prompt);

        void update();

        void render();

        void updateBoardDisplay();

        void showDiceRoll(int value);

        void displayPropertyCard(int propertyId);

        void askPurchaseDecision(int propertyId, int price);

        void handleEvent(const sf::Event & event);
    };
}
