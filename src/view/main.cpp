#include "../../include/view/Gui.hpp"
#include <iostream>
//g++ -o monopoly main.cpp Gui.cpp -I../../include -lsfml-graphics -lsfml-window -lsfml-system

int main() {
    try {
        // Get the singleton instance of the GUI
        monopoly::Gui& gui = monopoly::Gui::getInstance();

        // Main game loop
        while (gui.isOpen()) {
            // Process window events (close button, etc.)
            gui.processEvents();

            // Render the GUI
            gui.render();
        }

        // Cleanup the singleton instance
        monopoly::Gui::cleanup();

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}