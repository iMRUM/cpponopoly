//
// Created by imry on 1/12/25.
//

#include "Board.hpp"

Board::Board() {
    init();
}
Board::~Board() {
    squares.clear();
}
void Board::addSquare(std::unique_ptr<Square> square) {
    squares.push_back(std::move(square));
}

void Board::init() {
    //multiple addSquare for all squares on board, maybe use a squaresRegistry to provide dynamic add

}

Board * Board::getInstance() {
    if (instance == nullptr) {
        instance = new Board();
    }
    return instance;
}
