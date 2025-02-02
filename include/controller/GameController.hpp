#pragma once
#include <memory>
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"
#include "TurnController.hpp"
#include "PropertyController.hpp"

namespace monopoly {
    class GameController {
    private:
        std::unique_ptr<GameModel> model;
        std::unique_ptr<GameView> view;
        size_t current_player_index{0};

        void initModel(size_t num_of_players);
        void initView();

        void gameLoop();
        void processTurn();
        void executeTurn(Player &current_player);
        void moveToNextPlayer();
        bool isGameOver() const;


        bool handleKeyRelease(sf::Keyboard::Key key);

        bool handleUserInput(const std::string &message);
        void handleGameAction(AwaitedAction action);
        void updateGameState();

        // Action handlers
        void handleBuyProperty();
        void handleBuildHouse();
        void handleUseJailCard();
        void handleRollDice();
        void handleEndTurn();
        [[nodiscard]] AwaitedAction getAwaitedAction() const{return model->getAwaitedAction();};
    public:
        GameController() = default;
        ~GameController() = default;
        void init();
        void run();
    };
}