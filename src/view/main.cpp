#include "../../include/view/Gui.hpp"
#include <iostream>

int main() {
    try {
        monopoly::Gui &gui = monopoly::Gui::getInstance();

        // Main game loop
        while (gui.isOpen()) {
            gui.processEvents();
            gui.render();
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}