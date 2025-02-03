#pragma once
#include "GameState.hpp"

namespace monopoly {
    class TurnState : public GameState {
    private:
        static TurnState *instance;

        TurnState() = default;

    public:
        static GameState *getInstance();

        void onEnter(GameController *controller) override;

        void handleKeyRelease(GameController *controller, sf::Keyboard::Key key) override;
    };
}
