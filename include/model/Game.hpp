#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "utils/Id.hpp"
#include "../utils/registries/PropertyRegistry.hpp"
#include "../utils/registries/PlayerRegistry.hpp"
#include "Player.hpp"
#include "squares/Property.hpp"
#include "squares/Square.hpp"
#include "squares/Railroad.hpp"
#include "squares/Utility.hpp"
#include "squares/Street.hpp"
#include "squares/SpecialSquare.hpp"
#include "../../include/utils/Strategy/RailroadRentCalculator.hpp"
#include "../../include/utils/Strategy/StreetRentCalculator.hpp"
#include "../../include/utils/Strategy/UtilityRentCalculator.hpp"
class Square;
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
        bool has_another_turn{false};
        int current_dice_result{0};

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
            has_another_turn = false;
            current_dice_result = 0;
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

    // Basic Player and square management TODO
    void addPlayer(const std::string &player);
    void addSquare();
    void addProperty();
    void addRailroad(const std::string &name, PropertyID propertyId, int position, int price, int baseRent);
    void addStreet(const std::string &name, int position, int price, int baseRent, int house_cost, PropertyID propertyId);
    void addUtility(const std::string &name, int position, PropertyID propertyId);
    void addSpecialSquare();


    //Turns management:
    void handleTurn();
    Dice rollDice();

    void handleDiceRoll();
    void handleDouble();
    void isGameWon();
    void handleBankruptcy(Player &bankrupt_player);

    //Movement management:
    void moveSteps(int steps, Player &player);
    void movedPastGo(Player &player);


    //Landing management:
    void landOn(int pos, Player &player);

    void landOnProperty(Property &property, Player &player);
    void payRent(Property &property, Player &player);
    void buyProperty(Property &property, Player &player);
    void buildOnProperty(Property &property, Player &player);

    void landOnSpecialSquare(SpecialSquare &special_square, Player &player);//TODO
    void landOnFreeParking();
    void landOnInJailJustVisit();
    void landOnLuxuryTax();
    void landOnChance(); //TODO void drawChanceCard();
    void landOnGoToJail();//TODO
    void goToJail(Player &player);//TODO
    void outOfJail(Player &player);//TODO
    void payFine(int amount, Player& player);

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

    bool canBuildOnProperty(Property &property, Player &player);

    bool mustPayRent() const;
    int calculateCurrentRent() const;
    Player& getCurrentPlayer();
    Property* getCurrentProperty() const;
    Player* getWinner() const { return state.winner; }
};
}