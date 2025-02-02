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
    }


    void GameController::gameLoop() {
        view->start();
        if (!model->isGameStarted() && handleUserInput("Press SPACEBAR to continue")) {
            model->initializeGame(2);
        }
        while (!isGameOver() && view->isOpen()) {
            processTurn();
            view->update();
            view->render();
        }
    }

    void GameController::processTurn() {
        auto &current_player = model->getCurrentPlayer();
        executeTurn(current_player);
        moveToNextPlayer();
    }

    void GameController::executeTurn(Player &current_player) {
            while (getAwaitedAction() != AwaitedAction::TURN_ENDED) {
                switch (getAwaitedAction()) {
                    case AwaitedAction::ROLL_DICE:
                    case AwaitedAction::BUY_PROPERTY:
                    case AwaitedAction::BUILD_HOUSE:
                    case AwaitedAction::USE_JAIL_CARD:
                    case AwaitedAction::PAY_JAIL_FINE:
                        if (handleUserInput("Press SPACEBAR to continue")) {
                            model->executeAction(getAwaitedAction());
                        }
                        break;
                    case AwaitedAction::MOVE:
                        model->executeAction(AwaitedAction::MOVE);
                        break;
                }
            }
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

    bool GameController::handleKeyRelease(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Space) {
            std::cout << "Spacebar pressed" << std::endl;
            return true;
        }
        return false;
    }


    bool GameController::handleUserInput(const std::string &message) {
        sf::Event event;
        if (view->pollEvent(event)) {
            // Blocks until event occurs
            switch (event.type) {
                case sf::Event::Closed:
                    view->close();
                    return false;
                case sf::Event::KeyReleased:
                    return handleKeyRelease(event.key.code);
                default:
                    return false;
            }
        }
        return false;
    }


    void GameController::init() {
        initModel(2);
        initView();
    }
    void GameController::run() {
        view->start();

        bool waiting_for_input = true;
        sf::Clock frame_clock;
        const float frame_time = 1.0f / 60.0f;  // 60 FPS

        while (view->isOpen()) {
            sf::Event event;
            while (view->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    view->close();
                } else if (event.type == sf::Event::KeyReleased && waiting_for_input) {
                    if (event.key.code == sf::Keyboard::Space) {
                        waiting_for_input = false;
                    }
                }
            }

            if (frame_clock.getElapsedTime().asSeconds() >= frame_time) {
                if (!waiting_for_input && model->isGameStarted()) {
                    processTurn();
                    waiting_for_input = true;
                }

                view->update();
                view->render();
                frame_clock.restart();
            }
        }
    }
}
