#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "../include/utils/Id.hpp"
#define BOARD_SIZE 40
#define MAX_JAIL_TURNS 3

namespace monopoly {
    class Player {
    private:
        int balance;
        int position;
        int jail_turns;
        int doubles;
        bool in_jail = false;
        bool is_bankrupt = false;
        std::vector<PropertyID*> owned_properties;
        std::string name;

    public:
        explicit Player(std::string name)
            : balance(1500), position(0), jail_turns(0), doubles(0), name(std::move(name)) {
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

        // Getters and Setters
        [[nodiscard]] int getBalance() const { return balance; }
        [[nodiscard]] int getPosition() const { return position; }
        [[nodiscard]] int getJailTurns() const { return jail_turns; }
        [[nodiscard]] bool isInJail() const { return in_jail; }
        [[nodiscard]] const std::string &getName() const { return name; }

        void setPosition(const int new_position) {
            position = new_position;
        }

        void setJailState(const bool new_jail_state) { in_jail = new_jail_state; }

        void addPropertyID(PropertyID &property_id) {
            owned_properties.push_back(&property_id);
        }

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
