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
    class GameView {
    private:
        sf::RenderWindow window;
        BoardView board;
        UserView panel;
        static std::unique_ptr<GameView> instance;

        GameView(sf::VideoMode mode, const std::string& title, float boardSize, const sf::Vector2f& panelPos, const sf::Vector2f& panelSize);

    public:
        static std::unique_ptr<GameView> getInstance(sf::VideoMode mode, const std::string& title,
            float boardSize, const sf::Vector2f& panelPos, const sf::Vector2f& panelSize) {
            if (!instance) {
                instance = std::unique_ptr<GameView>(new GameView(mode, title, boardSize, panelPos, panelSize));
            }
            return std::move(instance);
        }
        void start();
        bool isKeyPressed(sf::Keyboard::Key key);
    };

        //
    };

