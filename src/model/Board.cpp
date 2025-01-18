//
// Created by imry on 1/12/25.
//

#include "../include/model/Board.hpp"

#include "../include/model/squares/Property.hpp"
#include "../include/model/squares/Street.hpp"

Board* Board::instance = nullptr;

Board::Board() = default;
Board::~Board() {
    squares.clear();
}
void Board::addSquare(std::unique_ptr<Square> square) {
    squares.push_back(std::move(square));
}

void Board::init() {
    addSquare(std::make_unique<monopoly::Street>("Broadway", 1, 500, 35,6, monopoly::PropertyID()));
    addSquare(std::make_unique<monopoly::Street>("Broadway2", 2, 400, 35,6, monopoly::PropertyID()));

}

Board * Board::getInstance() {
    if (instance == nullptr) {
        instance = new Board();
        instance->init();
    }
    return instance;
}
