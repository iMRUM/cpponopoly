#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../utils/Id.hpp"
#define BOARD_SIZE 40
#define MAX_JAIL_TURNS 3

namespace monopoly {
    class Player {
    private:
        int balance;
        int position;
        int jail_turns;
        int doubles;
        int jail_cards_amount;
        bool in_jail = false;
        bool is_bankrupt = false;
        PlayerID id;
        std::string name;

    public:
        explicit Player(std::string name)
            : balance(1500), position(0), jail_turns(0), doubles(0),jail_cards_amount(0), id(PlayerID()), name(std::move(name)) {
            std::cout << "Player created" << std::endl;
        }

        // Fields management:
        // ~Balance
        void increaseBalance(int amount);

        bool decreaseBalance(int amount);

        [[nodiscard]] bool canAfford(const int amount) const { return balance >= amount; }

        // ~Position
        void moveSteps(int steps);

        // ~Jail
        void toggleJailState();

        bool incrementJailTurns();

        void resetJailTurns() { jail_turns = 0; }

        void increaseDoubles() { doubles++; }

        void resetDoubles() { doubles = 0; }


        // Getters and Setters
        [[nodiscard]] int getBalance() const { return balance; }
        [[nodiscard]] int getPosition() const { return position; }
        [[nodiscard]] int getJailTurns() const { return jail_turns; }
        [[nodiscard]] bool isInJail() const { return in_jail; }
        [[nodiscard]] bool hasThreeConsecutiveDoubles() const { return doubles >= 3; }
        [[no_discard]] bool hasJailCard() const { return jail_cards_amount > 0; }
        void useJailCard() { jail_cards_amount--; }
        void addJailCard() { jail_cards_amount++; }
        [[nodiscard]] const std::string &getName() const { return name; }
        [[nodiscard]] PlayerID getId() const { return id; }
        void setId(PlayerID& id) { this->id = id; }
        void setPosition(const int new_position) {
            position = new_position;
        }

        void setJailState(const bool new_jail_state) { in_jail = new_jail_state; }


        void setBalance(int balance) {
            this->balance = balance;
        }

        [[nodiscard]] bool isBankrupt() const {
            return is_bankrupt;
        }

        void setBankrupt(bool is_bankrupt) {
            this->is_bankrupt = is_bankrupt;
        }
    };
}
