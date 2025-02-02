#include "include/controller/GameController.hpp"

int main() {
    try {
        // CHANGE: Added basic error handling
        monopoly::GameController game;
        game.init();
        game.run();  // CHANGE: Game loop now runs until window closed
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}