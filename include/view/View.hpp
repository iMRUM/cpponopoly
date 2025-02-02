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
        sf::RenderWindow window;
        BoardView board;
        UserView panel;
        static std::unique_ptr<View> instance;

        View(sf::VideoMode mode, const std::string& title, float boardSize, const sf::Vector2f& panelPos, const sf::Vector2f& panelSize);

    public:
        static std::unique_ptr<View> getInstance(sf::VideoMode mode, const std::string& title,
            float boardSize, const sf::Vector2f& panelPos, const sf::Vector2f& panelSize) {
            if (!instance) {
                instance = std::unique_ptr<View>(new View(mode, title, boardSize, panelPos, panelSize));
            }
            return std::move(instance);
        }
        void start();
        bool isKeyPressed(sf::Keyboard::Key key);
    };

        //
    };

