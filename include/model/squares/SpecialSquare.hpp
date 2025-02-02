#pragma once
#include "Square.hpp"

namespace monopoly {
    enum class SpecialSquareType {
        GO,             // Collect salary when passing/landing
        COMMUNITY_CHEST,// Draw a Community Chest card
        INCOME_TAX,     // Pay percentage of total worth
        LUXURY_TAX,     // Pay fixed amount
        JAIL,           // Just visiting/In jail location
        GO_TO_JAIL,     // Move player to jail
        FREE_PARKING,   // No action
        CHANCE          // Draw a Chance card
    };

    /**
     * @brief Represents special squares on the Monopoly board that trigger specific actions
     *
     * Special squares include non-property squares like GO, Chance, Community Chest,
     * taxes, and jail-related squares. Each type triggers different game actions when
     * a player lands on or passes over them.
     */
    class SpecialSquare final : public Square {
    private:
        SpecialSquareType type;

    public:
        /**
         * @brief Constructs a special square
         * @param name The display name of the square
         * @param position The position on the board (0-39)
         * @param type The type of special square and its associated action
         */
        SpecialSquare(const std::string &name, const int position,
                      const SpecialSquareType type)
            : Square(name, position)
              , type(type) {
        }

        /**
         * @brief Gets the type of special square
         * @return The SpecialSquareType enum value
         */
        [[nodiscard]] SpecialSquareType getType() const { return type; }

        /**
         * @brief Checks if this square requires drawing a card
         * @return true if square is Chance or Community Chest
         */
        [[nodiscard]] bool isCardSquare() const {
            return type == SpecialSquareType::CHANCE ||
                   type == SpecialSquareType::COMMUNITY_CHEST;
        }

        /**
         * @brief Checks if this square requires paying tax
         * @return true if square is Income Tax or Luxury Tax
         */
        [[nodiscard]] bool isTaxSquare() const {
            return type == SpecialSquareType::INCOME_TAX ||
                   type == SpecialSquareType::LUXURY_TAX;
        }

        // Prevent copying/moving
        SpecialSquare(const SpecialSquare &) = delete;
        SpecialSquare &operator=(const SpecialSquare &) = delete;
        SpecialSquare(SpecialSquare &&) = delete;
        SpecialSquare &operator=(SpecialSquare &&) = delete;
    };
}