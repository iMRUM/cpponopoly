#pragma once
#include "Property.hpp"

namespace monopoly {
    /**
     * @brief Represents a railroad property in Monopoly
     *
     * Railroad squares are special properties where rent increases based on how many
     * railroads the owner possesses. The base rent is multiplied by 2^(n-1), where n
     * is the number of railroads owned. For example:
     * - 1 railroad: base rent (50)
     * - 2 railroads: 2 × base rent (100)
     * - 3 railroads: 4 × base rent (200)
     * - 4 railroads: 8 × base rent (400)
     */
    class Railroad final : public Property {
    public:
        /** @brief Default purchase price for railroad properties */
        static constexpr int DEFAULT_RAILROAD_PRICE = 200;

        /** @brief Default base rent for railroad properties when owner has exactly one railroad */
        static constexpr int DEFAULT_RAILROAD_BASE_RENT = 50;

        /**
         * @brief Constructs a new Railroad property
         *
         * @param name The display name of the railroad (e.g., "Reading Railroad")
         * @param position The square's position on the board (0-39)
         * @param price The purchase price of the railroad (defaults to 200)
         * @param base_rent The base rent when owner has one railroad (defaults to 50)
         *
         * @note Railroad rent scales with the number of railroads owned by the same player
         */
        Railroad(const std::string &name,
                const int position,
                const int price = DEFAULT_RAILROAD_PRICE,
                const int base_rent = DEFAULT_RAILROAD_BASE_RENT)
            : Property(name, position, price, base_rent, SquareGroups::Railroad) {}
    };
}