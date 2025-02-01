#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <random>
#include <ctime>
#include <array>
#include "components/BoardView.hpp"
#include "components/UserView.hpp"

namespace monopoly {
    class View {
    private:
        sf::RenderWindow& window;
        BoardView& board;
        UserView& panel;
        // Singleton implementation
        static View *instance;

        // Private constructor to prevent instantiation
        View(sf::RenderWindow &window, BoardView &board, UserView &panel);

        // Delete copy constructor and assignment operator
        View(const View &) = delete;

        View &operator=(const View &) = delete;

    public:
        void start();
        bool isKeyPressed(sf::Keyboard::Key key);
        static View& getInstance(sf::RenderWindow &window, BoardView &board, UserView &panel) {
            if (instance == nullptr) {
                instance = new View(window, board, panel);
            }
            return *instance;
        }

    };
}
