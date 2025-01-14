#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "Board.hpp"
#include "utils/Id.hpp"
#include "player/Player.hpp"
class Square;
//ColorGroups should be registered here/store here a registry
namespace monopoly{
class Game { // Singleton class
private:
    static std::unique_ptr<Game> instance;
    bool game_initialized = false;
    bool game_started = false;
    bool game_over = false;
    int current_player_index = 0;
    Board* board;
    std::vector<std::unique_ptr<Player>> players;
    std::unordered_map<ColorGroupID, std::vector<SquareID>, ColorGroupID::Hash>;
    // Random number generation fields
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> dice_dist;

    Game() {
        board = Board::getInstance();
    }

public:
    static Game& getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Game>(new Game());
        }
        return *instance;
    }


    // Basic game initialization and states
    bool initializeGame(size_t size_players);
    bool startGame();

    bool endGame();

    // Basic Player and turn management
    void addPlayer(std::unique_ptr<Player> player);
    [[nodiscard]] size_t getPlayerCount() const { return players.size(); }
    Player& getCurrentPlayer();
    void nextTurn();

    // Basic dice rolling
    struct Dice {
        int first;
        int second;
        [[nodiscard]] bool isDoubles() const { return first == second; }
        [[nodiscard]] int getTotal() const { return first + second; }
    };
    Dice rollDice();

    // Delete copy/move operations
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Getters

    [[nodiscard]] bool isGameInitialized() const {
        return game_initialized;
    }

    [[nodiscard]] bool isGameStarted() const {
        return game_started;
    }

    [[nodiscard]] bool isGameOver() const {
        return game_over;
    }

    [[nodiscard]] int currentPlayerIndex() const {
        return current_player_index;
    }

    [[nodiscard]] Board& getBoard() const {
        return *board;
    }
    Square* getSquareAt(const int index) {
        return board->getSquare(index);
    }
    [[nodiscard]] const std::vector<std::unique_ptr<Player>>& getPlayers() const;

};
}
