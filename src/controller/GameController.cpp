#include "GameController.hpp"

#include "../model/squares/Property.hpp"

monopoly::GameController::GameController(const size_t numOfPlayers, Gui& gui, PlayerRegistry& player_registry): monopoly_instance(Game::getInstance()),
                                                                               player_registry(player_registry), gui(&gui),
                                                                               isGameOver(false) {
    monopoly_instance.initializeGame(numOfPlayers);
    startGame();
}

void monopoly::GameController::startGame() {
    if (!monopoly_instance.startGame()) {
        throw std::runtime_error("Failed to start game.");
    }
    while (!isGameOver) {
        nextTurn();
    }
    endGame();
}

void monopoly::GameController::endGame() {
    if (!monopoly_instance.endGame()) {
        throw std::runtime_error("Failed to end game.");
    }
}

void monopoly::GameController::nextTurn() {
    handleTurn();
    monopoly_instance.nextTurn();
}

void monopoly::GameController::addPlayer(std::unique_ptr<Player> player) {
    monopoly_instance.addPlayer(std::move(player));
}

monopoly::Player &monopoly::GameController::getCurrentPlayer() {
    return monopoly_instance.getCurrentPlayer();
}

Square *monopoly::GameController::getSquareAt(const int index) {
    return monopoly_instance.getSquareAt(index);
}

void monopoly::GameController::handleTurn() {
    rollDice();
    updateGui();
}

void monopoly::GameController::rollDice() {
    const Game::Dice dice = monopoly_instance.rollDice();
    handleDiceRoll(dice.getTotal(), dice.isDoubles());
}

void monopoly::GameController::updateGui() {
    std::cout << "updated gui" << &gui << std::endl;
}


void monopoly::GameController::handleDiceRoll(const int result, const bool isDoubles) {
    if (isDoubles) {
        handleDouble(result);
    } else {
        moveSteps(result);
    }
}

void monopoly::GameController::handleDouble(int result) {
    Player &currentPlayer = getCurrentPlayer();
    currentPlayer.increaseDoubles();
    if (currentPlayer.isInJail()) {
        outOfJail();
    }
}

void monopoly::GameController::isGameWon() {
    size_t bankrupters = 0;
    const std::unordered_map<uint32_t, std::shared_ptr<Player>> objects = player_registry.getAllObjects();
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (it->second->getBalance() >= 4000) {
                isGameOver = true; // should return/set the winner the winner
                std::cout << "Game Over, WINNER IS: "<< it->second->getName()<<std::endl;
                return;
            }
            if (it->second->getBalance() < 0) {
                bankrupters++;
            }
        }
    if (bankrupters == player_registry.getSize() - 1) {
        isGameOver = true;
    }
}

void monopoly::GameController::moveSteps(int steps) {
    if (getCurrentPlayer().getPosition() + steps >= monopoly_instance.getBoard().getSize()) {
        movedPastGo();
    }
    getCurrentPlayer().moveSteps(steps);
    landOn(getCurrentPlayer().getPosition());
}

void monopoly::GameController::movedPastGo() {
    getCurrentPlayer().increaseBalance(200);
    std::cout << getCurrentPlayer().getName() << " moved past go" << std::endl;
}

void monopoly::GameController::landOn(int pos) {
    //Registry to be used HERE!!! TODO
    Square *square = getSquareAt(pos);
    if (auto *property = dynamic_cast<Property *>(square)) {
        landOnProperty(property);
    }
    std::cout << "landOn " << getCurrentPlayer().canAfford(1) << std::endl;
}

void monopoly::GameController::landOnProperty(Property *property) {
    //TODO:complete!
    Player player = getCurrentPlayer();
    if (property.)

}


void monopoly::GameController::outOfJail() {
    Player &currentPlayer = getCurrentPlayer();
    currentPlayer.resetJailTurns();
}
