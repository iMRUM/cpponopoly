#pragma once
#include "GameState.hpp"

namespace monopoly {
    class StartState : public GameState {
    private:
        static StartState* instance;
        StartState() = default;
    public:
        static GameState *getInstance();

        void onEnter(GameController *controller) override;

        void handleKeyRelease(GameController *controller, sf::Keyboard::Key key) override;
    };
}
