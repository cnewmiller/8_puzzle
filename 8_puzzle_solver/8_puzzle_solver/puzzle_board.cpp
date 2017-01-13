//
//  puzzle_board.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/4/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "puzzle_board.hpp"
#include <iostream>

int findEmptyIndex(int array[]){
    
    for (int i=0;i<9;i++){
        if (array[i]<0) return i;
    }
    return -1;
};

PuzzleBoard::PuzzleBoard(){
    for (int i=0;i<8;i++){
        BOARD[i]=i+1;
    }
    BOARD[8]=-1;
    
};
PuzzleBoard::~PuzzleBoard(){
    
};
PuzzleBoard::PuzzleBoard(const PuzzleBoard& p){
//    setBoard(p.BOARD);
    
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


void PuzzleBoard::setBoard(int config[9]){
    for (int i=0;i<3;i++)
        BOARD[i]=config[i];
        
};

void PuzzleBoard::outputBoard(){
    for (int i=0;i<3;i++){
        std::cout<<"_| ";
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
void PuzzleBoard::getPossibleMoves(PuzzleBoard moves[4]){ //expects an array of size 4
    //if a move is not possible, it returns a board that is the same as the initial state
    moves[UP] = moveUp();
    moves[DOWN] = moveDown();
    moves[LEFT] = moveLeft();
    moves[RIGHT] = moveRight();
    
};


PuzzleBoard PuzzleBoard::moveUp(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex>2){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex-3];
        newBoard.BOARD[emptySlotIndex-3] = -1;
        
    }
    return newBoard;
};

PuzzleBoard PuzzleBoard::moveDown(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex<6){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex+3];
        newBoard.BOARD[emptySlotIndex+3] = -1;
        
    }
    return newBoard;
    //return null?
};

PuzzleBoard PuzzleBoard::moveLeft(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex%3!=0){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex-1];
        newBoard.BOARD[emptySlotIndex-1] = -1;
        
    }
    return newBoard;
    //return null?
};
PuzzleBoard PuzzleBoard::moveRight(){
    int emptySlotIndex=findEmptyIndex(BOARD);
    
    PuzzleBoard newBoard = PuzzleBoard(*this);
    if (emptySlotIndex%3!=2){
        newBoard.BOARD[emptySlotIndex] = newBoard.BOARD[emptySlotIndex+1];
        newBoard.BOARD[emptySlotIndex+1] = -1;
        
    }
    return newBoard;
    //return null?
};

int PuzzleBoard::findCostOfMove(PuzzleBoard *newState){
    
    for (int i=0;i<9;i++){
        if (newState->BOARD[i] != BOARD[i] && newState->BOARD[i]>0){
            return newState->BOARD[i];
        }
    }
    
    return 0;
};




