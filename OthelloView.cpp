#include "OthelloView.hpp"
#include "OthelloBoard.hpp"
#include <memory>
#include <iostream>
#include <string>

using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
    
    for (int i = 0; i < OthelloBoard::BOARD_SIZE + 1; i++){
        
        for (int j = 0; j < OthelloBoard::BOARD_SIZE + 1; j++){
            
            if (i == 0 && j == 0){
                
                cout << "- ";
            }
            
            else if (i == 0){
                
                cout << j - 1 << " ";
            }
            
            else if (j == 0){
                
                cout << i - 1 << " ";
            }
            
            
            else if ((int) mOthelloBoard->mBoard[i - 1][j - 1] == 0){
                
                cout << ". ";
            }
            
            else if ((int) mOthelloBoard->mBoard[i - 1][j - 1] == 1){
                
                cout << "B ";
            }
            
            else if ((int) mOthelloBoard->mBoard[i - 1][j - 1] == -1){
                
                cout << "W ";
            }
        }
            
        cout << endl;
    }
}

ostream& operator<<(ostream &lhs, const OthelloView &rhs) {
    
    rhs.PrintBoard(lhs);
    
    int player = (int) rhs.mOthelloBoard->GetCurrentPlayer();
    
    return lhs << player;
}

std::ostream& operator<<(std::ostream &lhs, const OthelloMove &rhs) {
    
    return lhs << string(rhs);
}

std::unique_ptr<OthelloMove> OthelloView::ParseMove(const std::string &strFormat) {
    
    istringstream parse{strFormat};
    
    char parenOne, parenTwo, comma;
    
    int row, col;
    
    parse >> parenOne >> row >> comma >> col >> parenTwo;
    
    BoardPosition newBoardPos = BoardPosition(row, col);
    
    auto move = make_unique<OthelloMove>(OthelloMove(newBoardPos));
    
    return move;
    
}
