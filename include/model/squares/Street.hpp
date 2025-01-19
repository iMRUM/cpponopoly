#pragma once
#include "Property.hpp"

namespace monopoly {
    class Street : public Property {
        int house_cost;
        int houses = 0;

    public:
        Street(const std::string &name, const int position, const int price, const int baseRent, const
               int house_cost,
               const PropertyID propertyId): Property(name, position, price, baseRent, propertyId),
                                             house_cost(house_cost) {
        }
        ~Street() override = default;
        [[nodiscard]] int getHouseCost() const {
            return house_cost;
        }

        [[nodiscard]] int getHouses() const {
            return houses;
        }

        void addHouse() {
            houses++;
        }

        [[nodiscard]] bool hasHotel() const {
            return houses > 4;
        }
    };
}
