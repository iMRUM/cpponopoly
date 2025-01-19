#include "../include/controller/Controller.hpp"
#define PLAYERS_COUNT 8

bool monopoly::Controller::initializeGame(size_t numPlayers) {
    return true;
}

void monopoly::Controller::handleRollDice() {
}

void monopoly::Controller::handleBuyProperty() {
}

void monopoly::Controller::handleEndTurn() {
}

void monopoly::Controller::handleBuildProperty() {
}

void monopoly::Controller::handlePropertyDecision() {
}

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
