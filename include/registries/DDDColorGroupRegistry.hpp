#pragma once
#include "Registry.hpp"
#include <vector>


namespace monopoly {
    enum class Color {
        Brown,
        LightBlue,
        Pink,
        Orange,
        Red,
        Yellow,
        Green,
        DarkBlue,
        Railroad,
        Utility
    };
    class ColorGroup {
        std::vector<PropertyID> properties;
        Color color;
    public:
        explicit ColorGroup(const Color c) : color(c) {}
        void addProperty(PropertyID id) { properties.push_back(id); }
        [[nodiscard]] const std::vector<PropertyID>& getProperties() const { return properties; }
        [[nodiscard]] const Color& getColor() const { return color; }
    };

    class DDDColorGroupRegistry : public Registry<ColorGroup, ColorGroupID> {
    public:
        bool isComplete(ColorGroupID groupId, PlayerID ownerId) const;
        std::vector<ColorGroupID> getCompleteGroups(PlayerID playerId) const;
    };

} // namespace monopoly