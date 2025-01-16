#pragma once
#include "../view/Gui.hpp"
#include "../src/model/Game.hpp"

class Gui;
namespace monopoly {
    class Controller {
        Game& model = Game::getInstance();
        Gui& view = Gui::getInstance();
        ~Controller() = default;
        void gameLoop();
        void handleUserInput();
        void updateView();
        public:
        Controller() = default;
        void run();
    };
}