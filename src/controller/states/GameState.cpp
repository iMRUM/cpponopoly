#include "../../../include/utils/state/GameState.hpp"
#include "../../../include/controller/GameController.hpp"

namespace monopoly {
    void GameState::changeState(GameController *controller, GameState *newState) {
        controller->changeState(newState);
    }

    void GameState::update(GameController* controller) {
        controller->update();
    }
}