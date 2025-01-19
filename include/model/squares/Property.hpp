#pragma once
#include "Square.hpp"
#include "../include/utils/Id.hpp"  // Add this include

namespace monopoly {
    class PropertyRegistry;
class Property : public Square {
protected:
    PlayerID owner_id;
    PropertyID property_id;  // Add this field
    int price;
    int base_rent;

public:
    Property(const std::string &name, const int position, const int price, const int baseRent, const PropertyID& propertyId)
        : Square(name, position), property_id(propertyId), price(price), base_rent(baseRent) {
        if (price < 0) {
            throw std::invalid_argument("Price cannot be negative");
        }
        if (baseRent < 0) {
            throw std::invalid_argument("Base rent cannot be negative");
        }
    }

    [[nodiscard]] const PlayerID& getOwnerId() const {
        return owner_id;
    }

    void setOwnerId(const PlayerID &owner_id) {
        this->owner_id = owner_id;
    }

    [[nodiscard]] const PropertyID& getPropertyId() const { return property_id; }  // Add getter

    [[nodiscard]] int getPrice() const { return price; }

    void setPrice(const int new_price) { price = new_price; }


    [[nodiscard]] int getBaseRent() const { return base_rent; }

    void setBaseRent(const int new_base_rent) { base_rent = new_base_rent; }


    // Prevent copying/moving
    Property(const Property &) = delete;

    Property &operator=(const Property &) = delete;

    Property(Property &&) = delete;

    Property &operator=(Property &&) = delete;
};
}