//
// Created by imry on 1/12/25.
//

#ifndef BOARD_HPP
#define BOARD_HPP
#include "squares/Square.hpp"
#include <vector>


class Board {
    Board();
    static Board* instance;
    std::vector<std::unique_ptr<Square>> squares;
    void addSquare(std::unique_ptr<Square> square); // will be used by init
    void init(); // will be used by get instance

public:
    static Board * getInstance();
};



#endif //BOARD_HPP
