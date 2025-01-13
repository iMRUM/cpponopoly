#pragma once
#include <cstdint>
#include <iostream>
//DONE
namespace monopoly {

    // Type-safe ID template
    template<typename Tag>
    class ID {
    private:
        uint32_t value;
    public:
        explicit ID(const uint32_t v = 0) : value(v) {
            std::cout << "ID: " << value << std::endl;
        }
        bool operator==(const ID& other) const { return value == other.getValue(); }
        bool operator!=(const ID& other) const { return value != other.getValue(); }
        [[nodiscard]] uint32_t getValue() const { return value; }
        // Make it hashable for use in containers
        struct Hash {
            size_t operator()(const ID& id) const {
                return std::hash<uint32_t>()(id.getValue());
            }
        };
    };

    // ID type definitions
    struct SquareTag {};
    struct PropertyTag {};
    struct PlayerTag {};
    struct ColorGroupTag {};
    struct BuildingTag {};
    struct ChanceCardTag {};

    using SquareID = ID<SquareTag>;
    using PropertyID = ID<PropertyTag>;
    using PlayerID = ID<PlayerTag>;
    using ColorGroupID = ID<ColorGroupTag>;
    using BuildingID = ID<BuildingTag>;
    using ChanceCardID = ID<ChanceCardTag>;

} // namespace monopoly