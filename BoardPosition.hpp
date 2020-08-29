#ifndef BoardPosition_hpp
#define BoardPosition_hpp
#include <sstream>
#include <stdio.h>
#include "BoardDirection.hpp"

#endif /* BoardPosition_hpp */
#pragma once

class BoardPosition {
    
private:
    
    char mRow;
    char mCol;
    
public:
    
    BoardPosition();
    
    BoardPosition(char row, char col);
    
    inline const char GetRow() const{
        
        return mRow;
    }
    
    inline const char GetCol() const{
        
        return mCol;
    }
    
    
    operator std::string() const;
            
    friend std::istream& operator>>(std::istream &lhs, BoardPosition& rhs);
    
    bool operator==(BoardPosition rhs);
    
    bool operator<(BoardPosition rhs) const;
    
    // Member methods
    bool InBounds(int boardSize);
    
    bool InBounds(int row, int col);
    
    static std::vector<BoardPosition> GetRectangularPositions(int row, int col);
    
    BoardPosition operator+(BoardDirection dir);
    
};

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs);
