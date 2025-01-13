#pragma once
#include <vector>

#include "Registry.hpp"
#include "../../src/model/squares/Property.hpp"

namespace monopoly {
    class PropertyRegistry : public Registry<Property, PropertyID> {
    private:
        std::unordered_map<PlayerID, std::vector<PropertyID>, PlayerID::Hash> ownershipMap;
        std::unordered_map<PropertyID, PlayerID, PropertyID::Hash> propertyOwners;

        void validateProperty(PropertyID propertyId) const;

        void validateOwnership(PropertyID propertyId) const;

    public:
        void setOwner(PropertyID propertyId, PlayerID playerId);

        void removeOwner(PropertyID propertyId);

        PlayerID getOwner(PropertyID propertyId) const;

        std::vector<PropertyID> getProperties(PlayerID playerId) const;

        bool hasOwner(PropertyID propertyId) const;

        // Override base class remove to handle ownership cleanup
        bool remove(PropertyID propertyId) override;
    };
} // namespace monopoly
