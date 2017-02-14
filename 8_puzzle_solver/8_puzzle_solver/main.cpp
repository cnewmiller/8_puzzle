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
#include "search_agent.hpp"
#include <ctime>

//using namespace std;


int main(int argc, const char * argv[]) {
    printf("Hi there! I'm an AI who solves the 8-puzzle!\n");
    int goal[] = {1, 2, 3, 8, 0, 4, 7, 6, 5};
    int easy[] = {1, 3, 4, 8,  6, 2, 7, 0,5};
    int med[]  = {2, 8, 1, 0, 4, 3, 7, 6, 5};
    int hard[] = {5, 6, 7, 4, 0, 8, 3, 2, 1};
    PuzzleBoard puzzle = PuzzleBoard();
    PuzzleBoard goalBoard = PuzzleBoard();
    goalBoard.setBoard(goal);
    bool loop=true;
    while (loop){
        printf("--------------\nPlease choose an option from the list below:\n1: Solve the easy puzzle\n2: Solve the medium difficulty puzzle\n3: Solve the hard puzzle\n4:Exit\n");
        int difficultyChoice;
        std::cin>>difficultyChoice;
        switch (difficultyChoice) {
            case 1:
                puzzle.setBoard(easy);
                break;
            case 2:
                puzzle.setBoard(med);
                break;
            case 3:
                puzzle.setBoard(hard);
                break;
            default:
                loop=false;
                break;
        }
        if (!loop) break;
        printf("--------------\nWhat algorithm do you want me to use?\n1: Breadth-First Search\n2: Depth-First Search\n3: Uniform Cost Search\n4: Best-First Search\n5: A* using number of misplaced tiles as the heuristic\n6: A* using regular Manhatten distance\n7: A* using a modified Manhatten distance\n8: exit\n");
        int algorithmChoice;
        std::cin>>algorithmChoice;
        
        SearchAgent s = SearchAgent(&puzzle, &goalBoard);
        printf("Searching...\n");
        std::clock_t timer = clock();
        switch (algorithmChoice) {
            case 1:
                s.findGoalUsingBFS();
                break;
            case 2:
                s.findGoalUsingDFS();
                break;
            case 3:
                s.findGoalUsingUniformCost();
                break;
            case 4:
                s.findGoalUsingBestFirst();
                break;
            case 5:
                s.findGoalUsingAStar(1);
                break;
            case 6:
                s.findGoalUsingAStar(2);
                break;
            case 7:
                s.findGoalUsingAStar(3);
                break;
            default:
                loop=false;
                break;
        }
        if (!loop) break;
        double iterationTime = (clock() - timer)/((double)CLOCKS_PER_SEC);
        char verboseChoice='x';
        printf("--------------\nWould you like to see all the boards between the start and the solution? (y/n): ");
        std::cin>>verboseChoice;
        if (verboseChoice=='y' || verboseChoice=='Y'){
            s.printSolution(true);
            printf("This solution took me %f seconds to find. Pretty fast, huh?\n", iterationTime);
        }
        else if (verboseChoice=='n' || verboseChoice=='N'){
            s.printSolution(false);
            printf("This solution took me %f seconds to find. Pretty fast, huh?\n", iterationTime);
        }
        else
            loop = false;
        
        
    }
    printf("\n--------------\nThanks for playing, goodbye!\n");    
    return 0;
};
