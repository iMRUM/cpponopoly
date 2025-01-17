#pragma once
#include "MonopolyObserver.hpp"
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

    class Gui : public MonopolyObserver {
    private:
        RenderWindow window;
        Font font;

        // SFML UI Elements
        // In Gui.hpp, add these members to the Gui class:x
        // Dice representation
        Rectangle dice[2];  // Using rectangles for dice faces
        int diceValues[2];       // Current values of dice
        bool diceRolling;        // Animation state
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

        void renderDiceDots(RenderTarget &target, const Rectangle &die, int value);

        void rollDice();

        void updateDiceAnimation();

        void renderDice();

        void initLabels();

    public:
        Gui();
        ~Gui() override;

        // Window management
        void render();
        bool isOpen() const;
        void processEvents();
        void close();

        // Observer pattern implementation
        void onEvent(const PlayerMoveEvent& event) override;
        void onEvent(const PropertyPurchaseEvent& event) override;
        void onEvent(const BankruptcyEvent& event) override;
        void onEvent(const DiceRollEvent& event) override;
        void onEvent(const MoneyChangeEvent& event) override;
        void onEvent(const GameOverEvent& event) override;

        // UI interaction methods
        void showDialog(const std::string& message);
        bool getYesNoResponse(const std::string& question);
        void displayError(const std::string& error);
    };

} // namespace monopoly