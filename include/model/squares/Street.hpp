#pragma once
#include "Property.hpp"

namespace monopoly {
    /**
     * @brief Represents a street property in Monopoly
     * 
     * A street is a type of property that can have houses built on it.
     * A hotel is represented by 5 houses.
     */
    class Street final : public Property {
        static constexpr int HOTEL = 5;  // Maximum number of houses (5 represents a hotel)
        int house_cost;                  // Cost to build each house
        int houses = 0;                  // Current number of houses (0-5, where 5 is a hotel)
        std::string color;               // Color group this street belongs to

    public:
        /**
         * @brief Constructs a new Street
         * @param name The name of the street
         * @param position The position on the board (0-39)
         * @param price The purchase price
         * @param base_rent The base rent (no houses)
         * @param house_cost The cost to build each house
         * @param group The color group this street belongs to
         * @throws std::invalid_argument if house_cost is negative
         */
        Street(const std::string &name, const int position, const int price, const int base_rent, const int house_cost,
               const std::string &group): Property(name, position, price, base_rent),
                                          house_cost(house_cost), color(group) {
            if (house_cost < 0) throw std::invalid_argument("House cost cannot be negative");
        }

        ~Street() override = default;

        /**
         * @brief Get the cost to build a house
         * @return The house cost
         */
        [[nodiscard]] int getHouseCost() const {
            return house_cost;
        }

        /**
         * @brief Get the number of houses
         * @return Number of houses (0-5, where 5 represents a hotel)
         */
        [[nodiscard]] int getHouses() const {
            return houses;
        }

        /**
         * @brief Add a house to this street
         * @throws std::runtime_error if a hotel already exists (5 houses)
         */
        void addHouse() {
            if (houses >= HOTEL) {
                throw std::runtime_error("Cannot add more houses - hotel already exists");
            }
            houses++;
        }

        /**
         * @brief Check if the street has a hotel
         * @return true if the street has 5 houses (hotel), false otherwise
         */
        [[nodiscard]] bool hasHotel() const {
            return houses == HOTEL;
        }

        /**
         * @brief Get the color group of this street
         * @return The color group name
         */
        [[nodiscard]] const std::string &getColor() const {
            return color;
        }
    };
}