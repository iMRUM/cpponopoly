#include "../../include/controller/GameController.hpp"

namespace monopoly {
    void GameController::initModel(const size_t num_of_players = 2) {
        model = GameModel::getInstance();
        model->initializeGame(num_of_players);
    }

    void GameController::initView() {
        view = GameView::getInstance(
            sf::VideoMode(1920, 1080), "Monopoly",
            960.f,
            sf::Vector2f(1000.f, 100.f),
            sf::Vector2f(640.f, 640.f)
        );
        view->start();
    }

    void GameController::initControllers() {
        turn_controller = std::make_unique<TurnController>(model.get(), view.get());
        property_controller = std::make_unique<PropertyController>(model.get(), view.get());
    }

    void GameController::gameLoop() {
        view->start();

        while (!isGameOver() && view->isOpen()) {
            handleUserInput();
            view->update();
            view->render();
        }
    }

    void GameController::processTurn() {
        auto& current_player = model->getCurrentPlayer();
        turn_controller->executeTurn(current_player, *property_controller);
        moveToNextPlayer();
    }

    void GameController::moveToNextPlayer() {
        do {
            current_player_index = (current_player_index + 1) % model->getPlayersCount();
        } while (model->getPlayer(current_player_index).isBankrupt());
        model->setHasRolled(true);
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
            processTurn();
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
                    handleKeyRelease(event.key.code);
                    break;
                default: view->handleEvent(event);
            }
        }
    }


    void GameController::init() {
        initModel(2);
        initView();
        initControllers();
    }

    void GameController::run() {
        while (!model->isGameOver() && view->isOpen()) {
            handleUserInput();
            view->update();
            view->render();
        }
    }
}
