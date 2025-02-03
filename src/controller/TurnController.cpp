#include "../../include/controller/TurnController.hpp"

namespace monopoly {
    // Minimal implementation for testing
    TurnController::TurnController(GameModel* m, GameView* v) : model(m), view(v) {}

    void TurnController::executeTurn(Player& player, PropertyController& property_controller) {
        std::cout << "Executing turn for player " << player.getId() << std::endl;
    }
}
