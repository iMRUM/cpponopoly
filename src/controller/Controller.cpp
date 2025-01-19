#include "../include/controller/Controller.hpp"
#define PLAYERS_COUNT 2
void monopoly::Controller::gameLoop() {
    model.initializeGame(PLAYERS_COUNT);
    while (!model.isGameOver()) {
        model.nextTurn();
    }

}

void monopoly::Controller::handleUserInput() {
}

void monopoly::Controller::updateView() {
}

void monopoly::Controller::run() {
    gameLoop();
}
