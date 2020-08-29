#include "OthelloBoard.hpp"
#include <iostream>

using namespace std;

OthelloBoard::OthelloBoard() : mBoard{Player::EMPTY}, mCurrentPlayer(Player::BLACK), mCurrentValue(0) { mBoard[3][3] = Player::WHITE, mBoard[3][4] = Player::BLACK, mBoard[4][3] = Player::BLACK, mBoard[4][4] = Player::WHITE;
    
}

vector<std::unique_ptr<OthelloMove>> OthelloBoard::GetPossibleMoves() const {
    
    vector<unique_ptr<OthelloMove>> mPossible;
        
    for (int i = 0; i < OthelloBoard::BOARD_SIZE; i++) {
        
        for (int j = 0; j < OthelloBoard::BOARD_SIZE; j++) {
                        
            BoardPosition m = BoardPosition(i, j);
            
            for (int k = 0; k < BoardDirection::CARDINAL_DIRECTIONS.size(); k++) {
                                    
                int counter = 0;
                    
                BoardPosition temp = BoardPosition(m);
                
                temp = temp + BoardDirection::CARDINAL_DIRECTIONS[k];
                    
                while ((InBounds(temp)) && (PositionIsEnemy(temp, mCurrentPlayer))) {
                        
                    counter++;
                
                    temp = temp + BoardDirection::CARDINAL_DIRECTIONS[k];
                }
                    
                if (mBoard[temp.GetRow()][temp.GetCol()] == mCurrentPlayer && InBounds(temp) && counter > 0 && mBoard[temp.GetRow()][temp.GetCol()] != Player::EMPTY && mBoard[i][j] == Player::EMPTY) {
                        
                    mPossible.push_back(std::make_unique<OthelloMove>(m));
                    
                    break;
                }
            }
        }
    }
    
    if (mPossible.size() == 0) {
        
        mPossible.push_back(std::make_unique<OthelloMove>(BoardPosition(-1, -1)));
    }
    
    return mPossible;
}

void OthelloBoard::ApplyMove(std::unique_ptr<OthelloMove> m) {
                  
    if (!(m->IsPass())) {
        
        mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] = mCurrentPlayer;
        
        mCurrentValue = mBoard[m->mPosition.GetRow()][m->mPosition.GetCol()] == Player::BLACK ? mCurrentValue + 1 : mCurrentValue - 1;
            
        for (int i = 0; i < BoardDirection::CARDINAL_DIRECTIONS.size(); i++) {
            
            int counter = 0;
                
            BoardPosition temp = m->mPosition;
                
            temp = temp + BoardDirection::CARDINAL_DIRECTIONS[i];
            
            while ((PositionIsEnemy(temp, mCurrentPlayer)) && InBounds(temp)){
                
                counter++;

                temp = temp + BoardDirection::CARDINAL_DIRECTIONS[i];
            }
                                          
            if (mBoard[temp.GetRow()][temp.GetCol()] == mCurrentPlayer && mBoard[temp.GetRow()][temp.GetCol()] != Player::EMPTY && InBounds(temp) && counter != 0){
                
                m->AddFlipSet(OthelloMove::FlipSet(counter, BoardDirection::CARDINAL_DIRECTIONS[i]));
                    
                temp = m->mPosition;
                                        
                while (counter > 0){
                                                
                    temp = temp + BoardDirection::CARDINAL_DIRECTIONS[i];

                    mBoard[temp.GetRow()][temp.GetCol()] = mCurrentPlayer;
                        
                    mCurrentValue = mCurrentPlayer == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
                                                
                    counter--;
                }
            }
        }
    }
    mHistory.push_back(std::move(m));
    
    mCurrentPlayer = mCurrentPlayer == Player::BLACK ? mCurrentPlayer = Player::WHITE : mCurrentPlayer = Player::BLACK;
}

void OthelloBoard::UndoLastMove() {
    
    unique_ptr<OthelloMove> move = std::move(mHistory.back());
    
    BoardPosition temp = move->mPosition;
    
    mCurrentValue = mBoard[temp.GetRow()][temp.GetCol()] == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
    
    mBoard[temp.GetRow()][temp.GetCol()] = Player::EMPTY;
        
    for (auto itr = move->mFlips.begin(); itr != move->mFlips.end(); itr++) {
                
        BoardPosition temp = move->mPosition;
        
        for (int i = 0; i < itr->mFlipCount; i++) {
            
            temp = temp + itr->mDirection;
                        
            mBoard[temp.GetRow()][temp.GetCol()] = mCurrentPlayer;
            
            mCurrentValue =  mBoard[temp.GetRow()][temp.GetCol()] == Player::BLACK ? mCurrentValue + 2 : mCurrentValue - 2;
        }
    }
        
    mHistory.pop_back();
    
    mCurrentPlayer = mCurrentPlayer == Player::BLACK ? Player::WHITE : Player::BLACK;
}

bool OthelloBoard::IsFinished() {
    
    if (mHistory.size() > 1) {
        
        BoardPosition first = mHistory[mHistory.size() - 2]->mPosition;
        
        BoardPosition next = mHistory[mHistory.size() - 1]->mPosition;
        
        if (first == next) {
            
            return true;
        }
    }
     
    for (int i = 0; i < OthelloBoard::BOARD_SIZE; i++) {
        for (int j = 0; j < OthelloBoard::BOARD_SIZE; j++) {
            
            if (mBoard[i][j] == Player::EMPTY) {
                
                return false;
            }
        }
    }
    
    return false;
}

