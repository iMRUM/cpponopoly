#include "../../include/model/Board.hpp"
#include <stdexcept>

namespace monopoly {
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
