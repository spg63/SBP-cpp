//
//  main.cpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include <iostream>
#include "sbpState.hpp"
#include "sbpMove.hpp"
#include "BoardManager.hpp"
#include "sbpSearch.hpp"
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    std::cout << "Hello\n";
    // Possible files to run against
    string level0_orig{"SBP-level0.txt"};
    string level1_orig{"SBP-level1.txt"};
    string level2_orig{"SBP-level2.txt"};
    string level3_orig{"SBP-level3.txt"};
    string level1{"SBP-bricks-level1.txt"};
    string level2{"SBP-bricks-level2.txt"};
    string level3{"SBP-bricks-level3.txt"};
    string level4{"SBP-bricks-level4.txt"};
    string level5{"SBP-bricks-level5.txt"};
    string level6{"SBP-bricks-level6.txt"};
    string level7{"SBP-bricks-level7.txt"};
    string level380{"SBP-level0-380.txt"};
    
    // Vars for user to pick algo and file
    int level_to_solve{-1};
    int algo_to_run{-1};
    
    // Figure it all out
    cout << "Enter 1 for random walk\n";
    cout << "Enter 2 for BFS\n";
    cout << "Enter 3 for DFS\n";
    cout << "Enter 4 for A* w/ Manhattan heuristic\n";
    cout << "Enter 5 for A* w/ Blocking heuristic (my *better* heuristic)\n";
    cout << "Enter 6 for A* w/ Blocking + Manhattan heuristic\n";
    cout << "Enter 7 for A* w/ Useless \"maxing\" heuristic\n";
    cout << "Choice: ";
    std::cin >> algo_to_run;
    while(algo_to_run < 1 || algo_to_run > 7){
        cout << "Dude...valid input please. Try again: ";
        std::cin >> algo_to_run;
    }
    
    // How many steps
    int num_steps_for_random{-1};
    if(algo_to_run == 1){
        while(num_steps_for_random < 1 || num_steps_for_random > 1000){
            cout << "How many moves for your random walk?: ";
            std::cin >> num_steps_for_random;
        }
    }
    
    cout << "\nEnter 0 for SBP-level0.txt\n";
    cout << "Enter 1 for SBP-level1.txt\n";
    cout << "Enter 2 for SBP-level2.txt\n";
    cout << "Enter 3 for SBP-level3.txt\n";
    cout << "Enter 4 for SBP-bricks-level1.txt\n";
    cout << "Enter 5 for SBP-bricks-level2.txt\n";
    cout << "Enter 6 for SBP-bricks-level3.txt\n";
    cout << "Enter 7 for SBP-bricks-level4.txt\n";
    cout << "Enter 8 for SBP-bricks-level5.txt\n";
    cout << "Enter 9 for SBP-bricks-level6.txt\n";
    cout << "Enter 10 for SBP-bricks-level7.txt\n";
    cout << "Enter 11 for 380\n";
    cout << "Choice: ";
    std::cin >> level_to_solve;
    while(level_to_solve < 0 || level_to_solve > 11){
        cout << "Pick a valid file: ";
        std::cin >> level_to_solve;
    }
    
    // Load the appropriate state
    sbpState state;
    switch(level_to_solve){
        case 0: state.loadGameState(level0_orig);
            break;
        case 1: state.loadGameState(level1_orig);
            break;
        case 2: state.loadGameState(level2_orig);
            break;
        case 3: state.loadGameState(level3_orig);
            break;
        case 4: state.loadGameState(level1);
            break;
        case 5: state.loadGameState(level2);
            break;
        case 6: state.loadGameState(level3);
            break;
        case 7: state.loadGameState(level4);
            break;
        case 8: state.loadGameState(level5);
            break;
        case 9: state.loadGameState(level6);
            break;
        case 10: state.loadGameState(level7);
            break;
        case 11: state.loadGameState(level380);
            break;
        default:
            cout << "Something is terribly broken\n";
            exit(-1);
    }
   
    std::function<size_t(sbpSearchNode)> manhattan = sbpHeuristics::getManhattanDistance;
    std::function<size_t(sbpSearchNode)> manhattan_and_blocking = sbpHeuristics::getManhattanAndBlocking;
    std::function<size_t(sbpSearchNode)> blocking = sbpHeuristics::getBlockingCount;
    std::function<size_t(sbpSearchNode)> maxing = sbpHeuristics::getBestGuess;
    
    // Pick the appropriate algorithm and run it
    sbpSearch search;
    switch(algo_to_run){
        case 1: search.randomWalk(state, num_steps_for_random);
            break;
        case 2: search.BFS(state);
            break;
        case 3: search.DFS(state);
            break;
        case 4: search.AStar(state, manhattan);
            break;
        case 5: search.AStar(state, blocking);
            break;
        case 6: search.AStar(state, manhattan_and_blocking);
            break;
            // Really, this just returns manhattanAndBlocking
        case 7: search.AStar(state, maxing);
            break;
        default:
            cout << "Something is terribly broken\n";
            exit(-1);
    }
    return 0;
}
