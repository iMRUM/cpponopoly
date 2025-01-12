#pragma once
//#include "../player/Player.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#define BOARD_SIZE 40

class Player;
class Square {
private:
    std::string name;
    int position;
public:
    Square(const std::string& name, const int position)
        : name(name), position(position) {
        if (position < 0 || position >= BOARD_SIZE) {
            throw std::invalid_argument("Invalid board position");
        }
    }
    // Virtual destructor for proper inheritance
    virtual ~Square() = default;

    // Called when a player lands on this square
    virtual void onLanding(const std::shared_ptr<Player>& player) = 0;

    // Getters
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getPosition() const { return position; }

    // Prevent copying/moving
    Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;
    Square(Square&&) = delete;
    Square& operator=(Square&&) = delete;
};

