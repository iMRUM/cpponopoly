#include "../../include/controller/GameController.hpp"

namespace monopoly {
    GameController::GameController() : model(GameModel::getInstance()), view(GameView::getInstance(
                               sf::VideoMode(1920, 1080), "Monopoly",
                               960.f,
                               sf::Vector2f(330.f, 200.f),
                               sf::Vector2f(640.f, 640.f)
                           )) {
        changeState(StartState::getInstance());
    }

    void GameController::initModel(const size_t num_of_players = 2) {
        model->initializeGame(num_of_players);
    }

    void GameController::initView() {
        view->start();
    }

    bool GameController::isGameOver() const {
        return model->isGameOver();
    }

    void GameController::handleKeyRelease(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Space && !model->isGameStarted()) {
            std::cout << "starting game" << std::endl;
            model->startGame();
        } else if (key == sf::Keyboard::Up &&
                   model->isGameStarted() &&
                   !model->hasRolled()) {
            model->setHasRolled(false);
        }
    }


    void GameController::handleUserInput() {
        sf::Event event;
        while (view->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    view->close();
                    break;
                case sf::Event::KeyReleased:
                    state->handleKeyRelease(this, event.key.code);
                    break;
                default: view->handleEvent(event);
            }
        }
    }

    void GameController::run() {
        while (!model->isGameOver() && view->isOpen()) {
            handleUserInput();
            view->update();
            view->render();
        }
    }

    void GameController::update() {
        view->update();
    }

    void GameController::changeState(GameState *newState) {
        state = std::unique_ptr<GameState>(newState);
        state->onEnter(this);
    }
}
