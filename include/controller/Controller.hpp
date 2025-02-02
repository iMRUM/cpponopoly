#pragma once
#include "../view/View.hpp"
#include "../model/GameModel.hpp"

namespace monopoly {
    struct UserInput {
        bool decision;
    };
    struct TurnViewData {
        Dice dice;

    };
    class Controller {
    private:
        std::unique_ptr<GameModel> model;
        std::unique_ptr<View> view;
        sf::RenderWindow window;

        void changeModel();
        void initModel(size_t num_of_players, size_t num_of_squares);
        void initView();
        bool isKeyPressed(sf::Keyboard::Key key);
        void changeView();
        void handleUserInput();



    public:
        ~Controller() = default;
        Controller() = default;
        void init();
        void run();
    };
}
