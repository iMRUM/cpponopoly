#include "../../../include/view/components/BoardView.hpp"

#include "../../../include/view/components/ChanceSquare.hpp"
#include "../../../include/view/components/CommunityChestSquare.hpp"
#include "../../../include/view/components/FreeParkingSquare.hpp"
#include "../../../include/view/components/GoSquare.hpp"
#include "../../../include/view/components/GoToJailSquare.hpp"
#include "../../../include/view/components/IncomeTaxSquare.hpp"
#include "../../../include/view/components/JailSquare.hpp"
#include "../../../include/view/components/MonopolyBoard.hpp"
#include "../../../include/view/components/RailroadSquare.hpp"
#include "../../../include/view/components/StreetSquare.hpp"
#include "../../../include/view/components/UtilitySquare.hpp"

monopoly::BoardView::BoardView(float width, float height): SFComposite(sf::Vector2f(0.f, 0.f), sf::Vector2f(width, height)) {
    add(std::make_unique<MonopolyBoard>());
    // Create all squares
    createBottomSquares();
    createLeftSquares();
    createTopSquares();
    createRightSquares();
    createCornerSquares();
}

void monopoly::BoardView::createBottomSquares() {
    float startX = 120.0f;  // Start after GO corner

    // Bottom row squares (left to right)
    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX, 840), "Mediterranean\nAvenue", 1, "60",
        sf::Color(150, 83, 55), BoardSide::Bottom));  // Brown

    add(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(startX + 80, 840), 2, BoardSide::Bottom));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 160, 840), "Baltic\nAvenue", 3, "60",
        sf::Color(150, 83, 55), BoardSide::Bottom));  // Brown

    add(std::make_unique<IncomeTaxSquare>(
        sf::Vector2f(startX + 240, 840), 4, BoardSide::Bottom));

    add(std::make_unique<RailroadSquare>(
        sf::Vector2f(startX + 320, 840), "Reading\nRailroad", 5, BoardSide::Bottom));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 400, 840), "Oriental\nAvenue", 6, "100",
        sf::Color::Cyan, BoardSide::Bottom));

    add(std::make_unique<ChanceSquare>(
        sf::Vector2f(startX + 480, 840), 7, BoardSide::Bottom, sf::Color::Blue));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 560, 840), "Vermont\nAvenue", 8, "100",
        sf::Color::Cyan, BoardSide::Bottom));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 640, 840), "Connecticut\nAvenue", 9, "120",
        sf::Color::Cyan, BoardSide::Bottom));
}

void monopoly::BoardView::createLeftSquares() {
    float startY = 120.0f;  // Start after Jail

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY), "St. Charles\nPlace", 11, "140",
        sf::Color::Magenta, BoardSide::Left));

    add(std::make_unique<UtilitySquare>(
        sf::Vector2f(0, startY + 80), "Electric\nCompany", 12, BoardSide::Left));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 160), "States\nAvenue", 13, "140",
        sf::Color::Magenta, BoardSide::Left));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 240), "Virginia\nAvenue", 14, "160",
        sf::Color::Magenta, BoardSide::Left));

    add(std::make_unique<RailroadSquare>(
        sf::Vector2f(0, startY + 320), "Pennsylvania\nRailroad", 15, BoardSide::Left));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 400), "St. James\nPlace", 16, "180",
        sf::Color::Black, BoardSide::Left));

    add(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(0, startY + 480), 17, BoardSide::Left));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 560), "Tennessee\nAvenue", 18, "180",
        sf::Color::Black, BoardSide::Left));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(0, startY + 640), "New York\nAvenue", 19, "200",
        sf::Color::Black, BoardSide::Left));
}

void monopoly::BoardView::createTopSquares() {
    float startX = 120.0f;  // Start after Free Parking

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX, 0), "Kentucky\nAvenue", 21, "220",
        sf::Color::Red, BoardSide::Top));

    add(std::make_unique<ChanceSquare>(
        sf::Vector2f(startX + 80, 0), 22, BoardSide::Top, sf::Color::Blue));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 160, 0), "Indiana\nAvenue", 23, "220",
        sf::Color::Red, BoardSide::Top));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 240, 0), "Illinois\nAvenue", 24, "240",
        sf::Color::Red, BoardSide::Top));

    add(std::make_unique<RailroadSquare>(
        sf::Vector2f(startX + 320, 0), "B. & O.\nRailroad", 25, BoardSide::Top));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 400, 0), "Atlantic\nAvenue", 26, "260",
        sf::Color::Yellow, BoardSide::Top));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 480, 0), "Ventnor\nAvenue", 27, "260",
        sf::Color::Yellow, BoardSide::Top));

    add(std::make_unique<UtilitySquare>(
        sf::Vector2f(startX + 560, 0), "Water\nWorks", 28, BoardSide::Top));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(startX + 640, 0), "Marvin\nGardens", 29, "280",
        sf::Color::Yellow, BoardSide::Top));
}

void monopoly::BoardView::createRightSquares() {
    float startY = 120.0f;  // Start after Go To Jail

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY), "Pacific\nAvenue", 31, "300",
        sf::Color::Green, BoardSide::Right));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 80), "North Carolina\nAvenue", 32, "300",
        sf::Color::Green, BoardSide::Right));

    add(std::make_unique<CommunityChestSquare>(
        sf::Vector2f(840, startY + 160), 33, BoardSide::Right));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 240), "Pennsylvania\nAvenue", 34, "320",
        sf::Color::Green, BoardSide::Right));

    add(std::make_unique<RailroadSquare>(
        sf::Vector2f(840, startY + 320), "Short Line", 35, BoardSide::Right));

    add(std::make_unique<ChanceSquare>(
        sf::Vector2f(840, startY + 400), 36, BoardSide::Right, sf::Color::Blue));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 480), "Park Place", 37, "350",
        sf::Color::Blue, BoardSide::Right));

    add(std::make_unique<IncomeTaxSquare>(
        sf::Vector2f(840, startY + 560), 38, BoardSide::Right));

    add(std::make_unique<StreetSquare>(
        sf::Vector2f(840, startY + 640), "Boardwalk", 39, "400",
        sf::Color::Blue, BoardSide::Right));
}

void monopoly::BoardView::createCornerSquares() {
    // GO (bottom right)
    add(std::make_unique<GoSquare>(
        sf::Vector2f(840, 840), 0));

    // Jail (bottom left)
    add(std::make_unique<JailSquare>(
        sf::Vector2f(0, 840), 10));

    // Free Parking (top left)
    add(std::make_unique<FreeParkingSquare>(
        sf::Vector2f(0, 0), 20));

    // Go To Jail (top right)
    add(std::make_unique<GoToJailSquare>(
        sf::Vector2f(840, 0), 30));
}

bool monopoly::BoardView::handleEvent(const sf::Event &event) {
    if (!isComponentEnabled()) return false;

    // Handle any Go To Jail specific events here
    // For now, just check if the square was clicked
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        return contains(mousePos);
    }
    return false;
}

void monopoly::BoardView::updateView() {
}

