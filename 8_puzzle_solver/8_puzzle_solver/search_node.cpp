//
//  search_node.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/11/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "search_node.hpp"

Node::Node(int action_taken, Node* parent, PuzzleBoard* inputState){
    
    action_taken_to_this_node = action_taken;
    parent_node = parent;
    state = inputState;
    
    depth=parent->depth+1;
    expanded=false;
    
    path_cost = parent->getPathCost() + parent->state->findCostOfMove(this->state);
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

/*
 My attempt at memory management, as someone with minimal C++ experience
 */
Node::~Node(){
    if (expanded){
        for (int i=0;i<4;i++){
            if (children[i]!=nullptr){
                delete(children[i]->state);
                delete(children[i]);
            }
        }
    }
    
};

bool Node::operator<(const Node &rightSide){
    if (aStarCost==rightSide.aStarCost)             //if aStarCost hasn't been initialized, pathcost is what matters. If it has and they're the same, breaks ties.
        return path_cost<rightSide.path_cost;
    
    return aStarCost<rightSide.aStarCost;
};

/*
 unsure if this is still necessary or not. It was supposed to help the priority_queue do its thing.
 */
bool Node::operator==(const Node &rightSide){
    return aStarCost==rightSide.aStarCost;
};


/*
 Various heuristics for A* search. Could also be used with Best First search, but that wasn't the assignment, so I didn't do that.
 */
void Node::calculateHeuristic1(PuzzleBoard* goal){
    heuristic = state->heuristic1(goal);
    aStarCost = heuristic+path_cost;
};
void Node::calculateHeuristic2(PuzzleBoard* goal){
    heuristic = state->heuristic2(goal);
    aStarCost = heuristic+path_cost;
};
void Node::calculateHeuristic3(PuzzleBoard* goal){
    heuristic = state->heuristic3(goal);
    aStarCost = heuristic+path_cost;
};



/*
 Big important function, used all the time! Takes the map of what's been seen already, and fills the children[] array accordingly
 */
void Node::expand(std::map<int, PuzzleBoard*>* explored){
    expanded=true;
    PuzzleBoard moves[4];
    state->getPossibleMoves(moves);                         //this is the successor function, basically. expand() does the state checking after this.
    
    for (int i=0;i<4;i++){                                  //this whole loop used to be more complicated, but I like this more readable version better
        bool seen = false;
        if (explored->count(moves[i])) seen = true;
        
        if (!seen &&
            moves[i] != *state){
            children[i]=new Node(i, this, new PuzzleBoard(moves[i]));
        }
        else{
            children[i]=nullptr;
        }
        
    }
    
}








