#pragma once
#include "Square.hpp"

namespace monopoly {
    enum class SpecialSquareType {
        GO,
        COMMUNITY_CHEST,
        INCOME_TAX,
        LUXURY_TAX,
        JAIL,
        GO_TO_JAIL,
        FREE_PARKING,
        TAX,
        CHANCE
    };

    class SpecialSquare : public Square {
    private:
        SpecialSquareType type;

    public:
        SpecialSquare(const std::string &name, const int position,
                      const SpecialSquareType type)
            : Square(name, position)
              , type(type) {
        }

        [[nodiscard]] SpecialSquareType getType() const { return type; }

        // Prevent copying/moving
        SpecialSquare(const SpecialSquare &) = delete;

        SpecialSquare &operator=(const SpecialSquare &) = delete;

        SpecialSquare(SpecialSquare &&) = delete;

        SpecialSquare &operator=(SpecialSquare &&) = delete;
    };
}
