#pragma once
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"
#include "PropertyController.hpp"

namespace monopoly {
    class TurnController {
    public:
        TurnController(GameModel* model, GameView* view);
        void executeTurn(Player& player, PropertyController& property_controller);

    private:
        int rollDice();
        void movePlayer(Player& player, int spaces);
        void handleSquareAction(Player& player, PropertyController& property_controller);
        void handleJailTurn(Player& player);

        GameModel* model;
        GameView* view;
    };
}
