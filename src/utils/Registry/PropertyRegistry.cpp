#include "../../../include/utils/registries/PropertyRegistry.hpp"

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
        validateProperty(propertyId);
        if (hasOwner(propertyId)) {
            PlayerID currentOwner = propertyOwners[propertyId];
            // Remove from ownershipMap
            auto& ownerProperties = ownershipMap[currentOwner];
            ownerProperties.erase(
                std::remove(ownerProperties.begin(), ownerProperties.end(), propertyId),
                ownerProperties.end()
            );
            // Remove from propertyOwners
            propertyOwners.erase(propertyId);
        }
    }

    PlayerID PropertyRegistry::getOwner(PropertyID propertyId) const {
        validateOwnership(propertyId);
        return propertyOwners.at(propertyId);
    }

    std::vector<PropertyID> PropertyRegistry::getProperties(PlayerID playerId) const {
        auto it = ownershipMap.find(playerId);
        return it != ownershipMap.end() ? it->second : std::vector<PropertyID>{};
    }

    bool PropertyRegistry::hasOwner(const PropertyID propertyId) const {
        return propertyOwners.contains(propertyId);
    }


    void PropertyRegistry::assignToColorGroup(PropertyID propertyId, ColorGroupID groupId) {
        validateProperty(propertyId);

        // Remove from old group if exists
        if (propertyToGroup.contains(propertyId)) {
            ColorGroupID oldGroup = propertyToGroup[propertyId];
            auto& groupProps = groupProperties[oldGroup];
            groupProps.erase(
                std::remove(groupProps.begin(), groupProps.end(), propertyId),
                groupProps.end()
            );
        }

        // Assign to new group
        propertyToGroup[propertyId] = groupId;
        groupProperties[groupId].push_back(propertyId);
    }

    bool PropertyRegistry::isGroupComplete(ColorGroupID groupId, PlayerID playerId) const {
        auto groupPropertiesIt = groupProperties.find(groupId);
        if (groupPropertiesIt == groupProperties.end()) {
            return false;
        }

        const auto& propertiesInGroup = groupPropertiesIt->second;
        return std::all_of(propertiesInGroup.begin(), propertiesInGroup.end(),
            [this, playerId](const PropertyID& propId) {
                return hasOwner(propId) && getOwner(propId) == playerId;
            });
    }

    std::vector<PropertyID> PropertyRegistry::getPropertiesInGroup(ColorGroupID groupId) const {
        auto it = groupProperties.find(groupId);
        return (it != groupProperties.end()) ? it->second : std::vector<PropertyID>();
    }

    ColorGroupID PropertyRegistry::getPropertyGroup(PropertyID propertyId) const {
        validateProperty(propertyId);
        auto it = propertyToGroup.find(propertyId);
        if (it == propertyToGroup.end()) {
            throw std::runtime_error("Property is not assigned to any color group");
        }
        return it->second;
    }

    bool PropertyRegistry::remove(PropertyID propertyId) {
        if (!exists(propertyId)) return false;

        if (propertyToGroup.contains(propertyId)) {
            ColorGroupID groupId = propertyToGroup[propertyId];
            auto& groupProps = groupProperties[groupId];
            groupProps.erase(
                std::remove(groupProps.begin(), groupProps.end(), propertyId),
                groupProps.end()
            );
            propertyToGroup.erase(propertyId);
        }

        removeOwner(propertyId);
        return Registry<Property, PropertyID>::remove(propertyId);
    }
} // namespace monopoly
