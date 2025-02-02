#include "../../include/model/Board.hpp"
#include <stdexcept>

namespace monopoly {
    void Board::initSquares() {
    // Bottom row (GO to Jail)
    addSquare(std::make_unique<SpecialSquare>("GO", 0, SpecialSquareType::GO));
    addSquare(std::make_unique<Street>("Mediterranean Avenue", 1, 60, 2, 50, SquareGroups::Brown));
    addSquare(std::make_unique<SpecialSquare>("Community Chest", 2, SpecialSquareType::COMMUNITY_CHEST));
    addSquare(std::make_unique<Street>("Baltic Avenue", 3, 60, 4, 50, SquareGroups::Brown));
    addSquare(std::make_unique<SpecialSquare>("Income Tax", 4, SpecialSquareType::INCOME_TAX));
    addSquare(std::make_unique<Railroad>("Reading Railroad", 5));
    addSquare(std::make_unique<Street>("Oriental Avenue", 6, 100, 6, 50, SquareGroups::LightBlue));
    addSquare(std::make_unique<SpecialSquare>("Chance", 7, SpecialSquareType::CHANCE));
    addSquare(std::make_unique<Street>("Vermont Avenue", 8, 100, 6, 50, SquareGroups::LightBlue));
    addSquare(std::make_unique<Street>("Connecticut Avenue", 9, 120, 8, 50, SquareGroups::LightBlue));
    addSquare(std::make_unique<SpecialSquare>("Jail", 10, SpecialSquareType::JAIL));

    // Left side (St. Charles Place to Free Parking)
    addSquare(std::make_unique<Street>("St. Charles Place", 11, 140, 10, 100, SquareGroups::Pink));
    addSquare(std::make_unique<Utility>("Electric Company", 12));
    addSquare(std::make_unique<Street>("States Avenue", 13, 140, 10, 100, SquareGroups::Pink));
    addSquare(std::make_unique<Street>("Virginia Avenue", 14, 160, 12, 100, SquareGroups::Pink));
    addSquare(std::make_unique<Railroad>("Pennsylvania Railroad", 15));
    addSquare(std::make_unique<Street>("St. James Place", 16, 180, 14, 100, SquareGroups::Orange));
    addSquare(std::make_unique<SpecialSquare>("Community Chest", 17, SpecialSquareType::COMMUNITY_CHEST));
    addSquare(std::make_unique<Street>("Tennessee Avenue", 18, 180, 14, 100, SquareGroups::Orange));
    addSquare(std::make_unique<Street>("New York Avenue", 19, 200, 16, 100, SquareGroups::Orange));
    addSquare(std::make_unique<SpecialSquare>("Free Parking", 20, SpecialSquareType::FREE_PARKING));

    // Top row (Kentucky Avenue to Go To Jail)
    addSquare(std::make_unique<Street>("Kentucky Avenue", 21, 220, 18, 150, SquareGroups::Red));
    addSquare(std::make_unique<SpecialSquare>("Chance", 22, SpecialSquareType::CHANCE));
    addSquare(std::make_unique<Street>("Indiana Avenue", 23, 220, 18, 150, SquareGroups::Red));
    addSquare(std::make_unique<Street>("Illinois Avenue", 24, 240, 20, 150, SquareGroups::Red));
    addSquare(std::make_unique<Railroad>("B. & O. Railroad", 25));
    addSquare(std::make_unique<Street>("Atlantic Avenue", 26, 260, 22, 150, SquareGroups::Yellow));
    addSquare(std::make_unique<Street>("Ventnor Avenue", 27, 260, 22, 150, SquareGroups::Yellow));
    addSquare(std::make_unique<Utility>("Water Works", 28));
    addSquare(std::make_unique<Street>("Marvin Gardens", 29, 280, 24, 150, SquareGroups::Yellow));
    addSquare(std::make_unique<SpecialSquare>("Go To Jail", 30, SpecialSquareType::GO_TO_JAIL));

    // Right side (Pacific Avenue to Luxury Tax)
    addSquare(std::make_unique<Street>("Pacific Avenue", 31, 300, 26, 200, SquareGroups::Green));
    addSquare(std::make_unique<Street>("North Carolina Avenue", 32, 300, 26, 200, SquareGroups::Green));
    addSquare(std::make_unique<SpecialSquare>("Community Chest", 33, SpecialSquareType::COMMUNITY_CHEST));
    addSquare(std::make_unique<Street>("Pennsylvania Avenue", 34, 320, 28, 200, SquareGroups::Green));
    addSquare(std::make_unique<Railroad>("Short Line", 35));
    addSquare(std::make_unique<SpecialSquare>("Chance", 36, SpecialSquareType::CHANCE));
    addSquare(std::make_unique<Street>("Park Place", 37, 350, 35, 200, SquareGroups::Blue));
    addSquare(std::make_unique<SpecialSquare>("Luxury Tax", 38, SpecialSquareType::LUXURY_TAX));
    addSquare(std::make_unique<Street>("Boardwalk", 39, 400, 50, 200, SquareGroups::Blue));
}
    void Board::addSquare(std::unique_ptr<Square> square) {
        if (squares.size() >= board_size) {
            throw std::runtime_error("Board is full");
        }
        squares.push_back(std::move(square));
    }

    Square* Board::getSquare(const size_t position) {
        if (position >= squares.size()) {
            throw std::out_of_range("Invalid square position");
        }
        return squares[position].get();
    }

    const Square* Board::getSquare(const size_t position) const {
        if (position >= squares.size()) {
            throw std::out_of_range("Invalid square position");
        }
        return squares[position].get();
    }

    std::vector<int> Board::getPropertyIdsInGroup(const int property_id) {
        std::vector<int> group_properties;
        auto property_ptr = dynamic_cast<Property*>(squares[property_id].get());
        if (!property_ptr) {
            throw std::invalid_argument("Not a property square");
        }

        SquareGroups target_group = property_ptr->getGroup();

        for (size_t i = 0; i < squares.size(); ++i) {
            if (auto other_property = dynamic_cast<Property*>(squares[i].get())) {
                if (other_property->getGroup() == target_group) {
                    group_properties.push_back(static_cast<int>(i));
                }
            }
        }
        return group_properties;
    }

    std::vector<Property*> Board::getPropertiesInGroup(int property_id) {
        std::vector<Property*> group_properties;
        if (property_id >= squares.size()) {
            throw std::out_of_range("Invalid property ID");
        }

        auto* source_property = dynamic_cast<Property*>(squares[property_id].get());
        if (!source_property) {
            throw std::invalid_argument("ID does not correspond to a property");
        }

        SquareGroups target_group = source_property->getGroup();

        for (auto& square : squares) {
            if (auto* property = dynamic_cast<Property*>(square.get())) {
                if (property->getGroup() == target_group) {
                    group_properties.push_back(property);
                }
            }
        }
        return group_properties;
    }
}
