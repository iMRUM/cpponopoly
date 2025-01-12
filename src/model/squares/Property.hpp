#pragma once
#include "Square.hpp"
#include "StrategyRentCalculator.hpp"

class Property : public Square {
protected:
    int price;
    int owner_id;
    int base_rent;

    // Each derived class must specify which calculator to use
    virtual const RentCalculator &getRentCalculator() const = 0;

public:
    Property(const std::string &name, const int position, const int price, const int baseRent)
        : Square(name, position), price(price),owner_id(INT8_MAX), base_rent(baseRent) {
        if (price < 0) {
            throw std::invalid_argument("Price cannot be negative");
        }
        if (baseRent < 0) {
            throw std::invalid_argument("Base rent cannot be negative");
        }
    }

    [[nodiscard]] int getOwnerId() const {
        return owner_id;
    }

    void setOwnerId(const int new_owner_id) {
        owner_id = new_owner_id;
    }

    [[nodiscard]] int getPrice() const { return price; }

    void setPrice(const int new_price) { price = new_price; }


    [[nodiscard]] int getBaseRent() const { return base_rent; }

    void setBaseRent(const int new_base_rent) { base_rent = new_base_rent; }

    virtual bool purchase(int buyer_id);

    virtual void transferTo(int new_owner_id); // in case of bankruptcy

    // Make onLanding pure virtual beacuse it depends on Property type
    void onLanding(const std::shared_ptr<Player> &player) override = 0;

    // Prevent copying/moving
    Property(const Property &) = delete;

    Property &operator=(const Property &) = delete;

    Property(Property &&) = delete;

    Property &operator=(Property &&) = delete;
};
