//
// Created by imry on 1/12/25.
//

#include "Property.hpp"

bool Property::purchase(const std::shared_ptr<Player> &buyer) {
    if (buyer) {
        setOwner(buyer);
        return true;
    }
    return false;
}

void Property::transferTo(const std::shared_ptr<Player> &newOwner) {
    owner.reset();
    setOwner(newOwner);
}

