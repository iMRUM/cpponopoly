#include "GameController.hpp"

#include "../model/squares/Property.hpp"

monopoly::GameController::GameController(size_t numOfPlayers) {
    monopoly_instance.initializeGame(numOfPlayers);
}

monopoly::Player & monopoly::GameController::getCurrentPlayer() {
    return monopoly_instance.getCurrentPlayer();
}

Square & monopoly::GameController::getSquareAt(int index) {
    return monopoly_instance.getSquareAt(index);
}

void monopoly::GameController::startGame() {
    if(!monopoly_instance.startGame()) {
        throw std::runtime_error("Failed to start game.");
    }
}

void monopoly::GameController::endGame() {
    if(!monopoly_instance.endGame()) {
        throw std::runtime_error("Failed to end game.");
    }
}

void monopoly::GameController::nextTurn() {
    handleTurn();
    monopoly_instance.nextTurn();
}

void monopoly::GameController::handleTurn() {
    rollDice();
    updateGui();
}

void monopoly::GameController::updateGui() {
    std::cout << "updated gui" << std::endl;
}

void monopoly::GameController::addPlayer(std::unique_ptr<Player> player) {
    monopoly_instance.addPlayer(std::move(player));
}

void monopoly::GameController::rollDice() {
    const Game::Dice dice = monopoly_instance.rollDice();
    handleDiceRoll(dice.getTotal(), dice.isDoubles());
}

void monopoly::GameController::handleDiceRoll(const int result, const bool isDoubles) {
    if (isDoubles) {
        handleDouble(result);
    } else {
        moveSteps(result);
    }
}

void monopoly::GameController::moveSteps(int steps) {
    getCurrentPlayer().moveSteps(steps);
}

void monopoly::GameController::landOn() { //Registry to be used HERE!!! TODO
    if(dynamic_cast<Property> getSquareAt(getCurrentPlayer().getPosition())).getOwnerId() == getCurrentPlayer().getPosition() {
        std::cout << getCurrentPlayer().getName()<<" is the owner"<<endl;
    }
}

void monopoly::GameController::handleDouble(int result) {
    Player& currentPlayer = getCurrentPlayer();
    currentPlayer.increaseDoubles();
    if (currentPlayer.isInJail()) {
        outOfJail();
    }
}
void monopoly::GameController::outOfJail() {
    Player& currentPlayer = getCurrentPlayer();
    currentPlayer.resetJailTurns();
}

