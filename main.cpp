#include "OthelloBoard.hpp"
#include "OthelloView.hpp"
#include "OthelloMove.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {
	// Initialization
	auto board = std::make_shared<OthelloBoard>(); // the state of the game board
	OthelloView v(board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice



	// Start with this DEBUGGING CODE to make sure your basic OthelloMove and 
	// OthelloBoard classes work, then remove it when you are ready to work
	// on the real main.
    
    /**
	cout << "Initial board:" << endl;
	cout << v << endl;
	unique_ptr<OthelloMove> m{ v.ParseMove("(3, 2)") };
	cout << "Applying the move " << *m << endl;
	board->ApplyMove(std::move(m));
	cout << endl << v << endl; // should show a changed board.
    
	m = v.ParseMove("(4, 2)");
	cout << "Applying the move " << *m << endl;
	board->ApplyMove(std::move(m));
	cout << endl << v << endl;

	m = v.ParseMove("(5, 2)");
	cout << "Applying the move " << *m << endl;
	board->ApplyMove(std::move(m));
	cout << endl << v << endl;
     
    */
	// END OF DEBUGGING CODE

	// Main loop
    
    cout << "Initial Board" << endl;
    
    cout << v << endl;

    OthelloMove pass = OthelloMove();

	do {
		// Print the game board using the OthelloView object
        
        if ((int) board->GetCurrentPlayer() == 1) {
            
            cout << "Black's turn" << endl;
        }
        else {
            
            cout << "White's turn" << endl;
        }

	   // Print all possible moves
        vector<unique_ptr<OthelloMove>> mPossible = board->GetPossibleMoves();
        
        cout << "Possible moves: ";
        
        for (auto&itr:mPossible){
                        
            if (*itr == pass) {
                
                cout << "pass ";
            }
            else {
                
                cout << *itr << " ";
            }
        }
        
        cout << endl;
        
	   // Ask to input a command
        cout << "Enter a command: ";
        
        getline(cin, userInput);
                
	   // Command loop:
		  // move (r,c)
		  // undo n
		  // showValue
		  // showHistory
		  // quit
        
        if (userInput.substr(5).compare("pass") == 0 || userInput.substr(5).compare("pass") == 1) {
                                                
            unique_ptr<OthelloMove> m{ v.ParseMove("(-1, -1)")};
            
            cout << "DEBUG OUTPUT: you entered " << userInput.substr(5) << endl;
                                                
            board->ApplyMove(std::move(m));
            
            cout << v << endl;
        }
        
        else if(userInput.substr(0, 4).compare("move") == 0) {
            
            bool validMove = false;
            
            unique_ptr<OthelloMove> m{v.ParseMove(userInput.substr(5))};
            
            cout << "DEBUG OUTPUT: you entered " << *m << endl;
            
            
            for (auto &itr : mPossible) {
                
                if (*itr == *m) {
                    
                    validMove = true;
                }
            }
             
            if (validMove) {
                
                board->ApplyMove(std::move(m));
            }
            else {
                
                cout << "Not a valid move" << endl;
            }
            
            cout << v << endl;
        }
        else if (userInput.substr(0, 4).compare("undo") == 0) {
            
            cout << "DEBUG OUTPUT: you entered " << userInput << endl;
            
            int counter;
            
            istringstream(userInput.substr(5)) >> counter;

            while (counter != 0) {
                
                board->UndoLastMove();
                
                counter--;
            }
            
            cout << v << endl;
        }
        
        else if (userInput.substr(0, 9).compare("showValue") == 0) {
                        
            cout << "DEBUG OUTPUT: you entered " << userInput << endl;
            
            cout << "Board value: " << board->GetValue() << endl;
        }
                
        else if (userInput.substr(0, 11).compare("showHistory") == 0) {
                        
            cout << "DEBUG OUTPUT: you entered " << userInput << endl;
            
            string player;
            
            player = (int) board->GetCurrentPlayer() == 1 ? "White" : "Black";
            
            for (auto itr = board->GetMoveHistory().rbegin(); itr != board->GetMoveHistory().rend(); itr++) {
                 
                if (*(*itr) == pass){
                    
                    cout << player << ": pass" << endl;
                }
                else {
                
                    cout << player << ": " << *(*itr) << endl;
                }
                
                player = player == "White" ? "Black" : "White";

            }
        }
        
        cout << endl;

    } while (!(board->IsFinished())); // you may want to change the condition
    
    if (board->GetValue() > 0) {
        
        cout << "Black wins!" << endl;
    }
    else if (board->GetValue() == 0) {
        
        cout << "It's a tie!" << endl;
    }
    else {
        
        cout << "White wins!" << endl;
    }
    
    cout << "Goodbye!" << endl;
}
