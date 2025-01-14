#pragma once
#include "../model/Game.hpp"

namespace monopoly {
    class GameController {
        Game& monopoly_instance = Game::getInstance();
        Player& getCurrentPlayer();
        Square& getSquareAt(int index);

        //Turns management:
        void handleTurn();
        void rollDice();
        void updateGui();
        void handleDiceRoll(int result, bool isDoubles);
        void handleDouble(int result);

        //Movement management:
        void moveSteps(int steps);
        void landOn();
        void outOfJail();
    public:
        explicit GameController(size_t numOfPlayers);
        void startGame();
        void endGame();
        void nextTurn();
        void addPlayer(std::unique_ptr<Player> player);

    };
}
