#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace monopoly {
    /**
     * @brief Represents a player in the Monopoly game
     *
     * Manages player state including money, position, jail status,
     * and game conditions. Each player maintains their own state
     * throughout the game including balance, position, jail status,
     * and bankruptcy status.
     */
    class Player {
    private:
        // Game constants
        static constexpr int STARTING_BALANCE = 1500;
        static constexpr int STARTING_POSITION = 0;
        static constexpr int MAX_DOUBLES = 3;

        // Money related
        int balance;
        bool is_bankrupt = false;

        // Position related
        int position;

        // Jail related
        int jail_turns;
        int jail_cards_amount;
        bool in_jail = false;

        // Dice related
        int doubles;

        // Identity
        int id;
        std::string name;

    public:
        /**
         * @brief Constructs a new Player
         * @param name Player's display name
         * @param player_id Unique identifier for the player
         */
        explicit Player(const std::string &name, const int player_id)
            : balance(STARTING_BALANCE), position(STARTING_POSITION),
              jail_turns(STARTING_POSITION), jail_cards_amount(STARTING_POSITION),
              doubles(STARTING_POSITION), id(player_id),
              name(std::move(name)) {
        }

        // Balance management
        /**
         * @brief Increases player's balance
         * @param amount Amount to add (must be positive)
         * @throws std::invalid_argument if amount is negative
         */
        void increaseBalance(int amount);

        /**
         * @brief Attempts to decrease player's balance
         * @param amount Amount to subtract
         * @return true if transaction successful, false if insufficient funds
         */
        bool decreaseBalance(int amount);

        /**
         * @brief Checks if player can afford a payment
         * @param amount Amount to check
         * @return true if player has sufficient funds
         */
        [[nodiscard]] bool canAfford(const int amount) const { return balance >= amount; }

        // Position management
        /**
         * @brief Moves player forward on the board
         * @param steps Number of steps to move
         */
        void moveSteps(int steps);

        // Jail management
        /**
         * @brief Toggles player's jail status and resets jail turns if freed
         */
        void toggleJailState();

        /**
         * @brief Increments number of turns spent in jail
         */
        void incrementJailTurns();

        /**
         * @brief Resets jail turn counter to 0
         */
        void resetJailTurns() { jail_turns = STARTING_POSITION; }

        /**
         * @brief Increments number of consecutive doubles rolled
         */
        void increaseDoubles() { doubles++; }

        /**
         * @brief Resets doubles counter to 0
         */
        void resetDoubles() { doubles = STARTING_POSITION; }

        // Getters and Setters
        [[nodiscard]] int getBalance() const { return balance; }
        [[nodiscard]] int getPosition() const { return position; }
        [[nodiscard]] int getJailTurns() const { return jail_turns; }
        [[nodiscard]] bool isInJail() const { return in_jail; }
        [[nodiscard]] bool hasMaxConsecutiveDoubles() const { return doubles >= MAX_DOUBLES; }
        [[nodiscard]] bool hasRolledDouble() const { return doubles > 0; }
        [[nodiscard]] bool hasJailCard() const { return jail_cards_amount > 0; }

        /**
         * @brief Uses a get out of jail free card
         * @throws std::runtime_error if no jail cards available
         */
        void useJailCard() {
            if (!hasJailCard()) {
                throw std::runtime_error("No jail cards available");
            }
            jail_cards_amount--;
        }

        void addJailCard() { jail_cards_amount++; }
        [[nodiscard]] const std::string &getName() const { return name; }
        [[nodiscard]] int getId() const { return id; }
        void setId(const int id) { this->id = id; }
        void setPosition(const int new_position) { position = new_position; }
        void setJailState(const bool new_jail_state) { in_jail = new_jail_state; }
        void setBalance(int balance) { this->balance = balance; }

        /**
         * @brief Checks if player is bankrupt
         * @return true if player is marked bankrupt or has negative balance
         */
        [[nodiscard]] bool isBankrupt() const {
            return is_bankrupt || balance < 0;
        }

        void setBankrupt(bool is_bankrupt) { this->is_bankrupt = is_bankrupt; }
    };
}
