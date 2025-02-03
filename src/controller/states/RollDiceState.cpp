#include "../../../include/utils/state/RollDiceState.hpp"
#include "../../../include/controller/GameController.hpp"
namespace monopoly{
    RollDiceState* RollDiceState::instance = nullptr;
GameState * RollDiceState::getInstance() {
    if (!instance) {
        instance = new RollDiceState();
    }
    return instance;
}

void RollDiceState::onEnter(GameController *controller) {
    std::string message = "Press SPACE to roll dice";
    controller->getView()->updatePanelMessage(message);
}

void RollDiceState::handleKeyRelease(GameController *controller, sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space) {
        GameModel* model = controller->getModel();
        GameView* view = controller->getView();
        Player& current_player = model->getCurrentPlayer();
        const Dice& dice = model->rollDice();
        if (dice.isDoubles()) {
            if (current_player.isInJail()) {
                view->updatePlayerAtBoardSquare(current_player.getId(),10);
                return;
            }
            if (!current_player.isInJail()) {
                std::string message = "CONGRATS! You are out Jail.";
                view->updatePanelMessage(message);
                return;
            }
        }
        std::cout << "changeState(controller, MoveState::getInstance())"<< std::endl;
    }
}
}