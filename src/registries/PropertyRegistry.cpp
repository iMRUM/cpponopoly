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
            properties.erase(std::remove(properties.begin(), properties.end(), propertyId), properties.end());
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
        if (Registry::remove(propertyId)) {
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
            auto &properties = groupProperties[oldGroupId];
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
            return false; // Group doesn't exist
        }

        const auto &properties = it->second;
        if (properties.empty()) {
            return false;
        }

        // Check if all properties in the group belong to the player
        return std::all_of(properties.begin(), properties.end(),
                           [this, playerId](const PropertyID &propId) {
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

} // namespace monopoly
