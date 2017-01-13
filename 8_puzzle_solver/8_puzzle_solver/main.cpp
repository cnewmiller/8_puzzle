//
//  main.cpp
//  8_puzzle_solver
//
//  Created by Clayton Newmiller on 1/4/17.
//  Copyright © 2017 Clayton Newmiller. All rights reserved.
//

#include <iostream>
#include "puzzle_board.hpp"
#include "search_node.hpp"

using namespace std;


//persistent solution memory?

int main(int argc, const char * argv[]) {
    PuzzleBoard p = PuzzleBoard();
    
    
    Node n(&p);
    n.expand();
    for (int i=0;i<4;i++){
        if (n.children[i]!=nullptr){
            cout<<i<<" has a child\n";
        }
    }
    n.children[0]->expand();
    for (int i=0;i<4;i++){
        if (n.children[0]->children[i]!=nullptr){
            cout<<"child number 0 sub "<<i<<" has a child\n";
        }
    }
    
    n.children[2]->expand();
    for (int i=0;i<4;i++){
        if (n.children[2]->children[i]!=nullptr){
            cout<<"child number 2 sub "<<i<<" has a child\n";
        }
    }
    
    
    
    return 0;
};
