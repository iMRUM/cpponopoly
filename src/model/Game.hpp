#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "utils/Id.hpp"
#include "../include/registries/PropertyRegistry.hpp"
#include "../include/registries/PlayerRegistry.hpp"
#include "player/Player.hpp"
#include "squares/Property.hpp"
#include "squares/Square.hpp"
#include "squares/Railroad.hpp"
#include "squares/Utility.hpp"
#include "squares/Street.hpp"
#include "squares/SpecialSquare.hpp"
class Square;
//ColorGroups should be registered here/store here a registry
namespace monopoly{
class Game { // Singleton class
private:
    static std::unique_ptr<Game> instance;

    // Core components
    std::unique_ptr<PropertyRegistry> property_registry;
    std::unique_ptr<PlayerRegistry> player_registry;
    std::vector<std::shared_ptr<Square>> squares;
    std::unordered_map<ColorGroupID, std::string, ColorGroupID::Hash> color_groups;
    /**
     * Encapsulates all game state information.
     * Helps track the current game situation and validate actions.
     */
    struct GameState {
        bool initialized{false};
        bool started{false};
        bool over{false};
        int current_player_index{0};
        Player* winner{nullptr};

        // Turn-specific state
        bool has_rolled{false};
        bool awaiting_action{false};  // Indicates player needs to make a decision

        void reset() {
            initialized = false;
            started = false;
            over = false;
            current_player_index = 0;
            winner = nullptr;
            resetTurnState();
        }

        void resetTurnState() {
            has_rolled = false;
            awaiting_action = false;
        }
    } state{};

    struct Dice {
        int first;
        int second;
        [[nodiscard]] bool isDoubles() const { return first == second; }
        [[nodiscard]] int getTotal() const { return first + second; }
    };
    // Random number generation
    std::random_device rd_{};
    std::mt19937 gen_{rd_()};
    std::uniform_int_distribution<> dice_dist{1, 6};

    Game();

    // Basic Player and square management
    void addPlayer(const std::string &player);
    // ReSharper disable once CppFunctionIsNotImplemented
    void addSquare(); //TODO
    void addProperty();
    void addRailroad();
    void addStreet();
    void addUtility();
    void addSpecialSquare();


    //Turns management:
    void handleTurn();
    Dice rollDice();
    void handleDiceRoll(int result, bool isDoubles);
    void handleDouble(int result);
    void isGameWon();//TODO
    void handleBankruptcy(Player &bankrupt_player);//TODO

    //Movement management:
    void moveSteps(int steps);
    void movedPastGo();


    //Landing management:
    void landOn(int pos);

    void landOnProperty(Property& property);
    void payRent(Property& property);
    void buyProperty(Property& property);
    void buildOnProperty(Property& property);

    void landOnSpecialSquare(SpecialSquare& special_square);//TODO
    void landOnFreeParking();
    void landOnInJailJustVisit();
    void landOnLuxuryTax();
    void landOnChance(); //TODO void drawChanceCard();
    void landOnGoToJail();//TODO
    void goToJail();//TODO
    void outOfJail();//TODO

    //to be revised
    void processCurrentTurn();  // Main turn processing logic
    void setupColorGroups();    // Initialize color groups
    void createProperties();    // Create and set up properties
    void createSpecialSquares(); // Create special squares
public:
    static Game& getInstance();
    // Delete copy/move operations
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Basic game initialization and states
    bool initializeGame(size_t size_players);
    void addPlayers(size_t num_players);
    bool startGame();
    bool endGame();
    void nextTurn();

    // Getters
    [[nodiscard]] size_t getPlayerCount() const { return player_registry->getSize(); }
    Square* getSquareAt(const int index) {return squares.at(index).get();}
    [[nodiscard]] bool isGameInitialized() const {return state.initialized;}
    [[nodiscard]] bool isGameStarted() const {return state.started;}
    [[nodiscard]] bool isGameOver() const {return state.over;}
    [[nodiscard]] int getCurrentPlayerIndex() const {return state.current_player_index;}
    [[nodiscard]] size_t getBoardSize() const { return squares.size(); }

    //to be revised:
    [[nodiscard]] bool hasRolled() const { return state.has_rolled; }
    [[nodiscard]] bool isAwaitingAction() const { return state.awaiting_action; }
    [[nodiscard]] bool canBuyProperty() const;
    [[nodiscard]] bool mustPayRent() const;
    [[nodiscard]] int calculateCurrentRent() const;
    Player& getCurrentPlayer();
    [[nodiscard]] Property* getCurrentProperty() const;
    [[nodiscard]] Player* getWinner() const { return state.winner; }
};
}
