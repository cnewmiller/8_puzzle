//
//  search_agent.hpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/12/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#ifndef search_agent_hpp
#define search_agent_hpp

#include <stdio.h>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include "puzzle_board.hpp"
#include "search_node.hpp"

class SearchAgent{
    
    
private:
    PuzzleBoard* goalState;
    
    Node* currentNode;
    Node* rootNode;
    
    int calculateHeuristic(PuzzleBoard* state);                                 //this can't be built in because the goal isn't hardcoded in.
    
    std::stack<Node*> s;
    std::queue<Node*> q;
    std::priority_queue<Node*, std::vector<Node*>, helperCompare> heap;         //helperCompare is declared in search_node.hpp
    
    std::stack<Node*> solution;
    
    std::map<int, PuzzleBoard*> exploredMap;                                    //keeps track of what I've evaluated to be the goal
    std::map<int, Node*> frontier;                                              //keeps track of what I'm about to evaluate
    int nodesPopped;
    unsigned long maxQueueSize=0;
    
    void uniformAdd(Node*);
    void aStarAdd(Node*);
    Node* recursiveBestFirstFind(Node*, int);
    void backTrack(Node*);
    
public:
    SearchAgent(PuzzleBoard* initialState, PuzzleBoard* goalState);
    ~SearchAgent();
    
    void findGoalUsingBFS();
    void findGoalUsingDFS();
    void findGoalUsingUniformCost();
    void findGoalUsingBestFirst();
    void findGoalUsingAStar(int);
    

    
    void printSolution(bool);
    
    
};


#endif /* search_agent_hpp */
