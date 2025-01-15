#pragma once
//#include "../player/Player.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include "../include/utils/Id.hpp"
#define BOARD_SIZE 40

class Player;
class Square {
private:
    std::string name;
    int position;
public:
    Square(std::string  name, const int position)
        : name(std::move(name)), position(position) {
        if (position < 0 || position >= BOARD_SIZE) {
            throw std::invalid_argument("Invalid board position");
        }
    }
    // Virtual destructor for proper inheritance
    virtual ~Square() = default;


    // Getters
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getPosition() const { return position; }

    // Prevent copying/moving
    Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;
    Square(Square&&) = delete;
    Square& operator=(Square&&) = delete;
};

