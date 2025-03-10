#include "../../../include/utils/state/TurnState.hpp"
#include "../../../include/controller/GameController.hpp"

namespace monopoly {
    TurnState *TurnState::instance = nullptr;

    GameState *TurnState::getInstance() {
        if (!instance) {
            instance = new TurnState();
        }
        return instance;
    }

    void TurnState::onEnter(GameController *controller) {
        GameModel* model = controller->getModel();
        GameView* view = controller->getView();
        Player& current_player = model->getCurrentPlayer();
        std::string message = "Let's Go "+current_player.getName() + "\nPress SPACE to start your turn";
        view->updateBalanceBox(current_player.getBalance());
        view->updateNameBox(current_player.getNamenc());
        view->updatePanelMessage(message);
    }

    void TurnState::handleKeyRelease(GameController *controller, sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Space) {
            std::cout << "space Released" << std::endl;
            GameModel *model = controller->getModel();
            if (model->isGameOver()) {
                std::cout << "changeState(controller, GameOverState::getInstance())" << std::endl;
                return;
            }
            Player &current_player = model->getCurrentPlayer();
            if (current_player.isInJail()) {
                std::cout << "changeState(controller, JailState::getInstance())" << std::endl;
                return;
            }
            std::cout << "changing to rolldice" << std::endl;
            changeState(controller, RollDiceState::getInstance());
        }
    }
}
