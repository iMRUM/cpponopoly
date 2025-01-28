#include "../../../include/utils/registry/PlayerRegistry.hpp"

namespace monopoly {
    PlayerRegistry::PlayerRegistry() : IRegistry<Player, int>(8) {
    }

    void PlayerRegistry::registerItem(std::unique_ptr<Player> player) {
        if (!player) {
            throw std::invalid_argument("Cannot register null player");
        }

        if (exists(player->getId())) {
            throw std::runtime_error("Player with this ID already exists");
        }

        if (size() >= 8) {
            throw std::runtime_error("Maximum number of players (8) reached");
        }

        objects.push_back(std::move(player));
    }
}