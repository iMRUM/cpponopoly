#include "../../include/view/View.hpp"
monopoly::View* monopoly::View::instance = nullptr;
monopoly::View::View(sf::RenderWindow &window, BoardView &board, UserView &panel): window(window), board(board), panel(panel) {
}

void monopoly::View::start() {
    window.setFramerateLimit(60);
    window.clear(sf::Color::White);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        board.draw(window);
        panel.draw(window);
        window.display();
    }
}
