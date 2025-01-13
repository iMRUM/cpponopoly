#include "registries/PropertyRegistry.hpp"

namespace monopoly {
    void PropertyRegistry::validateProperty(PropertyID propertyId) const {
        if (!exists(propertyId)) {
            throw std::invalid_argument("Property does not exist");
        }
    }

    void PropertyRegistry::validateOwnership(PropertyID propertyId) const {
        if (!hasOwner(propertyId)) {
            throw std::runtime_error("Property has no owner");
        }
    }

    void PropertyRegistry::setOwner(PropertyID propertyId, PlayerID playerId) {
        validateProperty(propertyId);
        removeOwner(propertyId);
        ownershipMap[playerId].push_back(propertyId);
        propertyOwners[propertyId] = playerId;
    }

    void PropertyRegistry::removeOwner(PropertyID propertyId) {
        auto it = propertyOwners.find(propertyId);
        if (it != propertyOwners.end()) {
            PlayerID oldOwner = it->second;
            auto &properties = ownershipMap[oldOwner];
            properties.erase(std::remove(properties.begin(), properties.end(), propertyId),properties.end());
            if (properties.empty()) {
                ownershipMap.erase(oldOwner);
            }
            propertyOwners.erase(propertyId);
        }
    }

    PlayerID PropertyRegistry::getOwner(PropertyID propertyId) const {
        validateProperty(propertyId);
        auto it = propertyOwners.find(propertyId);
        if (it == propertyOwners.end()) {
            throw std::runtime_error("Property has no owner");
        }
        return it->second;
    }

    std::vector<PropertyID> PropertyRegistry::getProperties(PlayerID playerId) const {
        auto it = ownershipMap.find(playerId);
        return it != ownershipMap.end() ? it->second : std::vector<PropertyID>{};
    }

    bool PropertyRegistry::hasOwner(const PropertyID propertyId) const {
        return propertyOwners.contains(propertyId);
    }

    bool PropertyRegistry::remove(PropertyID propertyId) {
        if (Registry<Property, PropertyID>::remove(propertyId)) {
            removeOwner(propertyId);
            return true;
        }
        return false;
    }
} // namespace monopoly
