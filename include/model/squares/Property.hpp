#pragma once
#include "Square.hpp"
#include <stdexcept>

namespace monopoly {
    /**
     * @brief Base class for all purchasable properties in Monopoly
     *
     * Property represents a purchasable square on the Monopoly board.
     * It extends Square and adds ownership, price, and rent attributes.
     * Properties start owned by the bank (BANK_ID) and can be purchased by players.
     */
    class Property : public Square {
    private:
        /** @brief Identifier for bank ownership of properties */
        static constexpr int BANK_ID = -1;

        /** @brief Current owner's ID, BANK_ID if owned by bank */
        int owner_id;

        /** @brief Purchase price of the property */
        int price;

        /** @brief Base rent amount when property is unimproved */
        int base_rent;

        SquareGroups group;

    public:
        /**
         * @brief Constructs a Property with given attributes
         *
         * @param name Property's display name
         * @param position Position on the board (0-39)
         * @param price Purchase price (must be non-negative)
         * @param base_rent Basic rent amount (must be non-negative)
         * @throws std::invalid_argument if price or base_rent is negative
         */
        Property(const std::string& name, int position, int price,
                int base_rent, SquareGroups group)
            : Square(name, position), owner_id(BANK_ID),
              price(price), base_rent(base_rent), group(group) {
            if (price < 0) throw std::invalid_argument("Price cannot be negative");
            if (base_rent < 0) throw std::invalid_argument("Base rent cannot be negative");
        }

        /** @brief Virtual destructor for proper inheritance */
        virtual ~Property() = default;

        /** @brief Gets the current owner's ID */
        [[nodiscard]] int getOwnerId() const { return owner_id; }

        /** @brief Sets the property's owner ID */
        void setOwnerId(const int new_owner_id) { owner_id = new_owner_id; }

        /** @brief Checks if property is owned by a player (not the bank) */
        [[nodiscard]] bool isOwned() const { return owner_id != BANK_ID; }

        /** @brief Gets the property's purchase price */
        [[nodiscard]] int getPrice() const { return price; }

        /**
         * @brief Sets a new purchase price
         * @param new_price New price value (must be non-negative)
         * @throws std::invalid_argument if new_price is negative
         */
        void setPrice(const int new_price) {
            if (new_price < 0) throw std::invalid_argument("Price cannot be negative");
            price = new_price;
        }

        /** @brief Gets the property's base rent amount */
        [[nodiscard]] int getBaseRent() const { return base_rent; }

        /**
         * @brief Sets a new base rent amount
         * @param new_base_rent New rent value (must be non-negative)
         * @throws std::invalid_argument if new_base_rent is negative
         */
        void setBaseRent(const int new_base_rent) {
            if (new_base_rent < 0) throw std::invalid_argument("Base rent cannot be negative");
            base_rent = new_base_rent;
        }

        [[nodiscard]] virtual SquareGroups getGroup() const { return group; }

        // Prevent copying/moving
        Property(const Property&) = delete;
        Property& operator=(const Property&) = delete;
        Property(Property&&) = delete;
        Property& operator=(Property&&) = delete;
    };
}