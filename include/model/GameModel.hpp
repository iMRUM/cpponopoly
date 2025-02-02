#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "MonopolyRules.hpp"
#include "Board.hpp"
#include "Player.hpp"



namespace monopoly{
    struct Dice {
        int first;
        int second;
        [[nodiscard]] bool isDoubles() const { return first == second; }
        [[nodiscard]] int getTotal() const { return first + second; }
    };
class GameModel{ // Singleton class
private:
    static std::unique_ptr<GameModel> instance;
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Player>> players;
    std::unordered_map<int, std::vector<int>> ownership_map; //player_id, owned properties square_ids
    std::unordered_map<int, int> owned_by_map; //square_id, owner
    /**
     * Encapsulates all game state information.
     * Helps track the current game situation and validate actions.
     */


    struct GameState {
        bool initialized{false};
        bool started{false};
        bool over{false};
        int winner{-1};

        // Turn-specific state
        int current_player_id{0};
        int current_square_id{0};
        bool has_rolled{false};
        bool awaiting_action{false};  // Indicates player needs to make a decision
        bool has_another_turn{false};
        int current_dice_result{0};

        void reset() {
            initialized = false;
            started = false;
            over = false;
            winner = -1;
            resetTurnState();
        }

        void resetTurnState() {
            current_player_id = 0;
            current_square_id = 0;
            has_rolled = false;
            awaiting_action = false;
            has_another_turn = false;
            current_dice_result = 0;
        }
    } state{};

    // Random number generation
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};
    std::uniform_int_distribution<> dice_dist{1, 6};

    GameModel();

    // Basic Player and square management
    void addPlayer(const std::string &name, int id);
    void addSquare(std::unique_ptr<Square>);
    void addRailroad(const std::string &name, int position, int price, int baseRent);
    void addStreet(const std::string &name, int position, int price, int baseRent, int house_cost, SquareGroups color);
    void addUtility(const std::string &name, int position);
    void addSpecialSquare(const std::string &name, int position, SpecialSquareType type);


    //Turns management:
    void handleTurn();
    Dice rollDice();

    void handleDiceRoll();
    void handleDouble();
    void isGameWon();
    void handleBankruptcy(int player_id);

    //Movement management:
    void moveSteps(int steps, int player_id);
    void movedPastGo(Player &player);


    //Landing management:
    void landOn(int pos, Player &player);

    void landOnProperty(Property &property, Player &player);
    void payRent(Property &property, Player &player);
    int getRailroadCount(int property_id, int player_id);
    void buyProperty(Property &property, Player &player);
    void buildOnStreet(int street_id, int player_id);

    void landOnSpecialSquare(SpecialSquare &special_square, Player &player);//TODO
    void landOnFreeParking();
    void landOnInJailJustVisit();
    void landOnLuxuryTax();
    void landOnChance(); //TODO
    void landOnGoToJail();//TODO
    void goToJail(Player &player);//TODO
    void outOfJail(Player &player);//TODO
    void payFine(int amount, Player& player);

public:
    static std::unique_ptr<GameModel> getInstance();
    // Delete copy/move operations
    GameModel(const GameModel&) = delete;
    GameModel& operator=(const GameModel&) = delete;
    // Basic game initialization and states
    bool initializeGame(size_t size_players, size_t board_size = 40);
    void addPlayers(size_t num_players);
    bool startGame();
    bool endGame();
    void nextTurn();

    // Getters
    [[nodiscard]] size_t getPlayersCount() const { return players.size(); }
    Square& getSquareAt(const int index) {return *(board->getSquare(index));}
    [[nodiscard]] bool isGameInitialized() const {return state.initialized;}
    [[nodiscard]] bool isGameStarted() const {return state.started;}
    [[nodiscard]] bool isGameOver() const {return state.over;}
    [[nodiscard]] int getCurrentPlayerIndex() const {return state.current_player_id;}
    [[nodiscard]] size_t getBoardSize() const { return board->getSize(); }

    //to be revised:
    [[nodiscard]] bool hasRolled() const { return state.has_rolled; }
    [[nodiscard]] bool isAwaitingAction() const { return state.awaiting_action; }
    [[nodiscard]] bool canBuyProperty() const;

    bool canBuildOnStreet(Street &street, const Player &player);
    bool hasMonopoly(int player_id, int square_id) const;
    bool mustPayRent(int square_id) const;
    int calculateCurrentRent() const;

    Player &getCurrentPlayer();

    int getWinner() const { return state.winner; }
};
}