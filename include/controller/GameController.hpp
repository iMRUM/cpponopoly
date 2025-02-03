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
        void moveToNextPlayer();
        bool isGameOver() const;

        void handleKeyRelease(sf::Keyboard::Key key);

        void handleUserInput();

    public:
        GameController() = default;
        ~GameController() = default;
        void init();
        void run();
    };
}