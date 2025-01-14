#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include <memory>

class Square;

class Board {
    Board();
    static Board* instance;
    std::vector<std::unique_ptr<Square>> squares;
    void addSquare(std::unique_ptr<Square> square); // will be used by init
    void init(); // will be used by get instance

public:
    static Board * getInstance();
    Square* getSquare(const int index) {
        return squares.at(index).get();
    }
    size_t getSize(){return squares.size();}
    ~Board();
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};



#endif //BOARD_HPP
