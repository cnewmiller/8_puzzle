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
#include <map>
#include "puzzle_board.hpp"


class Node{
    
private:
    
    
    
    Node* parent_node;

    PuzzleBoard* state;
    
    int action_taken_to_this_node, depth, path_cost=0, heuristic=0, aStarCost=0;
    bool expanded;                                                              //for the destructor

    
    
public:
    enum moves: int{UP=0, DOWN=1, LEFT=2, RIGHT=3};                             //this makes bookkeeping easier
    Node(PuzzleBoard*);
    Node(int, Node*, PuzzleBoard*);
    
    Node* children[4]; //these are pointers to the child nodes
    
    ~Node();
    void expand(std::map<int, PuzzleBoard*>* explored);
    
    Node* getParent(){return parent_node;};
    PuzzleBoard* getState(){return state;};
    int getActionTaken(){return action_taken_to_this_node;};
    int getDepth(){return depth;};
    int getPathCost(){return path_cost;};
    int getHeuristic(){return heuristic;};
    int getAStarCost(){return aStarCost;};
    bool getExpanded(){return expanded;};
    
    void calculateHeuristic1(PuzzleBoard*);
    void calculateHeuristic2(PuzzleBoard*);
    void calculateHeuristic3(PuzzleBoard*);
    
    void setActionTaken(int newAction){action_taken_to_this_node=newAction;};
    void setDepth(int newDepth){depth=newDepth;};
    void setCost(int newCost){path_cost=newCost;};
    void setParent(Node* newParent){parent_node=newParent;};
    
    bool operator==(const Node& rightSide);
    bool operator<(const Node& rightSide);
    bool operator>(const Node& rightSide){return !(*(this)<rightSide);};
    
};



/*
 This thing is how the priority queue compares nodes to each other, despite only storing node pointers. Otherwise, it would sort them based on memory
 address, and that would be stupid, right? And obvious if it were doing that, only an IDIOT wouldn't realize that a priority queue can't know to
 dereference it's objects before comparing them! Ha. Ha. Ha.
 */
struct helperCompare{
    bool operator()(Node* left, Node* right){ return !((*left)<(*right));};
};




#endif /* search_node_hpp */
