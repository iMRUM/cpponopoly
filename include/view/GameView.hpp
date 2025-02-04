#pragma once
#include <SFML/Graphics.hpp>
#include "components/BoardView.hpp"
#include "components/UserView.hpp"
/**
 * @file GameView.hpp
 * @brief Main view class for the Monopoly game's graphical interface
 *
 * GameView implements the View component of the MVC pattern using SFML.
 * It manages the game's visual representation including the board, player panels,
 * and UI components through a Singleton pattern.
 */
namespace monopoly {

/**
 * @class GameView
 * @brief Primary view class managing game visualization and UI components
 *
 * Coordinates rendering of:
 * - Game board (BoardView)
 * - Player interface panel (UserView)
 * - Game state updates
 * - Player interactions
 */
class GameView {
private:
    /** @brief SFML render window */
    sf::RenderWindow window;

    /** @brief Game board visualization component */
    BoardView board;

    /** @brief Player interface panel component */
    UserView panel;

    /** @brief Singleton instance pointer */
    static std::unique_ptr<GameView> instance;

    /**
     * @brief Private constructor for Singleton pattern
     * @param mode SFML video mode settings
     * @param title Window title
     * @param boardSize Board dimensions
     * @param panelPos User panel position
     * @param panelSize User panel dimensions
     */
    GameView(sf::VideoMode mode, const std::string &title, float boardSize,
             const sf::Vector2f &panelPos, const sf::Vector2f &panelSize);

public:
    /**
     * @brief Get singleton instance
     * @return Unique pointer to GameView instance
     */
    static std::unique_ptr<GameView> getInstance(sf::VideoMode mode,
                                               const std::string &title, float boardSize,
                                               const sf::Vector2f &panelPos, const sf::Vector2f &panelSize);

    /**
     * @brief Initialize and show the game window
     */
    void start();

    /**
     * @brief Update player token position on board
     * @param player_id Player identifier
     * @param new_square_id New square position
     * @param old_square_id Previous square position
     */
    void updatePlayerAtBoardSquare(int player_id, int new_square_id, int old_square_id);

    /**
     * @brief Close the game window
     */
    void close() { window.close(); }

    /**
     * @brief Check if window is still open
     * @return True if window is open
     */
    bool isOpen() const { return window.isOpen(); }

    /**
     * @brief Poll for window events
     * @param event SFML event object to populate
     * @return True if event was received
     */
    bool pollEvent(sf::Event &event) { return window.pollEvent(event); }

    /**
     * @brief Update player's balance display
     * @param balance New balance value
     */
    void updateBalanceBox(int balance);

    /**
     * @brief Update player name display
     * @param name Player name
     */
    void updateNameBox(std::string &name);

    /**
     * @brief Update player info display
     * @param name Player name
     */
    void updatePlayerName(const std::string &name);

    /**
     * @brief Update message in panel
     * @param prompt Message to display
     */
    void updatePanelMessage(std::string &prompt);

    /**
     * @brief Update visual state of all components
     */
    void update();

    /**
     * @brief Render frame to window
     */
    void render();

    /**
     * @brief Update board display
     */
    void updateBoardDisplay();

    /**
     * @brief Show dice roll result
     * @param value Dice total
     */
    void showDiceRoll(int value);

    /**
     * @brief Display property card
     * @param propertyId Property identifier
     */
    void displayPropertyCard(int propertyId);

    /**
     * @brief Show property purchase dialog
     * @param propertyId Property identifier
     * @param price Property cost
     */
    void askPurchaseDecision(int propertyId, int price);

    /**
     * @brief Handle SFML window events
     * @param event SFML event object
     */
    void handleEvent(const sf::Event & event);
};

} // namespace monopoly