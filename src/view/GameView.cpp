#include "../../include/view/GameView.hpp"
std::unique_ptr<monopoly::GameView> monopoly::GameView::instance = nullptr;
monopoly::GameView::GameView(sf::VideoMode mode, const std::string& title, float boardSize,
    const sf::Vector2f& panelPos, const sf::Vector2f& panelSize)
    : window(mode, title),
      board(boardSize, boardSize),
      panel(panelPos, panelSize) {
}

void monopoly::GameView::start() {
    if (!window.isOpen()) {
        std::cerr << "Window failed to open" << std::endl;
        return;
    }

    window.setFramerateLimit(60);
    try {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            board.draw(window);
            panel.draw(window);
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in game loop: " << e.what() << std::endl;
    }
}
