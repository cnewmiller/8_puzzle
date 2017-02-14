//
//  puzzle_board.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/4/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "puzzle_board.hpp"
#include <iostream>


/*
 Helper function. Returns the index of the board where the empty space is
 */
int findEmptyIndex(int array[]){
    for (int i=0;i<9;i++){
        if (array[i]<=0) return i;
    }
    return -1;
};

/*
 Default configuration
 */
PuzzleBoard::PuzzleBoard(){
    for (int i=0;i<8;i++){
        BOARD[i]=i+1;
    }
    BOARD[8]=-1;
    
};
PuzzleBoard::~PuzzleBoard(){
    
};
/*
 Copy constructor. Can't remember if I even use this anywhere or not...
 */
PuzzleBoard::PuzzleBoard(const PuzzleBoard& p){
    for (int i=0;i<9;i++)
        BOARD[i]=p.BOARD[i];
    
};
bool PuzzleBoard::operator==(const PuzzleBoard & rightSide){
    for (int i=0;i<9;i++){
        if (BOARD[i]!=rightSide.BOARD[i])
            return false;
    }
    return true;
};

/*
 Turns a puzzleboard into an integer representation of the board. This lets each board be used as an index to a map, allowing the
 explored and frontier data structures to be super fast
 */
PuzzleBoard::operator int(){
    char builder[9];
    for (int i=0;i<9;i++){
        builder[i]=(char)48+BOARD[i];
    }
    return atoi(builder);
}


void PuzzleBoard::setBoard(int config[9]){
    for (int i=0;i<9;i++)
        BOARD[i]=config[i];
};

void PuzzleBoard::outputBoard(){
    for (int i=0;i<3;i++){
        std::cout<<"| ";
        for (int j=0;j<3;j++){
            if (BOARD[i*3+j]>0)
                std::cout<<BOARD[i*3+j]<<"_|";
            else
                std::cout<<" "<<"_|";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
};

/*
 The successor function. If a move is not possible, it just fills in a board that is the same as the initial state.
 */
void PuzzleBoard::getPossibleMoves(PuzzleBoard moves[4]){ //expects an array of size 4
    moves[UP] = moveUp();
    moves[DOWN] = moveDown();
    moves[LEFT] = moveLeft();
    moves[RIGHT] = moveRight();
    
};

/*
 These functions do not modify the Puzzleboard object, rather they return what you would get if you moved it in that direction.
 */
PuzzleBoard PuzzleBoard::moveUp(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex<6){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex+3];
        newBoard.BOARD[emptySlotIndex+3] = 0;
        
    }
    return newBoard;
};
PuzzleBoard PuzzleBoard::moveDown(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex>2){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex-3];
        newBoard.BOARD[emptySlotIndex-3] = 0;
        
    }
    return newBoard;
};
PuzzleBoard PuzzleBoard::moveLeft(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex%3!=2){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex+1];
        newBoard.BOARD[emptySlotIndex+1] = 0;
        
    }
    return newBoard;
};
PuzzleBoard PuzzleBoard::moveRight(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex%3!=0){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex-1];
        newBoard.BOARD[emptySlotIndex-1] = 0;
        
    }
    return newBoard;
};

/*
 Necessary for our specific version of the modified cost 8-puzzle
 */
int PuzzleBoard::findCostOfMove(PuzzleBoard *newState){
    
    for (int i=0;i<9;i++){
        if (newState->BOARD[i] != BOARD[i] && newState->BOARD[i]>0){
            return newState->BOARD[i];
        }
    }
    return 0;
};

/*
 Returns the number of tiles that are out of place
 */
int PuzzleBoard::heuristic1(PuzzleBoard* goal){
    int h1=0;
    for (int i=0;i<9;i++){
        if (BOARD[i] != goal->BOARD[i] )
            h1+=BOARD[i];
    }
    return h1;
};
/*
 Returns the sum of each tile's Manhatten distance to its goal
 */
int PuzzleBoard::heuristic2(PuzzleBoard* goal){
    int h2=0;
    for (int i=0;i<9;i++){
        if (BOARD[i]<=0) continue;
        int targetIndex = 0;
        for (int j=0;j<9;j++){
            if (goal->BOARD[j]==BOARD[i]) targetIndex = j;
        }
        int x = i%3 - targetIndex%3;
        int y = i/3 - targetIndex/3;
        h2 += (abs(x)+abs(y));
    }
    return h2;
};
/*
 Returns the sum of each tile's Manhatten distance to its goal multiplied by its cost, giving you the actual cost of moving that tile so far
 */
int PuzzleBoard::heuristic3(PuzzleBoard* goal){ //A* v2, modified manhatten distance
    int h3=0;
    for (int i=0;i<9;i++){
        if (BOARD[i]<=0) continue;
        int targetIndex = 0; //this is where the tile needs to be
        for (int j=0;j<9;j++){
            if (goal->BOARD[j]==BOARD[i]) targetIndex = j;
        }
        int x = i%3 - targetIndex%3;
        int y = i/3 - targetIndex/3;
        h3 += (abs(x)+abs(y))*BOARD[i];
        
    }
    return h3;
};




