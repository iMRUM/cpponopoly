#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#define BOARD_SIZE 40

class Player;
class Square {
private:
    std::string name;
    int position;
    int id;
public:
    Square(const std::string& name, const int position)
        : name(name), position(position), id(position) {
        if (position < 0 || position >= BOARD_SIZE) {
            throw std::invalid_argument("Invalid board position");
        }
    }
    // Virtual destructor for proper inheritance
    virtual ~Square() = default;


    // Getters
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getPosition() const { return position; }
    [[nodiscard]] int getId() const { return id; }
    // Prevent copying/moving
    Square(const Square&) = delete;
    Square& operator=(const Square&) = delete;
    Square(Square&&) = delete;
    Square& operator=(Square&&) = delete;
};

