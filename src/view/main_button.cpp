#include <SFML/Graphics.hpp>
#include <memory>
#include "../../include/view/components/Button.hpp"
#include "../../include/view/components/StreetSquare.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Street Square Test");

    // Create street squares to test different board sides
    std::vector<std::unique_ptr<StreetSquare>> squares;

    // Bottom side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(300, 680),
        "Park Place",
        1,
        sf::Color::Blue
    ));
    squares.back()->setBoardSide(BoardSide::Bottom);

    // Left side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, 300),
        "St. James Place",
        2,
        sf::Color::Cyan
    ));
    squares.back()->setBoardSide(BoardSide::Left);

    // Top side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(300, 0),
        "Kentucky Avenue",
        3,
        sf::Color::Red
    ));
    squares.back()->setBoardSide(BoardSide::Top);

    // Right side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(680, 300),
        "Ventnor Avenue",
        4,
        sf::Color::Yellow
    ));
    squares.back()->setBoardSide(BoardSide::Right);

    // Test variables
    int activeSquareIndex = 0;
    int houseCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle keyboard events for testing
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        // Cycle through squares
                        activeSquareIndex = (activeSquareIndex + 1) % squares.size();
                        break;
                    case sf::Keyboard::H:
                        // Add/remove houses on active square
                        houseCount = (houseCount + 1) % 6;  // 0-4 houses, 5 = hotel
                        squares[activeSquareIndex]->setHouses(houseCount);
                        break;
                }
            }

            // Handle square events
            for (auto& square : squares) {
                square->handleEvent(event);
            }
        }

        window.clear(sf::Color::White);

        // Draw squares
        for (auto& square : squares) {
            square->draw(window);
        }

        // Draw grid for reference
        sf::RectangleShape line(sf::Vector2f(800, 1));
        line.setFillColor(sf::Color(200, 200, 200));

        for (int y = 0; y < 800; y += 80) {
            line.setPosition(0, y);
            window.draw(line);
        }

        line.setSize(sf::Vector2f(1, 800));
        for (int x = 0; x < 800; x += 80) {
            line.setPosition(x, 0);
            window.draw(line);
        }

        window.display();
    }

    return 0;
}