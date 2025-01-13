#include "registries/PropertyRegistry.hpp"

namespace monopoly {
    void PropertyRegistry::validateProperty(PropertyID propertyId) const {
        if (!exists(propertyId)) {
            throw std::invalid_argument("Property does not exist");
        }
    }

    void PropertyRegistry::validateOwnership(PropertyID propertyId) const {
        validateProperty(propertyId);
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
        validateOwnership(propertyId);
        auto it = propertyOwners.find(propertyId);
        /*
        if (it == propertyOwners.end()) {
            throw std::runtime_error("Property has no owner");
        }*/
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
    void PropertyRegistry::assignToColorGroup(PropertyID propertyId, ColorGroupID groupId) {
        validateProperty(propertyId);

        // Remove from old group if exists
        auto oldGroupIt = propertyToGroup.find(propertyId);
        if (oldGroupIt != propertyToGroup.end()) {
            ColorGroupID oldGroupId = oldGroupIt->second;
            auto& properties = groupProperties[oldGroupId];
            properties.erase(
                std::remove(properties.begin(), properties.end(), propertyId),
                properties.end()
            );
            if (properties.empty()) {
                groupProperties.erase(oldGroupId);
            }
        }

        // Assign to new group
        propertyToGroup[propertyId] = groupId;
        groupProperties[groupId].push_back(propertyId);
    }

    bool PropertyRegistry::isGroupComplete(ColorGroupID groupId, PlayerID playerId) const {
        auto it = groupProperties.find(groupId);
        if (it == groupProperties.end()) {
            return false;  // Group doesn't exist
        }

        const auto& properties = it->second;
        if (properties.empty()) {
            return false;
        }

        // Check if all properties in the group belong to the player
        return std::all_of(properties.begin(), properties.end(),
            [this, playerId](const PropertyID& propId) {
                return hasOwner(propId) && getOwner(propId) == playerId;
            });
    }

    std::vector<PropertyID> PropertyRegistry::getPropertiesInGroup(ColorGroupID groupId) const {
        auto it = groupProperties.find(groupId);
        return it != groupProperties.end() ? it->second : std::vector<PropertyID>{};
    }

    ColorGroupID PropertyRegistry::getPropertyGroup(PropertyID propertyId) const {
        validateProperty(propertyId);

        auto it = propertyToGroup.find(propertyId);
        if (it == propertyToGroup.end()) {
            throw std::runtime_error("Property is not assigned to any color group");
        }
        return it->second;
    }

    bool PropertyRegistry::canBuildHouse(PropertyID propertyId) const {
        validateProperty(propertyId);

        // Get current building count
        auto countIt = houseCount.find(propertyId);
        int currentHouses = countIt != houseCount.end() ? countIt->second : 0;

        // Can't build more than 4 houses
        if (currentHouses >= 4) {
            return false;
        }

        // Must own all properties in color group
        ColorGroupID groupId = getPropertyGroup(propertyId);
        PlayerID owner = getOwner(propertyId);
        if (!isGroupComplete(groupId, owner)) {
            return false;
        }

        // Must maintain even building across color group
        // All properties in group must have equal or one less house
        const auto& groupProperties = getPropertiesInGroup(groupId);
        return std::all_of(groupProperties.begin(), groupProperties.end(),
            [this, currentHouses, propertyId](const PropertyID& otherId) {
                if (otherId == propertyId) return true;
                auto it = houseCount.find(otherId);
                int otherHouses = it != houseCount.end() ? it->second : 0;
                return otherHouses >= (currentHouses - 1) && otherHouses <= currentHouses;
            });
    }

    void PropertyRegistry::addHouse(PropertyID propertyId) {
    }

    bool PropertyRegistry::upgradeToHotel(PropertyID propertyId) {
    }

    int PropertyRegistry::getHouseCount(PropertyID propertyId) const {
    }

    bool PropertyRegistry::hasHotel(PropertyID propertyId) const {
    }
} // namespace monopoly
