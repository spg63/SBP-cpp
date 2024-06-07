//
//  sbpSearch.cpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpSearch.hpp"

//----- Search Class, holding the search algorithms

void sbpSearch::randomWalk(sbpState &state, int num_iterations){
    BoardManager manager;
    // Output the initial state
    state.outputGameState();
    cout << '\n';
    
    for(auto i = 0; i < num_iterations; ++i){
        // Get all the possible moves in the current state
        auto all_possible_moves = manager.allMoves(state);
        
        // Select one at random
        int move_selection = NumUtils::getRandomInt(0, (int)(all_possible_moves.size() - 1));
        
        sbpMove move = all_possible_moves[move_selection];
        
        // Execute the move
        manager.applyMove(state, move);
        
        // Normalize the resulting state
        state.normalizeState();
        
        // Output the move
        cout << move.getPieceAndDirection() << "\n\n";
        
        // Output the resulting gamestate
        state.outputGameState();
        cout << '\n';
        
        if(state.gameStateSolved())
            break;
    }
}



void sbpSearch::genericSearch(const sbpState &state, bool is_bfs){
    cout << "Yeah....clearly the better option; ran out of time to avoid the\n";
    cout << "copy & past between DFS and BFS....next time!\n";
    cout << "**** So I know I said next time...but it's not going to happen!\n";
}

void sbpSearch::DFS(const sbpState &state){
    sbpState ss;
    ExeTimer timer;
    // Keep track of total visited nodes
    size_t node_counter = 0;
    timer.start_timer();
    vector<sbpMove> sbpm;
    sbpSearchNode solved_node(nullptr, ss, sbpm, -1);
    volatile bool solved = false;
    // Get a clone of the state and normalize it
    sbpState pa = state.clone();
    pa.normalizeState();
    
    // Create the parent node
    sbpSearchNode parent(pa);
    // Check if the state is already complete, if so cool, we're done
    if(parent.getState().gameStateSolved()){
        std::cout << "Game state was already solved; no moves necessary.\n";
        return;
    }
    
    // Set of states, using the stateHash class to provide the hash value
    // NOTE: there is no need to check if the state is already in the open
    
    // On a more realistic note, add it to the queue and start the expansion
    // Note this gets pushed on here (just to be popped immediately off) to
    // simplify the loop below
    _stackOpenList.push(parent);
    _generalOpenSet.insert(parent.getState());
    
    while((!_stackOpenList.empty()) && (solved == false)){
        
        // Get the information needed from the node in the openlist
        sbpSearchNode *tmpND = _stackOpenList.top().getParent();
        sbpState tmpST = _stackOpenList.top().getState();
        vector<sbpMove> tmpML = _stackOpenList.top().getMoveList();
        size_t tmpPC = _stackOpenList.top().getPathCost();
        sbpSearchNode popped_node(tmpND, tmpST, tmpML, tmpPC);
        
        // Pop the node off the openlist and remove it from the hashset
        _stackOpenList.pop();
        _generalOpenSet.erase(popped_node.getState());
        ++node_counter;
        
        // Get a list of all the possible moves in the given state
        BoardManager manager;
        auto possible_moves = manager.allMoves(popped_node.getState());
        
        // Add current node's state to closed list as it's about to be operated on
        _closedSet.insert(popped_node.getState());
        
        // Do each of the possible moves, create a new node for the new state
        for(auto &&move : possible_moves){
            // Create the child-node with information post-movement
            auto new_state = manager.applyMoveCloning(popped_node.getState(), move);
            
            // Normalize the resulting state
            new_state.normalizeState();
            
            // Add the move to the node's parents move list
            vector<sbpMove> ml = popped_node.getMoveList();
            ml.push_back(move);
            
            // Increment the path cost
            size_t new_pc = popped_node.getPathCost() + 1;
            
            sbpSearchNode child(&popped_node, new_state, ml, new_pc);
            
            // Check if the state is now solved
            if(new_state.gameStateSolved()){
                solved = true;
                solved_node.setParent(child.getParent());
                solved_node.setState(child.getState());
                solved_node.setMoveList(child.getMoveList());
                solved_node.setPathCost(child.getPathCost());
                break;
            }
            
            // Else, add it to the open list if it's not already in the closed list
            bool in_closed_list = false;
            if(_closedSet.find(child.getState()) != _closedSet.end())
                in_closed_list = true;
            
            bool in_opened_list = false;
            if(_generalOpenSet.find(child.getState()) != _generalOpenSet.end())
                in_opened_list = true;
            
            if((!in_closed_list) && (!in_opened_list)){
                _stackOpenList.push(child);
                _generalOpenSet.insert(child.getState());
            }
        }
        
        if(solved){
            timer.stop_timer();
            printResults(solved_node, timer.get_exc_time_in_ms(), node_counter);
        }
    }
}

