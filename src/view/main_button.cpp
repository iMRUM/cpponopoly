#include "../../include/view/View.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Monopoly");
    monopoly::BoardView board(960.f, 960.f);
    monopoly::UserView panel(sf::Vector2f(1000.f, 100.f), sf::Vector2f(640.f, 640.f));

    monopoly::View::getInstance(window, board, panel).start();


    return 0;
}