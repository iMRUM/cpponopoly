#pragma once
#include "Property.hpp"

namespace monopoly {
    class Railroad : public Property {
    public:
        Railroad(const std::string &name, const int position, const int price = 200, const int baseRent= 50,
                 const PropertyID propertyId): Property(name, position, price, baseRent, propertyId) {
        }
    };
}
