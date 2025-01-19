//
// Created by imry on 1/13/25.
//
#pragma once
#include "Registry.hpp"
#include "../../model/Player.hpp"
namespace monopoly {

    class PlayerRegistry : public Registry<Player, PlayerID> {
    public:
        PlayerID registerPlayer(const std::string& name) {
            return registerObject(std::make_shared<Player>(name, PlayerID(nextId)));
        }
    };
}
