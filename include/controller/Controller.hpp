#pragma once
#include "../view/Gui.hpp"
#include "../model/Game.hpp"

class Gui;
namespace monopoly {
    class Controller {
        Game& model = Game::getInstance();
        Gui& view = Gui::getInstance();
        ~Controller() = default;
        bool initializeGame(size_t numPlayers);
        void handleRollDice();
        void handleBuyProperty();
        void handleEndTurn();
        void handleBuildProperty();
        void handlePropertyDecision();

        void gameLoop();
        void handleUserInput();
        void updateView();
        public:
        Controller() = default;
        void run();
    };
}