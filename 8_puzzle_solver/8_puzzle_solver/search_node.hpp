//
//  search_node.hpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/11/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef search_node_hpp
#define search_node_hpp

#include <stdio.h>
#include "puzzle_board.hpp"


class Node{
    
private:
    
    enum {UP, DOWN, LEFT, RIGHT}; //this makes bookkeeping easier
    
    Node* parent_node; //this is a pointer up to the parent node

    PuzzleBoard* state;

    
    
    int action_taken_to_this_node, depth, path_cost;
    bool expanded;

    
    
public:
    //initial constructor
    Node(PuzzleBoard* init_state);
    Node(int action_taken, Node* parent, PuzzleBoard* state);
    
    //should this be private?
    Node* children[4]; //these are pointers to the child nodes
    
    ~Node(); //TODO
    void expand(); //TODO
    
    
};



#endif /* search_node_hpp */
