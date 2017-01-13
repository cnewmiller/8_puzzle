//
//  search_node.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/11/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "search_node.hpp"

#include <iostream>

Node::Node(int action_taken, Node* parent, PuzzleBoard* state){
    
    action_taken_to_this_node = action_taken;
    parent_node = parent;
    this->state = state;
    
    depth=parent->depth+1;
    expanded=false;
    
    path_cost = parent->state->findCostOfMove(this->state);
    
};

Node::Node(PuzzleBoard* init_state){
    
    parent_node = nullptr;
    state = init_state;
    depth=0;
    action_taken_to_this_node=-1;
    path_cost=0;
    expanded = false;
    for (int i=0;i<4;i++){
        children[i]=nullptr;
    }
};

Node::~Node(){
    
    if (expanded){
        for (int i=0;i<4;i++){
            if (children[i]!=nullptr){
                delete(children[i]);
            }
        }
    }
    
};


void Node::expand(){
    expanded=true;
    PuzzleBoard moves[4];
    state->getPossibleMoves(moves);
    for (int i=0;i<4;i++){
        if (moves[i]!=*state){
            children[i]=new Node(i, this, new PuzzleBoard(moves[i]));
        }
        else
            children[i]=nullptr;
    }
    
}







