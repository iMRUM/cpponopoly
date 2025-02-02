#include "../../include/controller/GameController.hpp"

bool monopoly::GameController::isKeyPressed(sf::Keyboard::Key key) {
    std::cout << key + "WAS PRESSED" << std::endl;
    return sf::Keyboard::isKeyPressed(key);
}

void monopoly::GameController::handleUserInput() {
    if (isKeyPressed(sf::Keyboard::Up)) {
        std::cout << "buy/use jail card" << std::endl;
    }
    if (isKeyPressed(sf::Keyboard::Down)) {
        model->nextTurn();
    }
}

void monopoly::GameController::initModel(size_t num_of_players, size_t num_of_squares) {
    model = GameModel::getInstance();
    model->initializeGame(num_of_players, num_of_squares);
}

void monopoly::GameController::initView() {
    view = GameView::getInstance(
    sf::VideoMode(1920, 1080), "Monopoly",
    960.f,
    sf::Vector2f(1000.f, 100.f),
    sf::Vector2f(640.f, 640.f)
);
}

void monopoly::GameController::init() {
    initView();
    initModel(2, 40);
}

void monopoly::GameController::run() {
    view->start();
    handleUserInput();
}
