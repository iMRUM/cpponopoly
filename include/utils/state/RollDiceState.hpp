#pragma once
#include "GameState.hpp"
#include "LandState.hpp"

namespace monopoly {
    class RollDiceState : public GameState {
    private:
        static RollDiceState* instance;
        RollDiceState() = default;
    public:
        static GameState *getInstance();

        void onEnter(GameController *controller) override;

        void handleKeyRelease(GameController *controller, sf::Keyboard::Key key) override;
    };
}
