#pragma once
#include "Square.hpp"
#include "StrategyRentCalculator.hpp"
#include "../include/utils/Id.hpp"  // Add this include

namespace monopoly {
    class PropertyRegistry;
}

class Property : public Square {
protected:
    monopoly::PropertyID id;  // Add this field
    int price;
    int base_rent;
    virtual const RentCalculator &getRentCalculator() const = 0;

public:
    Property(const std::string &name, const int position, const int price, const int baseRent, const monopoly::PropertyID propertyId)
        : Square(name, position), id(propertyId), price(price), base_rent(baseRent) {
        if (price < 0) {
            throw std::invalid_argument("Price cannot be negative");
        }
        if (baseRent < 0) {
            throw std::invalid_argument("Base rent cannot be negative");
        }
    }

    [[nodiscard]] monopoly::PropertyID getId() const { return id; }  // Add getter

    [[nodiscard]] int getPrice() const { return price; }

    void setPrice(const int new_price) { price = new_price; }


    [[nodiscard]] int getBaseRent() const { return base_rent; }

    void setBaseRent(const int new_base_rent) { base_rent = new_base_rent; }


    // Make onLanding pure virtual beacuse it depends on Property type
    void onLanding(const std::shared_ptr<Player> &player) override = 0;

    virtual int getRent(const monopoly::PropertyRegistry& registry, std::optional<int> diceRoll = std::nullopt) const = 0;

    // Prevent copying/moving
    Property(const Property &) = delete;

    Property &operator=(const Property &) = delete;

    Property(Property &&) = delete;

    Property &operator=(Property &&) = delete;
};
