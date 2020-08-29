#include "BoardPosition.hpp"
#include <sstream>
#include <vector>

using namespace std;

BoardPosition::BoardPosition() : mRow(0), mCol(0){
    
}

BoardPosition::BoardPosition(char row, char col) : mRow(row), mCol(col){
    
}

BoardPosition::operator std::string() const {

    ostringstream os;

    os << "(" << (int) mRow << ", " << (int) mCol << ")";
    
    return os.str();
}

std::istream& operator>>(std::istream &lhs, BoardPosition& rhs){
        
    int row, col;
    
    lhs.ignore();
    lhs >> row;
    lhs.ignore(2);
    lhs >> col;
    lhs.ignore();
    
    rhs = BoardPosition(row, col);
    
    return lhs;
    
}

bool BoardPosition::operator==(BoardPosition rhs) {
    
    return mRow == rhs.mRow && mCol == rhs.mCol ;
}

bool BoardPosition::operator<(BoardPosition rhs) const{
    
    if (mRow < rhs.mRow){
        
        return true;
    }
    else {
        
        if (mCol < rhs.mCol){
            
            return true;
        }
        
        else {
            
            return false;
        }
    }
}

bool BoardPosition::InBounds(int boardSize){
    
    return mRow < boardSize && mRow >= 0 && mCol < boardSize && mCol >= 0;
}

bool BoardPosition::InBounds(int row, int col){
    
    return mRow < row && mRow >= 0 && mCol < col && mCol >= 0;
}

std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int row, int col){
    
    vector<BoardPosition> v1;
    
    for (int i = 0; i < row; i++){
        
        for (int j = 0; j < col; j++){
            
            v1.push_back(BoardPosition(i, j));
        }
    }
    
    return v1;
}

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs){
    
    lhs << string(rhs);
    
    return lhs;
    
}


BoardPosition BoardPosition::operator+(BoardDirection dir){
            
    mRow += dir.GetRow();
    
    mCol += dir.GetCol();
    
    return BoardPosition(mRow, mCol);
    
}
