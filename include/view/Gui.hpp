#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <random>
#include <ctime>
#include <array>

// SFML type aliases
using Rectangle = sf::RectangleShape;
using Circle = sf::CircleShape;
using Font = sf::Font;
using Text = sf::Text;
using Clock = sf::Clock;
using Time = sf::Time;
using Vector2f = sf::Vector2f;
using Color = sf::Color;
using RenderTarget = sf::RenderTarget;
using RenderWindow = sf::RenderWindow;

namespace monopoly {

    class Gui{
    private:
        // Singleton implementation
        static Gui* instance;

        // Private constructor to prevent instantiation
        Gui();

        // Delete copy constructor and assignment operator
        Gui(const Gui&) = delete;
        Gui& operator=(const Gui&) = delete;

        RenderWindow window;
        Font font;

        // SFML UI Elements
        Rectangle dice[2];
        int diceValues[2];
        bool diceRolling;
        Clock diceAnimationClock;
        Time diceAnimationDuration;
        Rectangle board;
        Rectangle current_player_info;
        Rectangle buy_button;
        Rectangle end_turn_button;
        Rectangle roll_button;
        Rectangle history_panel;
        std::vector<Rectangle> squares;
        std::vector<Circle> playerTokens;
        Text messageText;
        std::vector<Text> squareLabels;

        // Helper function for text wrapping
        void setWrappedText(Text& text, const std::string& str, float width);

        // Game state tracking
        bool isWindowOpen;
        std::string currentMessage;

        // UI initialization helpers
        void initWindow();
        void initBoard();
        void initPlayers();
        void initUI();
        void initDice();
        void initLabels();

        void renderDiceDots(RenderTarget& target, const Rectangle& die, int value);
        void rollDice();
        void updateDiceAnimation();
        void renderDice();

    public:
        // Singleton access method
        static Gui& getInstance() {
            if (instance == nullptr) {
                instance = new Gui();
            }
            return *instance;
        }

        // Destructor
        ~Gui();;

        // Static cleanup method
        static void cleanup() {
            delete instance;
            instance = nullptr;
        }

        // Window management
        void render();
        bool isOpen() const;
        void processSfmlEvents();
        void close();


    };

} // namespace monopoly