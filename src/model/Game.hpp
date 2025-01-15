#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "Board.hpp"
#include "utils/Id.hpp"
#include "../include/registries/PropertyRegistry.hpp"
#include "../include/registries/PlayerRegistry.hpp"
#include "player/Player.hpp"
class Square;
//ColorGroups should be registered here/store here a registry
namespace monopoly{
class Game { // Singleton class
private:
    static std::unique_ptr<Game> instance;

    // Core game components
    std::unique_ptr<PropertyRegistry> property_registry;
    std::unique_ptr<PlayerRegistry> player_registry;
    Board* board;
    /**
     * Encapsulates all game state information.
     * Helps track the current game situation and validate actions.
     */
    struct GameState {
        bool initialized{false};
        bool started{false};
        bool over{false};
        int current_player_index{0};
        bool has_rolled{false};
        int doubles_count{0};
        bool can_buy_property{false};
        bool must_pay_rent{false};

        void reset() {
            initialized = false;
            started = false;
            over = false;
            current_player_index = 0;
            resetTurnState();
        }

        void resetTurnState() {
            has_rolled = false;
            doubles_count = 0;
            can_buy_property = false;
            must_pay_rent = false;
        }
    } state{};
    bool game_initialized = false; //D
    bool game_started = false;//D
    bool game_over = false;//D
    int current_player_index = 0;//D

    std::vector<std::unique_ptr<Player>> players;
    std::unordered_map<ColorGroupID, std::vector<SquareID>, ColorGroupID::Hash>;
    // Random number generation fields
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};
    std::uniform_int_distribution<> dice_dist{1, 6};

    Game();

public:
    static Game& getInstance();


    // Basic game initialization and states
    bool initializeGame(size_t size_players);
    bool startGame();

    bool endGame();

    // Basic Player and turn management
    void addPlayer(const std::string &player);
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
        return state.initialized;
    }

    [[nodiscard]] bool isGameStarted() const {
        return state.started;
    }

    [[nodiscard]] bool isGameOver() const {
        return state.over;
    }

    [[nodiscard]] int currentPlayerIndex() const {
        return state.current_player_index;
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
