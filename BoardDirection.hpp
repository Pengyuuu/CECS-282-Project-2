#ifndef BoardDirection_hpp
#define BoardDirection_hpp

#include <stdio.h>
#include <array>

#endif /* BoardDirection_hpp */
#pragma once
class BoardDirection {
    
private:
    
    char mRowChange;
    char mColChange;
    
public:
    
    static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;
    
    BoardDirection();
    
    BoardDirection(char row, char col);
    
    inline const char GetRow() const { return mRowChange; }
    
    inline const char GetCol() const { return mColChange; }
    
};
