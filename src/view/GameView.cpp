#include "../../include/view/GameView.hpp"

namespace monopoly {
    std::unique_ptr<GameView> GameView::instance = nullptr;

    GameView::GameView(sf::VideoMode mode, const std::string &title, float boardSize,
                       const sf::Vector2f &panelPos, const sf::Vector2f &panelSize)
        : board(boardSize, boardSize)
          , panel(panelPos, panelSize) {
    }

    std::unique_ptr<GameView> GameView::getInstance(sf::VideoMode mode,
                                                    const std::string &title, float boardSize,
                                                    const sf::Vector2f &panelPos, const sf::Vector2f &panelSize) {
        if (!instance) {
            instance = std::unique_ptr<GameView>(
                new GameView(mode, title, boardSize, panelPos, panelSize));
        }
        return std::move(instance);
    }

    void GameView::start() {
        window.create(sf::VideoMode(1920, 1080), "Monopoly");
        window.setFramerateLimit(60);
    }

    void GameView::update() {
        board.updateView();
        panel.updateView();
    }

    void GameView::render() {
        window.clear(sf::Color::White);
        board.draw(window);
        panel.draw(window);
        window.display();
    }

    void GameView::updateBoardDisplay() {
        board.updateView();
    }

    void GameView::showDiceRoll(int value) {
        std::cout << value << std::endl;
    }

    void GameView::displayPropertyCard(int propertyId) {
        std::cout << propertyId << std::endl;
    }

    void GameView::askPurchaseDecision(int propertyId, int price) {
        std::cout << propertyId << std::endl;
    }

    void GameView::handleEvent(const sf::Event &event) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
