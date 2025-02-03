#include "../../../include/utils/state/StartState.hpp"
#include "../../../include/controller/GameController.hpp"

namespace monopoly {
    StartState* StartState::instance = nullptr;
    GameState *StartState::getInstance() {
        if (!instance) {
            instance = new StartState();
        }
        return instance;
    }

    void StartState::onEnter(GameController *controller) {
        controller->initView();
        std::string message = "Enter num of players";
        controller->getView()->updatePanelMessage(message);
    }

    void StartState::handleKeyRelease(GameController *controller, const sf::Keyboard::Key key) {
        if (key >= sf::Keyboard::Num2 && key <= sf::Keyboard::Num8) {
            const size_t numPlayers = static_cast<size_t>(key - sf::Keyboard::Num0);
            controller->initModel(numPlayers);
            GameView *view = controller->getView();
            for (int i = 0; i < numPlayers; ++i) {
                controller->getView()->updatePlayerAtBoardSquare(i, 0);
            }
            std::cout << "changeState(controller, RollDiceState::Instance());" << std::endl;
            changeState(controller, RollDiceState::getInstance());
        }
    }
};
