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


namespace monopoly {
    struct Dice {
        int first;
        int second;
        [[nodiscard]] bool isDoubles() const { return first == second; }
        [[nodiscard]] int getTotal() const { return first + second; }
    };

    /**
 * @file GameModel.hpp
 * @brief Core game logic implementation for Monopoly board game
 *
 * The GameModel class implements the Singleton pattern and serves as the central
 * coordinator for all game mechanics. It manages the game state, player turns,
 * property ownership, and all game rules enforcement.
 *
 * Key responsibilities:
 * - Game state management
 * - Turn sequencing
 * - Player movement
 * - Property transactions
 * - Rent calculations
 * - Special square effects
 *
 * @note This class is implemented as a Singleton to ensure only one game instance exists
 */
    class GameModel {
    private:
        /** @brief Singleton instance pointer */
        static std::unique_ptr<GameModel> instance;

        /** @brief Game board containing all squares */
        std::unique_ptr<Board> board;

        /** @brief Collection of all players in the game */
        std::vector<std::unique_ptr<Player> > players;

        /** @brief Maps player IDs to their owned property square IDs */
        std::unordered_map<int, std::vector<int> > ownership_map;

        /** @brief Maps square IDs to their owner's player ID */
        std::unordered_map<int, int> owned_by_map;
        /**
            * @brief Internal game state tracking structure
            *
            * Maintains all state information about the current game including:
            * - Game lifecycle (initialized, started, over)
            * - Current turn information
            * - Dice roll status
            * - Player action states
            */
        struct GameState {
            bool initialized{false}; ///< True if game is properly initialized
            bool started{false}; ///< True if game has started
            bool over{false}; ///< True if game has ended
            int winner{-1}; ///< ID of winning player (-1 if no winner)

            // Turn-specific state
            int current_player_id{0}; ///< ID of player whose turn it is
            int current_square_id{0}; ///< Current square position
            int current_dice_result{0}; ///< Sum of current dice roll
            bool has_rolled{false}; ///< True if dice have been rolled this turn
            bool awaiting_action{false}; ///< True if waiting for player decision
            bool has_another_turn{false}; ///< True if player gets another turn


            /** @brief Reset all game state to initial values */
            void reset() {
                initialized = false;
                started = false;
                over = false;
                winner = -1;
                resetTurnState();
            }

            /** @brief Reset only turn-specific state values */
            void resetTurnState() {
                current_player_id = 0;
                current_square_id = 0;
                current_dice_result = 0;
                has_rolled = false;
                awaiting_action = false;
                has_another_turn = false;
            }
        } state{};

        // Random number generation
        std::random_device rd_{};
        std::mt19937 gen_{rd_()};
        std::uniform_int_distribution<> dice_dist{1, 6};

        /**
        * @brief Private constructor for Singleton pattern
        */
        GameModel();

        /**
         * @brief Add a new player to the game
         * @param name Player's display name
         * @param id Unique player identifier
         */
        void addPlayer(const std::string &name, int id);

        /**
         * @brief Add a square to the board
         * @param square Unique pointer to square object
         */
        void addSquare(std::unique_ptr<Square>);

        /**
         * @brief Add a railroad square to the board
         * @param name Railroad name
         * @param position Board position
         * @param price Purchase price
         * @param baseRent Base rent amount
         */
        void addRailroad(const std::string &name, int position, int price, int baseRent);

        /**
         * @brief Add a street square to the board
         * @param name Street name
         * @param position Board position
         * @param price Purchase price
         * @param baseRent Base rent amount
         * @param house_cost Cost per house
         * @param color Property color group
         */
        void addStreet(const std::string &name, int position, int price, int baseRent, int house_cost,
                       SquareGroups color);

        /**
         * @brief Add a utility square to the board
         * @param name Utility name
         * @param position Board position
         */
        void addUtility(const std::string &name, int position);

        /**
         * @brief Add a special square to the board
         * @param name Square name
         * @param position Board position
         * @param type Special square type
         */
        void addSpecialSquare(const std::string &name, int position, SpecialSquareType type);


        /**
     * @brief Process current player's turn
     */
        /*void handleTurn();*/


        /**
         * @brief Handle consequences of current dice roll
         */
        void handleDiceRoll();

        /**
         * @brief Process doubles roll consequences
         */
        void handleDouble();

        /**
         * @brief Check if game has been won
         */
        void isGameWon();

        /**
         * @brief Handle player bankruptcy process
         * @param player_id ID of bankrupt player
         */
        void handleBankruptcy(int player_id);

        //Movement management:


        /**
         * @brief Handle player passing GO square
         */
        void movedPastGo();


