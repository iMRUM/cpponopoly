#pragma once
#include "Square.hpp"

enum class SpecialSquareType {
    GO_TO_JAIL,
    FREE_PARKING,
    TAX,
    CHANCE
};

class SpecialSquare : public Square {
private:
    SpecialSquareType type;

public:
    SpecialSquare(const std::string& name, const int position, 
                  SpecialSquareType type)
        : Square(name, position)
        , type(type) {}

    [[nodiscard]] SpecialSquareType getType() const { return type; }

    // Prevent copying/moving
    SpecialSquare(const SpecialSquare&) = delete;
    SpecialSquare& operator=(const SpecialSquare&) = delete;
    SpecialSquare(SpecialSquare&&) = delete;
    SpecialSquare& operator=(SpecialSquare&&) = delete;
};