#include "../../include/controller/Controller.hpp"

int main() {
    monopoly::Controller controller;
    controller.init();
    controller.run();
    return 0;
}