        //Landing management:
        /**
      * @brief Process landing on a square
      * @param pos Square position
      * @param player Landing player
      */
        void landOn(int pos, Player &player);

        /**
         * @brief Handle landing on property square
         * @param property Property landed on
         * @param player Landing player
         */
        void landOnProperty(Property &property, Player &player);

        /**
         * @brief Process rent payment
         * @param property Property requiring rent
         * @param player Player paying rent
         */
        void payRent(Property &property, Player &player);

        /**
         * @brief Count railroads owned by player
         * @param property_id Railroad property ID
         * @param player_id Owner player ID
         * @return Number of railroads owned
         */
        int getRailroadCount(int property_id, int player_id);

        /**
         * @brief Process property purchase
         * @param property Property to buy
         * @param player Buying player
         */
        void buyProperty(Property &property, Player &player);

        /**
         * @brief Build houses on street
         * @param street_id Street to build on
         * @param player_id Building player ID
         */
        void buildOnStreet(int street_id, int player_id);

        /**
         * @brief Handle landing on special square
         * @param special_square Square landed on
         * @param player Landing player
         */
        void landOnSpecialSquare(SpecialSquare &special_square, Player &player);

        /**
         * @brief Process Free Parking effects
         */
        void landOnFreeParking();

        /**
         * @brief Handle Just Visiting jail
         */
        void landOnInJailJustVisit();

        /**
         * @brief Process Luxury Tax payment
         */
        void landOnLuxuryTax();

        /**
         * @brief Handle Chance card effects
         */
        void landOnChance();

        /**
         * @brief Process Go To Jail effects
         */
        void landOnGoToJail();

        /**
         * @brief Send player to jail
         * @param player Player to jail
         */
        void goToJail(Player &player);

        /**
         * @brief Release player from jail
         * @param player Player to release
         */
        void outOfJail(Player &player);

        /**
         * @brief Process fine payment
         * @param amount Fine amount
         * @param player Player paying fine
         */
        void payFine(int amount, Player &player);

    public:
        static std::unique_ptr<GameModel> getInstance();

        // Delete copy/move operations
        GameModel(const GameModel &) = delete;

        GameModel &operator=(const GameModel &) = delete;
     /**
            * @brief Move player specified number of steps
            * @param steps Number of steps to move
            * @param player_id Player to move
            */
     void moveSteps(int steps, int player_id);
        /**
     * @brief Initialize a new game
     * @param size_players Number of players
     * @return True if initialization successful
     */
        void initializeGame(size_t size_players);

        /**
    * @brief Add specified number of players to game
    * @param num_players Number of players to add
    */
        void addPlayers(size_t num_players);

        /**
     * @brief Start the game
     * @return True if game started successfully
     */
        void startGame();

        /**
         * @brief End the current game
         * @return True if game ended successfully
         */
        void endGame();

        /**
         * @brief Advance to next player's turn
         */
        void nextTurn();

        /**
        * @brief Roll two dice and return their values
        * @return Dice structure containing both die values
        */
        const Dice &rollDice();

        bool hasAnotherTurn();

        // Getters
        [[nodiscard]] size_t getPlayersCount() const { return players.size(); }
        [[nodiscard]] int getCurrentPlayerIndex() const { return state.current_player_id; }
        [[nodiscard]] Player &getPlayer(int id) const { return *players[id]; }
        Square &getSquareAt(const int index) { return *(board->getSquare(index)); }
        [[nodiscard]] bool isGameInitialized() const { return state.initialized; }
        [[nodiscard]] bool isGameStarted() const { return state.started; }
        [[nodiscard]] bool isGameOver() const { return state.over; }

        [[nodiscard]] size_t getBoardSize() const { return board->getSize(); }

        [[nodiscard]] bool hasRolled() const { return state.has_rolled; }
        void setHasRolled(bool value) { state.has_rolled = value; }
        [[nodiscard]] bool isAwaitingAction() const { return state.awaiting_action; }

        /**
     * @brief Check if a property can be purchased
     * @return True if current square is purchasable property
     */
        [[nodiscard]] bool canBuyProperty() const;

        /**
         * @brief Check if houses can be built on street
         * @param street Street to check
         * @param player Player attempting to build
         * @return True if building allowed
         */
        bool canBuildOnStreet(Street &street, const Player &player);

        /**
         * @brief Check if player has monopoly on property group
         * @param player_id Player to check
         * @param square_id Property to check
         * @return True if player owns all properties in group
         */
        bool hasMonopoly(int player_id, int square_id) const;

        bool mustPayRent(const int square_id) const;

        /**
         * @brief Calculate rent due on current square
         * @return Rent amount
         */
        int calculateCurrentRent() const;

        Player &getCurrentPlayer();

        int getWinner() const { return state.winner; }
    };
}
