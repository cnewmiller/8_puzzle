//
//  search_agent.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/12/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include "search_agent.hpp"
#include <iostream>

SearchAgent::SearchAgent(PuzzleBoard* initialState, PuzzleBoard* goal){
    rootNode = new Node(initialState);
    currentNode = rootNode;
    goalState = goal;
    
};


SearchAgent::~SearchAgent(){
    delete(rootNode);
}

/*
    Expands the search tree using breadth-first search
 */
void SearchAgent::findGoalUsingBFS(){
    q.push(rootNode);                                                       //queue starts with root node, unexpanded
    nodesPopped=0;
    while (!q.empty()){
        currentNode = q.front();                                            //remove front reference, put it in currentNode
        q.pop();                                                            //remove it from queue
        nodesPopped++;
        if (q.size()>maxQueueSize)maxQueueSize=q.size();
        exploredMap[*(currentNode->getState())] = currentNode->getState();  //add it to the map of nodes that have been explored
        
        if (frontier.count(*(currentNode->getState()))>0){                  //if this node was in the frontier list (it was, almost certainly), remove it
            frontier.erase(*(currentNode->getState()));
        }
        
        if (*goalState == *(currentNode->getState())){                      //if currentNode is the same state as goalState
            std::cout<<"Found it!\n";
            backTrack(currentNode);
            break;
        }
        
        else{
            
            currentNode->expand(&exploredMap);                              //expand currentNode's children
            for (int i=0;i<4;i++){
                if (currentNode->children[i] != nullptr                     //if it was expanded
                    && frontier.count(*(currentNode->children[i]->getState()))==0){ //and it's not already in the queue of states to expand
                    q.push(currentNode->children[i]);
                    frontier[*(currentNode->children[i]->getState())] = currentNode->children[i];
                    
                }
                
            }
            
        }
        
    }
};



/*
 Expands the search tree using breadth-first search. Essentially the same implementation as BFS, but uses a stack instead of a queue
 */
void SearchAgent::findGoalUsingDFS(){
    s.push(rootNode);
    nodesPopped=0;
    while (!s.empty()){
        currentNode = s.top();
        s.pop();
        nodesPopped++;
        if (s.size()>maxQueueSize)maxQueueSize=s.size();
        exploredMap[*(currentNode->getState())] = currentNode->getState();
        if (frontier.count(*(currentNode->getState()))>0){
            frontier.erase(*(currentNode->getState()));
        }
        
        if (*goalState == *(currentNode->getState())){
            backTrack(currentNode);
            printf("Found it!\n");
            break;
        }
        
        else{
            currentNode->expand(&exploredMap);
            for (int i=3;i>=0;i--){                                                 //goes in reverse order, because for some reason this makes DFS faster in these cases.
                if (currentNode->children[i] != nullptr
                    && frontier.count(*(currentNode->children[i]->getState()))==0){
                    s.push(currentNode->children[i]);
                    frontier[*(currentNode->children[i]->getState())] = currentNode->children[i];
                    
                }
            }
        }
    }
};

/*
 Expands using uniform cost. The cost of each move is considered the value of the "tile" being moved.
 */
void SearchAgent::findGoalUsingUniformCost(){
    heap.push(rootNode);                        //"heap" is technically a priority queue, but it functions pretty much the same
    nodesPopped=0;
    while (!heap.empty() ){
        currentNode = heap.top();
        heap.pop();
        nodesPopped++;
        if (heap.size()>maxQueueSize)maxQueueSize=heap.size();
        exploredMap[*(currentNode->getState())] = currentNode->getState();
        if (frontier.count(*(currentNode->getState()))>0){
            frontier.erase(*(currentNode->getState()));
        }
        if (*goalState == *(currentNode->getState())){
            std::cout<<"Found it!\n";
            backTrack(currentNode);
            break;
        }
        else{
            currentNode->expand(&exploredMap);
            
            for (int i=0;i<4;i++){ //check children
                if (currentNode->children[i] != nullptr){
                    uniformAdd(currentNode->children[i]);       //special helper function, explained below
                }
            }
        }
        
    }
};

/*
 This function uses checks to see if the state is already in the queue under some other cost, then if the new cost is lower than the old one, updates the
 old node with the new node's values. This is done so frontier will always have the correcet reference to the nodes that are in the heap/priority queue
 */

void SearchAgent::uniformAdd(Node* target){
    int targetTotal =target->getPathCost();
    
    if (frontier.count(*(target->getState()))>0 &&                          //if it's in the frontier already
        targetTotal < frontier[*(target->getState())]->getPathCost()){      //and if the new cost is lower than the old cost
        Node* toReplace = frontier[*(target->getState())];
        toReplace->setCost(target->getPathCost());
        toReplace->setDepth(target->getDepth());
        toReplace->setParent(target->getParent());
        toReplace->setActionTaken(target->getActionTaken());
        return;
    }
    else if (frontier.count(*(target->getState()))==0){                     //it's not in the frontier
        heap.push(target);                                                  //it hasn't been seen before, so just shove it on the heap
        frontier[*(target->getState())] = target;
    }
}

/*
 This does BestFirst (greedy) expansion. The only loops used are to explore the children in order of heuristic. It only backtracks if every child has been explored already
 */