void sbpSearch::BFS(const sbpState &state){

    sbpState ss;
    ExeTimer timer;
    // Keep track of total visited nodes
    size_t node_counter = 0;
    timer.start_timer();
    vector<sbpMove> sbpm;
    sbpSearchNode solved_node(nullptr, ss, sbpm, -1);
    volatile bool solved = false;
    // Get a clone of the state and normalize it
    sbpState pa = state.clone();
    pa.normalizeState();
    
    // Create the parent node
    sbpSearchNode parent(pa);
    // Check if the state is already complete, if so cool, we're done
    if(parent.getState().gameStateSolved()){
        std::cout << "Game state was already solved; no moves necessary.\n";
        return;
    }
    
    // Set of states, using the stateHash class to provide the hash value
    // NOTE: there is no need to check if the state is already in the open
    
    // On a more realistic note, add it to the queue and start the expansion
    // Note this gets pushed on here (just to be popped immediately off) to
    // simplify the loop below
    _queueOpenList.push(parent);
    _generalOpenSet.insert(parent.getState());
    
    while((!_queueOpenList.empty()) && (solved == false)){
        
        // Get the information needed from the node in the openlist
        sbpSearchNode *tmpND = _queueOpenList.front().getParent();
        sbpState tmpST = _queueOpenList.front().getState();
        vector<sbpMove> tmpML = _queueOpenList.front().getMoveList();
        size_t tmpPC = _queueOpenList.front().getPathCost();
        sbpSearchNode popped_node(tmpND, tmpST, tmpML, tmpPC);
        
        // Pop the node off the openlist and remove it from the hashset
        _queueOpenList.pop();
        _generalOpenSet.erase(popped_node.getState());
        ++node_counter;
        
        // Get a list of all the possible moves in the given state
        BoardManager manager;
        auto possible_moves = manager.allMoves(popped_node.getState());
        
        // Add current node's state to closed list as it's about to be operated on
        _closedSet.insert(popped_node.getState());
        
        // Do each of the possible moves, create a new node for the new state
        for(auto &&move : possible_moves){
            // Create the child-node with information post-movement
            auto new_state = manager.applyMoveCloning(popped_node.getState(), move);
            
            // Normalize the resulting state
            new_state.normalizeState();
            
            // Add the move to the node's parents move list
            vector<sbpMove> ml = popped_node.getMoveList();
            ml.push_back(move);
            
            // Increment the path cost
            size_t new_pc = popped_node.getPathCost() + 1;
            
            sbpSearchNode child(&popped_node, new_state, ml, new_pc);
            
            // Check if the state is now solved
            if(new_state.gameStateSolved()){
                solved = true;
                solved_node.setParent(child.getParent());
                solved_node.setState(child.getState());
                solved_node.setMoveList(child.getMoveList());
                solved_node.setPathCost(child.getPathCost());
                break;
            }
            
            // Else, add it to the open list if it's not already in the closed list
            bool in_closed_list = false;
            if(_closedSet.find(child.getState()) != _closedSet.end())
                in_closed_list = true;
            
            bool in_opened_list = false;
            if(_generalOpenSet.find(child.getState()) != _generalOpenSet.end())
                in_opened_list = true;

            if((!in_closed_list) && (!in_opened_list)){
                _queueOpenList.push(child);
                _generalOpenSet.insert(child.getState());
            }
        }
        
        if(solved){
            timer.stop_timer();
            printResults(solved_node, timer.get_exc_time_in_ms(), node_counter);
        }
    }
}

