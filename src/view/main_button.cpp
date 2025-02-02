#include "../../include/controller/GameController.hpp"

int main() {
    monopoly::GameController controller;
    controller.init();
    controller.run();
    return 0;
}