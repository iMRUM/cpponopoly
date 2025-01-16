#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <string>

namespace monopoly {

    enum class PlayerAction {
        ROLL_DICE,
        BUY_PROPERTY,
        END_TURN,
        NONE
    };

    class Gui {
    public:
        static Gui& getInstance();
    
        PlayerAction getPlayerAction();
        void updateBoard(size_t size, std::function<void*(int)> square_getter);
        void updatePlayerInfo(const std::string& name, int balance, int position);
        void enableRollDice(bool enable);
        void enableBuyProperty(bool enable);
        void enableEndTurn(bool enable);
        void showGameOver(const std::string& winner_name);
        void refresh();

        // Delete copy/move operations
        Gui(const Gui&) = delete;
        Gui& operator=(const Gui&) = delete;

    private:
        Gui();
        ~Gui();
    
        static std::unique_ptr<Gui> instance;
        std::unique_ptr<sf::RenderWindow> window;
        sf::Font font;
        std::vector<sf::RectangleShape> squares;
        sf::Text player_info;
        sf::RectangleShape dice_button;
        sf::RectangleShape buy_button;
        sf::RectangleShape end_turn_button;
    
        void handleEvents();
        void draw();
        void initializeWindow();
        void initializeButtons();
    };

} // namespace monopoly