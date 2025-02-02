#pragma once
#include "Property.hpp"
#include "../../utils/strategy/UtilityRentCalculator.hpp"

namespace monopoly {
    /**
     * @brief Represents a utility property (Electric Company or Water Works) in Monopoly
     *
     * Utilities are special properties where rent is calculated based on dice roll:
     * - If one utility is owned: rent = dice roll × 4
     * - If both utilities are owned: rent = dice roll × 10
     *
     * The multiplier (passed as base_rent to Property) determines the rent calculation and is 10 by default.
     *
     * Standard Monopoly rules:
     * - Base price: $150
     * - Cannot be improved with houses/hotels
     * - Part of the utility group (Electric Company and Water Works)
     */
    class Utility final : public Property {
    private:
        static constexpr int DEFAULT_UTILITY_PRICE = 150;      ///< Standard purchase price for utilities
        static constexpr int DEFAULT_MULTIPLIER = 10;  ///< Rent multiplier when both utilities are owned

    public:
        /**
         * @brief Constructs a Utility property
         *
         * @param name The name of the utility ("Electric Company" or "Water Works")
         * @param position The position on the board
         * @param price The purchase price (defaults to 150)
         * @param multiplier The rent multiplier (defaults to 10)
         */
        Utility(const std::string &name,
               const int position,
               const int price = DEFAULT_UTILITY_PRICE,
               const int multiplier = DEFAULT_MULTIPLIER)
            : Property(name, position, price, multiplier, SquareGroups::Utility) {
            setRentCalculator(std::make_unique<UtilityRentCalculator>(base_rent, 0)); // No dice roll initially
        }
        void updateRent(int diceRoll) {
            setRentCalculator(std::make_unique<UtilityRentCalculator>(base_rent, diceRoll));
        }
    };
}