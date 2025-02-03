#pragma once
#include <vector>
#include <memory>
#include "squares/Property.hpp"
#include "squares/Square.hpp"
#include "squares/Railroad.hpp"
#include "squares/Utility.hpp"
#include "squares/Street.hpp"
#include "squares/SpecialSquare.hpp"

namespace monopoly {
    class Board {
    private:
        size_t board_size;
        std::vector<std::unique_ptr<Square>> squares;

    public:
        explicit Board(const size_t size = 40) : board_size(size) { squares.reserve(size); }
        void initSquares();
        void addSquare(std::unique_ptr<Square> square);
        Square* getSquare(const size_t position);
        const Square* getSquare(const size_t position) const;
        [[nodiscard]] size_t getSize() const { return board_size; }
        [[nodiscard]] bool isComplete() const { return squares.size() == board_size; }
        [[nodiscard]] std::vector<int> getPropertyIdsInGroup(int property_id);
        [[nodiscard]] std::vector<Property*> getPropertiesInGroup(int property_id);
    };
}