Node* SearchAgent::recursiveBestFirstFind(Node* parent, int tracker){
    if (parent == nullptr) return nullptr;
    if (*goalState == *(parent->getState())){
        printf("Found it!\n");
        return parent;
    }
    exploredMap[*(parent->getState())] = parent->getState();
    parent->expand(&exploredMap);
    
    
    //this could be implemented as a priority queue, but comparing node pointers is a pain in the ass and worst case is a list of length 4
    std::list<Node*> orderedChildren;
    
    for (int i=0;i<4;i++){
        if (parent->children[i] != nullptr){
            parent->children[i]->calculateHeuristic1(goalState);        //the heuristic used is the number of tiles that are out of place
            std::list<Node*>::iterator index = orderedChildren.begin();
            while (index!=orderedChildren.end()){
                if (parent->children[i]->getHeuristic() <= (*index)->getHeuristic()){
                    orderedChildren.insert(index, parent->children[i]);
                    break;
                }
                else
                    index++;
            }
            if (index == orderedChildren.end()){
                orderedChildren.push_back(parent->children[i]);
            }
        }
    }
    
    
    Node* ret = nullptr;
    while (ret == nullptr && !orderedChildren.empty()){
        ret = recursiveBestFirstFind(orderedChildren.front(), tracker+1);
        orderedChildren.pop_front();
    }
    nodesPopped++;
    if (tracker>maxQueueSize)maxQueueSize=tracker;
    return ret;
};

//public facing function for the recursive Best First search
void SearchAgent::findGoalUsingBestFirst(){
    nodesPopped=0;
    backTrack(recursiveBestFirstFind(this->rootNode, 0));
};


/*
 Uses essentially the same structure as uniform-cost search. (int h) is the number of the heuristic to use:
    1 is number of tiles out of place
    2 is Manhatten distance
    3 is Manhatten distance times tile cost
 Any other call doesn't get a heuristic added on
 */
void SearchAgent::findGoalUsingAStar(int h){
    heap.push(rootNode);
    nodesPopped=0;
    while (!heap.empty() ){
        currentNode = heap.top();
        heap.pop();
        nodesPopped++;
        if (heap.size()>maxQueueSize)maxQueueSize=heap.size();
        exploredMap[*(currentNode->getState())] = currentNode->getState();
        if (frontier.count(*(currentNode->getState()))>0){
            frontier.erase(*(currentNode->getState()));
        }
        if (*goalState == *(currentNode->getState())){
            std::cout<<"Found it!\n";
            backTrack(currentNode);
            break;
        }
        
        else{
            currentNode->expand(&exploredMap);
            
            for (int i=0;i<4;i++){ //check children
                if (currentNode->children[i] != nullptr){                       //these ->calculateHeuristicX() calls are where the heuristic is created
                    if (h==1){
                        currentNode->children[i]->calculateHeuristic1(goalState);
                    }
                    else if (h==2){
                        currentNode->children[i]->calculateHeuristic2(goalState);
                    }
                    else if (h==3){
                        currentNode->children[i]->calculateHeuristic3(goalState);
                    }
                    aStarAdd(currentNode->children[i]);
                }
            }
        }
        
    }
    
};


/*
 Helper function for A* search. Uses the AStarCost variable instead of the regular cost. Must be called after a calculateHeuristic_() function
 */
void SearchAgent::aStarAdd(Node* target){
    
    int targetTotal =target->getAStarCost();
    
    if (frontier.count(*(target->getState()))>0 &&                      //if it's in the frontier already
        targetTotal < frontier[*(target->getState())]->getAStarCost()){ //and the new node is cheaper
        Node* toReplace = frontier[*(target->getState())];
        toReplace->setCost(target->getPathCost());
        toReplace->setDepth(target->getDepth());
        toReplace->setParent(target->getParent());
        toReplace->setActionTaken(target->getActionTaken());
        return;
    }
    else if (frontier.count(*(target->getState()))==0){ //it's not in the frontier
        heap.push(target);
        frontier[*(target->getState())] = target;
    }
    
    
}

/*
 Builds the solution by putting nodes onto a stack, starting from a given node and building upwards until we get to the rootNode
 */
void SearchAgent::backTrack(Node* endPoint){
    Node* pointOnPath = endPoint;
    while (pointOnPath != rootNode){
        solution.push(pointOnPath);
        pointOnPath = pointOnPath->getParent();
    }
}


/*
 prints out the solution which was build in backTrack(). I kind of don't like printing in the searchAgent object, but it was simple and it's not like it's
 getting pushed to production or anything.
 
 (bool verbose) lets you choose whether or not you want to see all the intermediate boards or just the move instructions. Useful for debugging
 and following along with a real 8-puzzle, if I had one.
 */
void SearchAgent::printSolution(bool verbose){
    printf("You began with this board:\n");
    rootNode->getState()->outputBoard();
    
    while (!solution.empty()){
        Node* pointOnPath = solution.top();
        std::string thisMove;
        switch (pointOnPath->getActionTaken()) {
            case Node::moves::UP :
                thisMove = "UP";
                break;
            case Node::moves::DOWN:
                thisMove = "DOWN";
                break;
            case Node::moves::LEFT:
                thisMove = "LEFT";
                break;
            case Node::moves::RIGHT:
                thisMove = "RIGHT";
                break;
            default:
                thisMove="move error";
                break;
        }
        printf("Move %s - the cost of the entire path so far is %d, the cost of this single move is %d, this is move number %d\n",
               thisMove.c_str(), pointOnPath->getPathCost(), (pointOnPath->getPathCost() - pointOnPath->getParent()->getPathCost()), pointOnPath->getDepth());
        if (verbose) pointOnPath->getState()->outputBoard();

        solution.pop();
    }
    
    printf("And you're there!\n");
    printf("\tStats for this solution: nodes popped: %d, maximum queue size: %lu\n",nodesPopped, maxQueueSize);
    
}




