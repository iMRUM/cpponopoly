#pragma once
#include "MonopolyObserver.hpp"
#include <SFML/Graphics.hpp>
#include <array>

// SFML type aliases
using Rectangle = sf::RectangleShape;
using Circle = sf::CircleShape;
using Font = sf::Font;
using Text = sf::Text;
using RenderWindow = sf::RenderWindow;

namespace monopoly {

    class Gui : public MonopolyObserver {
    private:
        RenderWindow window;
        Font font;

        // SFML UI Elements
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
        void initLabels();
        // Game state tracking
        bool isWindowOpen;
        std::string currentMessage;

        // UI initialization helpers
        void initWindow();
        void initBoard();
        void initPlayers();
        void initUI();

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