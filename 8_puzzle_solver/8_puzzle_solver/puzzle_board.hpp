//
//  puzzle_board.hpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/4/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef puzzle_board_hpp
#define puzzle_board_hpp

#include <stdio.h>

class PuzzleBoard{
private:
    enum {UP, DOWN, LEFT, RIGHT};
    
    /*
     the board is stored as a 1d array to make it easier to pass configurations in
     */
    int BOARD[9]; //0-2 row one, 3-5 row 2, 6-8 row 3
    
public:
    
    PuzzleBoard(); //initializes default board
    ~PuzzleBoard();
    PuzzleBoard(const PuzzleBoard &);//copies values
    
    void setBoard(int [9]); //requires properly configured set
    void outputBoard();
    void getPossibleMoves(PuzzleBoard[4]); //get the next four possible states
    
    //these move the EMPTY SPACE in the indicated direction
    PuzzleBoard moveLeft();
    PuzzleBoard moveRight();
    PuzzleBoard moveDown();
    PuzzleBoard moveUp();
    
    int findCostOfMove(PuzzleBoard* newState);
    
    //overload == to compare puzzleboards
    bool operator==(const PuzzleBoard& rightSide);
    bool operator!=(const PuzzleBoard& rightSide){return !(*this==rightSide);};
    
};


#endif /* puzzle_board_hpp */
