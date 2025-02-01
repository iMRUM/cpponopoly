#include "../include/controller/Controller.hpp"

bool monopoly::Controller::isKeyPressed(sf::Keyboard::Key key) {
    std::cout << key + "WAS PRESSED" << std::endl;
    return sf::Keyboard::isKeyPressed(key);
}

void monopoly::Controller::handleUserInput() {
    if (isKeyPressed(sf::Keyboard::Up)) {
        std::cout << "buy/use jail card" << std::endl;
    }
    if (isKeyPressed(sf::Keyboard::Down)) {
        model.nextTurn();
    }
}

void monopoly::Controller::initModel(size_t num_of_players, size_t num_of_squares) {
    model.initializeGame(num_of_players, num_of_squares);
}

void monopoly::Controller::run() {
    initModel(2, 40);
    while (!model.isGameOver()) {
        model.nextTurn();
    }
}
