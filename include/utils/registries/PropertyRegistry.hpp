#pragma once
#include <vector>
#include "Registry.hpp"
#include "../../src/model/squares/Property.hpp"

namespace monopoly {
    class PropertyRegistry : public Registry<Property, PropertyID> {
    private:
        // Ownership tracking
        std::unordered_map<PlayerID, std::vector<PropertyID>, PlayerID::Hash> ownershipMap;
        std::unordered_map<PropertyID, PlayerID, PropertyID::Hash> propertyOwners;

        // Color group tracking
        std::unordered_map<PropertyID, ColorGroupID, PropertyID::Hash> propertyToGroup;
        std::unordered_map<ColorGroupID, std::vector<PropertyID>, ColorGroupID::Hash> groupProperties;

        void validateProperty(PropertyID propertyId) const;

        void validateOwnership(PropertyID propertyId) const;


    public:
        // Ownership methods
        void setOwner(PropertyID propertyId, PlayerID playerId);

        void removeOwner(PropertyID propertyId);

        PlayerID getOwner(PropertyID propertyId) const;

        std::vector<PropertyID> getProperties(PlayerID playerId) const;

        bool hasOwner(PropertyID propertyId) const;

        // Color group methods
        void assignToColorGroup(PropertyID propertyId, ColorGroupID groupId);

        bool isGroupComplete(ColorGroupID groupId, PlayerID playerId) const;

        std::vector<PropertyID> getPropertiesInGroup(ColorGroupID groupId) const;

        ColorGroupID getPropertyGroup(PropertyID propertyId) const;

        // Override base class remove to handle all cleanup
        bool remove(PropertyID propertyId) override;

    };
} // namespace monopoly
