#pragma once
#include "Property.hpp"

namespace monopoly {
    class Utility : public Property { //baseRent is actually a multiplier
    public:
        Utility(const std::string &name, const int position,const PropertyID propertyId, const int price = 150, const int baseRent= 10): Property(name, position, price, baseRent, propertyId) {
        }
    };
}
