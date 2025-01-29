#pragma once
#include "Square.hpp"
#include <stdexcept>

namespace monopoly {
    class Property : public Square {
    private:
        int owner_id;
        int price;
        int base_rent;

    public:
        Property(const std::string& name,
                const int position,
                const int price,
                const int base_rent)
            : Square(name, position),
                owner_id(-1),
              price(price),
              base_rent(base_rent) {
            if (price < 0) throw std::invalid_argument("Price cannot be negative");
            if (base_rent < 0) throw std::invalid_argument("Base rent cannot be negative");
        }

        virtual ~Property() = default;

        [[nodiscard]] int getOwnerId() const { return owner_id; }
        void setOwnerId(const int new_owner_id) { owner_id = new_owner_id; }
        [[nodiscard]] bool isOwned() const { return owner_id != int(); }

        [[nodiscard]] int getPrice() const { return price; }
        void setPrice(const int new_price) {
            if (new_price < 0) throw std::invalid_argument("Price cannot be negative");
            price = new_price;
        }

        [[nodiscard]] int getBaseRent() const { return base_rent; }
        void setBaseRent(const int new_base_rent) {
            if (new_base_rent < 0) throw std::invalid_argument("Base rent cannot be negative");
            base_rent = new_base_rent;
        }

        // Prevent copying/moving
        Property(const Property&) = delete;
        Property& operator=(const Property&) = delete;
        Property(Property&&) = delete;
        Property& operator=(Property&&) = delete;
    };
}