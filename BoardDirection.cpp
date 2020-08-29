#include "BoardDirection.hpp"
#include <array>

using namespace std;

BoardDirection::BoardDirection() : mRowChange(0), mColChange(0){
    
}

BoardDirection::BoardDirection(char row, char col): mRowChange(row), mColChange(col){
    
}

array<BoardDirection, 8> BoardDirection::CARDINAL_DIRECTIONS = { BoardDirection(1, 0), BoardDirection(1, -1), BoardDirection(0, -1), BoardDirection(-1, -1), BoardDirection(-1, 0), BoardDirection(-1, 1), BoardDirection(0, 1), BoardDirection(1, 1)};
