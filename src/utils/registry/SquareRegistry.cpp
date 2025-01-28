#include "../../../include/utils/registry/SquareRegistry.hpp"
#include <stdexcept>
//TESTED
namespace monopoly {

SquareRegistry::SquareRegistry() : IRegistry<Square, int>(BOARD_SIZE) {}

void SquareRegistry::registerItem(std::unique_ptr<Square> square) {
    if (square == nullptr) {
        throw std::invalid_argument("Cannot register null square");
    }

    int position = square->getPosition();
    if (position < 0 || position >= BOARD_SIZE) {
        throw std::invalid_argument("Invalid square position");
    }

    for (const auto& existing : objects) {
        if (existing->getPosition() == position) {
            throw std::invalid_argument("Position already occupied");
        }
    }

    objects.push_back(std::move(square));
}

Square& SquareRegistry::getByPosition(int position) const {
    if (position < 0 || position >= BOARD_SIZE) {
        throw std::invalid_argument("Invalid position");
    }

    for (const auto& square : objects) {
        if (square->getPosition() == position) {
            return *square;
        }
    }
    throw std::runtime_error("Square not found at position");
}

Property& SquareRegistry::getPropertyByPosition(int position) const {
    auto& square = getByPosition(position);
    auto* property = dynamic_cast<Property*>(&square);
    if (!property) {
        throw std::runtime_error("Square is not a property");
    }
    return *property;
}

Street& SquareRegistry::getStreetByPosition(int position) const {
    auto& square = getByPosition(position);
    auto* street = dynamic_cast<Street*>(&square);
    if (!street) {
        throw std::runtime_error("Square is not a street");
    }
    return *street;
}

Railroad& SquareRegistry::getRailroadByPosition(int position) const {
    auto& square = getByPosition(position);
    auto* railroad = dynamic_cast<Railroad*>(&square);
    if (!railroad) {
        throw std::runtime_error("Square is not a railroad");
    }
    return *railroad;
}

Utility& SquareRegistry::getUtilityByPosition(int position) const {
    auto& square = getByPosition(position);
    auto* utility = dynamic_cast<Utility*>(&square);
    if (!utility) {
        throw std::runtime_error("Square is not a utility");
    }
    return *utility;
}

SpecialSquare& SquareRegistry::getSpecialSquareByPosition(int position) const {
    auto& square = getByPosition(position);
    auto* specialSquare = dynamic_cast<SpecialSquare*>(&square);
    if (!specialSquare) {
        throw std::runtime_error("Square is not a special square");
    }
    return *specialSquare;
}

bool SquareRegistry::isProperty(int position) const {
    try {
        auto& square = getByPosition(position);
        return dynamic_cast<Property*>(&square) != nullptr;
    } catch (const std::exception&) {
        return false;
    }
}

bool SquareRegistry::isStreet(int position) const {
    try {
        auto& square = getByPosition(position);
        return dynamic_cast<Street*>(&square) != nullptr;
    } catch (const std::exception&) {
        return false;
    }
}

bool SquareRegistry::isRailroad(int position) const {
    try {
        auto& square = getByPosition(position);
        return dynamic_cast<Railroad*>(&square) != nullptr;
    } catch (const std::exception&) {
        return false;
    }
}

bool SquareRegistry::isUtility(int position) const {
    try {
        auto& square = getByPosition(position);
        return dynamic_cast<Utility*>(&square) != nullptr;
    } catch (const std::exception&) {
        return false;
    }
}

bool SquareRegistry::isSpecialSquare(int position) const {
    try {
        auto& square = getByPosition(position);
        return dynamic_cast<SpecialSquare*>(&square) != nullptr;
    } catch (const std::exception&) {
        return false;
    }
}

}