#pragma once

#include "MonopolyObserver.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>
#include <functional>

// Forward declarations
namespace monopoly {
    class Game;
    struct PlayerMoveEvent;
    struct PropertyPurchaseEvent;
    struct BankruptcyEvent;
    struct DiceRollEvent;
    struct MoneyChangeEvent;
    struct GameOverEvent;
}

namespace monopoly {

class Board final : public MonopolyObserver {
private:
    // Singleton implementation
    static std::unique_ptr<Board> instance;
    Board();

    // UI State
    enum class UIState {
        MAIN_MENU,
        AWAITING_ROLL,
        ROLLING_DICE,
        AWAITING_DECISION,
        GAME_OVER
    };
    UIState currentState{UIState::MAIN_MENU};

    // Core SFML components
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<ResourceManager> resources;

    // UI Components
    struct Button {
        sf::RectangleShape shape;
        sf::Text label;
        bool enabled{true};
        std::function<void()> onClick;
    };
    std::unordered_map<std::string, Button> buttons;

    struct BoardUI {
        sf::RectangleShape background;
        std::vector<sf::RectangleShape> squares;
        std::vector<sf::Text> labels;
        std::vector<sf::CircleShape> playerTokens;
    } board;

    struct DiceUI {
        std::array<sf::RectangleShape, 2> dice;
        sf::Clock animationClock;
        sf::Time animationDuration;
        bool isRolling{false};
        void update();
        void render(sf::RenderTarget& target);
    } diceUI;

    struct MessageUI {
        sf::Text text;
        sf::RectangleShape background;
        sf::Clock displayClock;
        bool isVisible{false};
        void show(const std::string& message, sf::Time duration);
        void update();
        void render(sf::RenderTarget& target);
    } messageUI;

    // Initialization
    void initWindow();
    void initBoard();
    void initButtons();
    void initDice();
    void loadResources();

    // Input handling
    void handleMouseClick(const sf::Event::MouseButtonEvent& event);
    void handleKeyPress(const sf::Event::KeyEvent& event);
    void processInput();

    // Rendering
    void renderBoard();
    void renderProperties();
    void renderPlayers();
    void renderUI();
    void updatePropertyStates();

    // UI state management
    void updateUIState(UIState newState);
    void updateButtonStates();
    
public:
    // Singleton pattern
    static Board& getInstance();
    ~Board() override;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    // Main interface
    void initialize();
    void update();
    void render();
    void processEvents();
    [[nodiscard]] bool isOpen() const;
    void close();

    // Observer pattern implementation
    void onEvent(const PlayerMoveEvent& event) override;
    void onEvent(const PropertyPurchaseEvent& event) override;
    void onEvent(const BankruptcyEvent& event) override;
    void onEvent(const DiceRollEvent& event) override;
    void onEvent(const MoneyChangeEvent& event) override;
    void onEvent(const GameOverEvent& event) override;

    // UI interaction
    void showMessage(const std::string& message, sf::Time duration = sf::seconds(3));
    bool showDialog(const std::string& message, const std::vector<std::string>& options);
    void showError(const std::string& error);
};

} // namespace monopoly