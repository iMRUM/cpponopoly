#pragma once
#include <vector>

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
        explicit Board(size_t size = 40) : board_size(size) {
            squares.reserve(size);
        }

        void addSquare(std::unique_ptr<Square> square) {
            if (squares.size() >= board_size) {
                throw std::runtime_error("Board is full");
            }
            squares.push_back(std::move(square));
        }

        Square* getSquare(size_t position) {
            if (position >= squares.size()) {
                throw std::out_of_range("Invalid square position");
            }
            return squares[position].get();
        }

        const Square* getSquare(size_t position) const {
            if (position >= squares.size()) {
                throw std::out_of_range("Invalid square position");
            }
            return squares[position].get();
        }

        size_t getSize() const { return board_size; }

        bool isComplete() const { return squares.size() == board_size; }
    };
}
