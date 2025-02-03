#pragma once
#include "LandState.hpp"

namespace monopoly {
    class RollDiceState : public GameState {
    public:
        static GameState *Instance() {
            static RollDiceState instance;
            return &instance;
        }

        void onEnter(GameController *controller) override {
            auto currentPlayer = controller->getCurrentPlayerIndex();
            controller->getView()->showRollDicePrompt(currentPlayer);
        }

        void handleKeyRelease(GameController *controller, sf::Keyboard::Key key) override {
            if (key == sf::Keyboard::Space) {
                auto model = controller->getModel();
                auto currentPlayer = controller->getCurrentPlayerIndex();

                // Roll dice and move player
                int steps = model->rollDice();
                model->movePlayer(currentPlayer, steps);

                // Update view
                controller->getView()->updateDiceRoll(steps);
                controller->getView()->updatePlayerPosition(currentPlayer);

                // Transition to LandState
                changeState(controller, LandState::Instance());
            }
        }
    };
}
