#include <SFML/Graphics.hpp>
#include <memory>
#include "../../include/view/components/Button.hpp"
#include "../../include/view/components/StreetSquare.hpp"
#include "../../include/view/components/CommunityChestSquare.hpp"
#include "../../include/view/components/IncomeTaxSquare.hpp"
#include "../../include/view/components/ChanceSquare.hpp"
#include "../../include/view/components/RailroadSquare.hpp"
#include "../../include/view/components/JailSquare.hpp"
#include "../../include/view/components/FreeParkingSquare.hpp"
#include "../../include/view/components/GoToJailSquare.hpp"
#include "../../include/view/components/GoSquare.hpp"
#include "../../include/view/components/UtilitySquare.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1200), "Street Square Test");
    window.setFramerateLimit(30);


    //surely works from here:
    // Create street squares to test different board sides
    std::vector<std::unique_ptr<BoardSquare> > squares;

    // Bottom side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(310, 0),
        "Park Place",
        1,
        "100",
        sf::Color::Blue, BoardSide::Top));

    // Left side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, 250),
        "St. James Place",
        2,
        "150",
        sf::Color::Cyan, BoardSide::Left
    ));

    // Top side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(310, 500),
        "Kentucky\n  Avenue",
        3,
        "200",
        sf::Color::Red, BoardSide::Bottom
    ));

    // Right side street
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(500, 250),
        "Ventnor Avenue",
        4,
        "250",
        sf::Color::Yellow, BoardSide::Right
    ));
    squares.push_back(std::make_unique<CommunityChestSquare>(sf::Vector2f(240, 0), 5, BoardSide::Top));
    squares.push_back(std::make_unique<CommunityChestSquare>(sf::Vector2f(0, 240), 5, BoardSide::Left));
    squares.push_back(std::make_unique<CommunityChestSquare>(sf::Vector2f(240, 400), 6, BoardSide::Bottom));
    squares.push_back(std::make_unique<CommunityChestSquare>(sf::Vector2f(400, 240), 5, BoardSide::Right));
    squares.push_back(std::make_unique<IncomeTaxSquare>(sf::Vector2f(650, 0), 8));
    squares.push_back(std::make_unique<ChanceSquare>(sf::Vector2f(240, 0), 5, BoardSide::Top, sf::Color::Green));
    squares.push_back(std::make_unique<ChanceSquare>(sf::Vector2f(0, 240), 5, BoardSide::Left, sf::Color::Green));
    squares.push_back(std::make_unique<ChanceSquare>(sf::Vector2f(240, 400), 6, BoardSide::Bottom, sf::Color::Green));
    squares.push_back(std::make_unique<ChanceSquare>(sf::Vector2f(400, 240), 5, BoardSide::Right, sf::Color::Green));
    squares.push_back(std::make_unique<RailroadSquare>(sf::Vector2f(240, 0), "  B. & O.\nRAILROAD", 5, BoardSide::Top));
    squares.push_back(std::make_unique<RailroadSquare>(sf::Vector2f(0, 240)," PENNSYLVANIA\n  RAILROAD", 5, BoardSide::Left));
    squares.push_back(
        std::make_unique<RailroadSquare>(sf::Vector2f(240, 400), " READING\nRAILROAD", 6, BoardSide::Bottom));
    squares.push_back(std::make_unique<RailroadSquare>(sf::Vector2f(400, 240),"SHORT\n LINE", 5, BoardSide::Right));
    squares.push_back(std::make_unique<JailSquare>(sf::Vector2f(700, 700),10));
    squares.push_back(std::make_unique<FreeParkingSquare>(sf::Vector2f(700, 700),10));
    squares.push_back(std::make_unique<GoToJailSquare>(sf::Vector2f(700, 700),10));
    squares.push_back(std::make_unique<GoSquare>(sf::Vector2f(700, 700),10));
    squares.push_back(std::make_unique<UtilitySquare>(sf::Vector2f(240, 0), "ELECTRIC\nCOMPANY", 5, BoardSide::Top));
    squares.push_back(std::make_unique<UtilitySquare>(sf::Vector2f(0, 240),"  WATER\nCOMPANY", 5, BoardSide::Left));
    squares.push_back(
        std::make_unique<UtilitySquare>(sf::Vector2f(240, 400), "ELECTRIC\nCOMPANY", 6, BoardSide::Bottom));
    squares.push_back(std::make_unique<UtilitySquare>(sf::Vector2f(400, 240),"  WATER\nCOMPANY", 5, BoardSide::Right));

    // Test variables
    int activeSquareIndex = 0;
    int houseCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            /*/ Handle keyboard events for testing
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        // Cycle through squares
                        activeSquareIndex = (activeSquareIndex + 1) % squares.size();
                        break;
                    case sf::Keyboard::H:
                        // Add/remove houses on active square
                        houseCount = (houseCount + 1) % 6; // 0-4 houses, 5 = hotel
                        squares[activeSquareIndex]->setHouses(houseCount);
                        break;
                }
            }*/

            // Handle square events
            for (auto &square: squares) {
                square->handleEvent(event);
            }
        }

        window.clear(sf::Color::White);
        /*Electric company logo:
        // Draw all components
        window.draw(bulb);
        window.draw(base);
        window.draw(thread1);
        window.draw(thread2);
        window.draw(filament1);
        window.draw(filament2);
*/
        // Draw squares
        for (auto &square: squares) {
            square->draw(window);
        }

        /* Draw grid for reference
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
        }*/

        window.display();
    }


    return 0;
}
