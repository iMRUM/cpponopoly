#pragma once
#include "Property.hpp"

namespace monopoly {
    class Railroad : public Property {
    public:
        Railroad(const std::string &name,const PropertyID propertyId, const int position, const int price = 200, const int baseRent= 50
                 ): Property(name, position, price, baseRent) {
        }
    };
}
