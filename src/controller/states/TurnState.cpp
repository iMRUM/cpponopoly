#include "../../../include/utils/state/TurnState.hpp"
#include "../../../include/controller/GameController.hpp"

monopoly::GameState * monopoly::TurnState::getInstance() {
    if (!instance) {
        instance = new TurnState();
    }
    return instance;
}

void monopoly::TurnState::onEnter(GameController *controller) {
    std::string message = "Press SPACE to start your turn";
    controller->getView()->updatePanelMessage(message);
}

void monopoly::TurnState::handleKeyRelease(GameController *controller, sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space) {
        GameModel* model = controller->getModel();
        if(model->isGameOver()) {
            std::cout << "changeState(controller, GameOverState::getInstance())" << std::endl;
            return;
        }
        Player& current_player = model->getCurrentPlayer();
        if(current_player.isInJail()) {
            std::cout << "changeState(controller, JailState::getInstance())" << std::endl;
            return;
        }
        changeState(controller, RollDiceState::getInstance());
    }
}
