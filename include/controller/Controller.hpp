#pragma once
#include "../view/View.hpp"
#include "../model/Game.hpp"

namespace monopoly {
    struct UserInput {
        bool decision;
    };
    struct TurnViewData {
        Dice dice;

    };
    class Controller {
    private:
        Game &model = Game::getInstance();
        View &view = View::getInstance(TODO, TODO, TODO);
        void changeModel();
        void initModel(size_t num_of_players, size_t num_of_squares);

        bool isKeyPressed(sf::Keyboard::Key key);
        void changeView();
        void handleUserInput();

        ~Controller() = default;

    public:
        Controller() = default;

        void run();
    };
}
