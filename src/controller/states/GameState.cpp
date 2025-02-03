#include "../../../include/utils/state/GameState.hpp"
#include "../../../include/controller/GameController.hpp"

namespace monopoly {
    void GameState::update(GameController* controller) {
        controller->update();
    }
}