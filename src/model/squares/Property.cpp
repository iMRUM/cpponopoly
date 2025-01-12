//
// Created by imry on 1/12/25.
//

#include "Property.hpp"

bool Property::purchase(const int buyer_id) {
    if (buyer_id!=INT8_MAX) {
        setOwnerId(buyer_id);
        return true;
    }
    return false;
}

void Property::transferTo(const int new_owner_id) {
    setOwnerId(new_owner_id);
}

