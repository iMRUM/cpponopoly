#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <stdexcept>
#define BOARD_SIZE 40
#define MAX_JAIL_TURNS 3

class Property; // forward declaration

class Player {
private:
    int id;
    int balance;
    int position;
    int jail_turns;
    bool in_jail = false;
    std::string name;
    std::vector<std::shared_ptr<Property>> properties;

public:
    explicit Player(const int id, std::string name)
        : id(id), balance(1500), position(0),jail_turns(0), name(std::move(name)) {
        std::cout<<"Player created"<< std::endl;
    }

    // Fields management:
    // ~Balance
    void increaseBalance(int amount);
    bool decreaseBalance(int amount);
    [[nodiscard]] bool canAfford(const int amount) const{return balance >= amount;}
    // ~Position
    void moveSteps(int steps);
    // ~Jail
    void toggleJailState();

    bool incrementJailTurns();
    void resetJailTurns(){jail_turns = 0;}
    // ~Properties
    void addProperty(const std::shared_ptr<Property>& property);
    void removeProperty(const std::shared_ptr<Property>& property);
    [[nodiscard]] bool ownsProperty(const std::shared_ptr<Property>& property) const;

    // Getters and Setters
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] int getBalance() const { return balance; }
    [[nodiscard]] int getPosition() const { return position; }
    [[nodiscard]] int getJailTurns() const { return jail_turns; }
    [[nodiscard]] bool isInJail() const { return in_jail; }
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] const std::vector<std::shared_ptr<Property>>& getProperties() const { return properties; }
    void setPosition(const int new_position) {
        position = new_position;
    }
    void setJailState(const bool new_jail_state) {in_jail = new_jail_state;}
};
