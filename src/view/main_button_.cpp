#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
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
#include "../../include/view/components/MonopolyBoard.hpp"

void createBottomSquares(std::vector<std::unique_ptr<BoardSquare>>& squares) {
    float startX = 120.0f;  // Start after GO corner

    // Bottom row squares (left to right)
    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX, 840), "Mediterranean\nAvenue", 1, "60",
        sf::Color(150, 83, 55), BoardSide::Bottom));  // Brown

    squares.push_back(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(startX + 80, 840), 2, BoardSide::Bottom));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 160, 840), "Baltic\nAvenue", 3, "60",
        sf::Color(150, 83, 55), BoardSide::Bottom));  // Brown

    squares.push_back(std::make_unique<IncomeTaxSquare>(
        sf::Vector2f(startX + 240, 840), 4, BoardSide::Bottom));

    squares.push_back(std::make_unique<RailroadSquare>(
        sf::Vector2f(startX + 320, 840), "Reading\nRailroad", 5, BoardSide::Bottom));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 400, 840), "Oriental\nAvenue", 6, "100",
        sf::Color::Cyan, BoardSide::Bottom));

    squares.push_back(std::make_unique<ChanceSquare>(
        sf::Vector2f(startX + 480, 840), 7, BoardSide::Bottom, sf::Color::Blue));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 560, 840), "Vermont\nAvenue", 8, "100",
        sf::Color::Cyan, BoardSide::Bottom));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 640, 840), "Connecticut\nAvenue", 9, "120",
        sf::Color::Cyan, BoardSide::Bottom));
}

void createLeftSquares(std::vector<std::unique_ptr<BoardSquare>>& squares) {
    float startY = 120.0f;  // Start after Jail

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY), "St. Charles\nPlace", 11, "140",
        sf::Color::Magenta, BoardSide::Left));

    squares.push_back(std::make_unique<UtilitySquare>(
        sf::Vector2f(0, startY + 80), "Electric\nCompany", 12, BoardSide::Left));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 160), "States\nAvenue", 13, "140",
        sf::Color::Magenta, BoardSide::Left));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 240), "Virginia\nAvenue", 14, "160",
        sf::Color::Magenta, BoardSide::Left));

    squares.push_back(std::make_unique<RailroadSquare>(
        sf::Vector2f(0, startY + 320), "Pennsylvania\nRailroad", 15, BoardSide::Left));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 400), "St. James\nPlace", 16, "180",
        sf::Color::Black, BoardSide::Left));

    squares.push_back(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(0, startY + 480), 17, BoardSide::Left));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 560), "Tennessee\nAvenue", 18, "180",
        sf::Color::Black, BoardSide::Left));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 640), "New York\nAvenue", 19, "200",
        sf::Color::Black, BoardSide::Left));
}

void createTopSquares(std::vector<std::unique_ptr<BoardSquare>>& squares) {
    float startX = 120.0f;  // Start after Free Parking

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX, 0), "Kentucky\nAvenue", 21, "220",
        sf::Color::Red, BoardSide::Top));

    squares.push_back(std::make_unique<ChanceSquare>(
        sf::Vector2f(startX + 80, 0), 22, BoardSide::Top, sf::Color::Blue));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 160, 0), "Indiana\nAvenue", 23, "220",
        sf::Color::Red, BoardSide::Top));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 240, 0), "Illinois\nAvenue", 24, "240",
        sf::Color::Red, BoardSide::Top));

    squares.push_back(std::make_unique<RailroadSquare>(
        sf::Vector2f(startX + 320, 0), "B. & O.\nRailroad", 25, BoardSide::Top));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 400, 0), "Atlantic\nAvenue", 26, "260",
        sf::Color::Yellow, BoardSide::Top));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 480, 0), "Ventnor\nAvenue", 27, "260",
        sf::Color::Yellow, BoardSide::Top));

    squares.push_back(std::make_unique<UtilitySquare>(
        sf::Vector2f(startX + 560, 0), "Water\nWorks", 28, BoardSide::Top));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 640, 0), "Marvin\nGardens", 29, "280",
        sf::Color::Yellow, BoardSide::Top));
}

void createRightSquares(std::vector<std::unique_ptr<BoardSquare>>& squares) {
    float startY = 120.0f;  // Start after Go To Jail

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY), "Pacific\nAvenue", 31, "300",
        sf::Color::Green, BoardSide::Right));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 80), "North Carolina\nAvenue", 32, "300",
        sf::Color::Green, BoardSide::Right));

    squares.push_back(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(840, startY + 160), 33, BoardSide::Right));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 240), "Pennsylvania\nAvenue", 34, "320",
        sf::Color::Green, BoardSide::Right));

    squares.push_back(std::make_unique<RailroadSquare>(
        sf::Vector2f(840, startY + 320), "Short Line", 35, BoardSide::Right));

    squares.push_back(std::make_unique<ChanceSquare>(
        sf::Vector2f(840, startY + 400), 36, BoardSide::Right, sf::Color::Blue));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 480), "Park Place", 37, "350",
        sf::Color::Blue, BoardSide::Right));

    squares.push_back(std::make_unique<IncomeTaxSquare>(
        sf::Vector2f(840, startY + 560), 38, BoardSide::Right));

    squares.push_back(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 640), "Boardwalk", 39, "400",
        sf::Color::Blue, BoardSide::Right));
}

void createCornerSquares(std::vector<std::unique_ptr<BoardSquare>>& squares) {
    // GO (bottom right)
    squares.push_back(std::make_unique<GoSquare>(
        sf::Vector2f(840, 840), 0));

    // Jail (bottom left)
    squares.push_back(std::make_unique<JailSquare>(
        sf::Vector2f(0, 840), 10));

    // Free Parking (top left)
    squares.push_back(std::make_unique<FreeParkingSquare>(
        sf::Vector2f(0, 0), 20));

    // Go To Jail (top right)
    squares.push_back(std::make_unique<GoToJailSquare>(
        sf::Vector2f(840, 0), 30));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(960, 960), "Monopoly Board");
    window.setFramerateLimit(60);

    std::vector<std::unique_ptr<BoardSquare>> squares;
    auto m_board = std::make_unique<MonopolyBoard>();

    // Create all squares
    createBottomSquares(squares);
    createLeftSquares(squares);
    createTopSquares(squares);
    createRightSquares(squares);
    createCornerSquares(squares);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle square events
            for (auto& square : squares) {
                square->handleEvent(event);
            }
        }

        window.clear(sf::Color::White);

        // Draw board first (background)
        m_board->draw(window);

        // Draw all squares
        for (auto& square : squares) {
            square->draw(window);
        }
        window.display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            std::cout << "SPACE WAS PRESSED" << std::endl;
        }
    }

    return 0;
}