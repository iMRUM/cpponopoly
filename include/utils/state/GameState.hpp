#pragma once
#include <stdexcept>
#include <SFML/Window/Keyboard.hpp>

namespace monopoly {
    class GameController;

    class GameState {
    public:
        static GameState *getInstance() {
            throw std::runtime_error("Cannot instantiate base GameState");
        }

        virtual ~GameState() = default;

        virtual void onEnter(GameController *controller) = 0;

        virtual void handleKeyRelease(GameController *controller, sf::Keyboard::Key key) = 0;

        void update(GameController *controller);

    protected:
        GameState() = default;

        void changeState(GameController *controller, GameState *newState);

        // Prevent copying of singleton states
        GameState(const GameState &) = delete;

        GameState &operator=(const GameState &) = delete;
    };
}
