// PlayerRegistry.hpp
#pragma once
#include "IRegistry.hpp"
#include "../../model/Player.hpp"
#include <stdexcept>

namespace monopoly {
    class PlayerRegistry : public IRegistry<Player, int> {
    public:
        explicit PlayerRegistry();
        void registerItem(std::unique_ptr<Player> player) override;
    };
}