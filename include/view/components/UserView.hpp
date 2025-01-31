#pragma once
#include "SFComposite.hpp"
//composes current turn-relevant components (right panel).
class UserView: public SFComposite {
    UserView(const sf::Vector2f& pos, const sf::Vector2f& sz);
};