void sbpSearch::AStar(const sbpState &state, function<size_t(sbpSearchNode)> heuristic_func){
    //sbpHeuristics heuristic;
    BoardManager manager;
    ExeTimer timer;
    size_t node_counter{};
    volatile bool solved = false;
    sbpState ss;
    vector<sbpMove> sbpm;
    sbpSearchNode solved_node{nullptr, ss, sbpm, static_cast<size_t>(-1)};
    timer.start_timer();
    
    sbpState pa = state.clone();
    pa.normalizeState();
    
    
    sbpSearchNode parent{pa};
    if(parent.getState().gameStateSolved()){
        std::cout << "Game state was already solved, no moves necessary.\n";
        return;
    }
    
    // Starting node needs g and h values, g is 0, then computer manhattan
    parent.setPathCost(0);
    size_t heuristic_cost = heuristic_func(parent);
    parent.setHeuristicCost(heuristic_cost);
    
    // Different from BFS --> Heap takes the full node, not just the state
    _heap.push(parent);
    // Add the state to the open hashset so we can do efficiencies [sorry it's late]
    _generalOpenSet.insert(parent.getState());
    
    while((!_heap.empty()) && (solved == false)){
        
        //So yeah....a copy constructor would have been nice.
        sbpSearchNode *tmpND = _heap.top().getParent();
        sbpState tmpST = _heap.top().getState();
        vector<sbpMove> tmpML = _heap.top().getMoveList();
        size_t tmpPC = _heap.top().getPathCost();
        size_t tmpHC = _heap.top().getHeuristicCost();
        sbpSearchNode popped_node(tmpND, tmpST, tmpML, tmpPC);
        popped_node.setHeuristicCost(tmpHC);
        
        // Pop off the node with the lowest cost f = g + h
        // Seems like a good place to explain this...as nodes are added to the
        // 'heap' (std::priority_queue) a comparison function is used for
        // heap ordering...this function simply computes f = g + h, so the node
        // with the lowest g + h will always be at the top of the heap
        _heap.pop();
        _generalOpenSet.erase(popped_node.getState());
        ++node_counter;
        
        // All possible moves from node
        auto possible_moves = manager.allMoves(popped_node.getState());
        
        // Move popped into the closed set
        _closedSet.insert(popped_node.getState());
        
        for(auto &&move : possible_moves){
            auto new_state = manager.applyMoveCloning(popped_node.getState(), move);
            new_state.normalizeState();
            
            vector<sbpMove> ml = popped_node.getMoveList();
            ml.push_back(move);
            
            size_t new_pc = popped_node.getPathCost() + 1;
            size_t h_cost = heuristic_func(popped_node);
            
            sbpSearchNode child(&popped_node, new_state, ml, new_pc);
            child.setHeuristicCost(h_cost);
            
            if(new_state.gameStateSolved()){
                solved = true;
                solved_node.setParent(child.getParent());
                solved_node.setState(child.getState());
                solved_node.setMoveList(child.getMoveList());
                solved_node.setPathCost(child.getPathCost());
                solved_node.setHeuristicCost(child.getHeuristicCost());
                break;
            }
            
            bool in_closed_list = false;
            if(_closedSet.find(child.getState()) != _closedSet.end())
                in_closed_list = true;
            
            bool in_open_list = false;
            if(_generalOpenSet.find(child.getState()) != _generalOpenSet.end())
                in_open_list = true;
            
            if((!in_closed_list) && (!in_open_list)){
                _heap.push(child);
                _generalOpenSet.insert(child.getState());
            }
        }
        
        if(solved){
            timer.stop_timer();
            printResults(solved_node, timer.get_exc_time_in_ms(), node_counter);
        }
    }
}

void sbpSearch::printResults(sbpSearchNode solved_node, double exe_time, size_t node_counter){
    auto move_list = solved_node.getMoveList();
    auto length = solved_node.getPathCost();
    for(auto &&move : move_list){
        cout << move.getPieceAndDirection() << '\n';
    }
    solved_node.getState().outputGameState();
    cout << "Total search time: " << exe_time << "ms.\n";
    cout << "Total nodes visited: " << node_counter << ".\n";
    cout << "Total solution length: " << length << ".\n";
}










