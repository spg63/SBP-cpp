//
//  sbpSearch.hpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpSearch_hpp
#define sbpSearch_hpp

#include "sbpState.hpp"
#include "sbpMove.hpp"
#include "BoardManager.hpp"
#include "NumUtils.hpp"
#include "sbpMove.hpp"
#include "ExeTimer.hpp"
#include "sbpSearchNode.hpp"
#include "sbpHeuristics.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <functional>
using std::vector;
using std::stack;
using std::queue;
using std::unordered_set;
using std::function;
using std::priority_queue;

class sbpSearch{
public:
    void randomWalk(sbpState &state, int num_iterations);
    void BFS(const sbpState &state);
    void DFS(const sbpState &state);
    // A* takes what amounts to a function pointer as it's heuristic function
    void AStar(const sbpState &state, function<size_t(sbpSearchNode)> heuristic_func);
    
private:
    void genericSearch(const sbpState &state, bool is_bfs);
    void printResults(sbpSearchNode solved_node, double exe_time, size_t node_counter);
    stack<sbpSearchNode> _stackOpenList;    // Used for DFS
    queue<sbpSearchNode> _queueOpenList;    // Used for BFS
    // stateHash contains the hash function for sbpState class
    unordered_set<sbpState, stateHash> _closedSet;
    unordered_set<sbpState, stateHash> _generalOpenSet;
    priority_queue<sbpSearchNode, vector<sbpSearchNode>, sbpSearchNodeCompare> _heap;
    
};


#endif /* sbpSearch_hpp */
