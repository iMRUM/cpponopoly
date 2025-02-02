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
        std::unique_ptr<TurnController> turn_controller;
        std::unique_ptr<PropertyController> property_controller;
        size_t current_player_index{0};

        void initModel(size_t num_of_players);
        void initView();
        void initControllers();
        void gameLoop();
        void processTurn();
        void moveToNextPlayer();
        bool isGameOver() const;
        void handleUserInput();

    public:
        GameController() = default;
        ~GameController() = default;
        void init();
        void run();
    };
}