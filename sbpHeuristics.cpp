//
//  sbpHeuristics.cpp
//  CS510 Assignment 2
//
//  Created by Sean Grimes on 1/30/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpHeuristics.hpp"

size_t sbpHeuristics::getManhattanDistance(const sbpSearchNode &node){
    int dist_x, dist_y;
    getDxDy(dist_x, dist_y, node);
    
    auto scaler = 1; // The cost for each movement...may be used in custom heuristic.
    return scaler * (dist_x + dist_y);
}

size_t sbpHeuristics::getDiagonalDistance(const sbpSearchNode &node){
    int dist_x, dist_y;
    getDxDy(dist_x, dist_y, node);
    
    auto scaler = 1;
    // Chebyshev Distance:
    // https://en.wikipedia.org/wiki/Chebyshev_distance
    return scaler * (dist_x + dist_y) + (scaler - 2 * scaler) * std::min(dist_x, dist_y);
}

size_t sbpHeuristics::getEucDistance(const sbpSearchNode &node){
    int dist_x, dist_y;
    getDxDy(dist_x, dist_y, node);
    
    auto scaler = 1;
    return scaler * std::sqrt(dist_x * dist_x + dist_y * dist_y);
}

size_t sbpHeuristics::getBlockingCount(const sbpSearchNode &node){
    
    // Determine the number of blocks between
    // the master and goal, since they will need to be moved at least once.
    // Determining number or blocks between will be done very simply:
    //  From row# bottom_of_master to row# top_of_goal, within the column(s)
    //  that are as wide as the master, count number of move areas that are
    //  blocked
    //  From column# goal to first column holding master, count blocked move
    //  areas.
    // Basically assume we can follow the most logical path, then count the # of
    // moves that would be blocked by blocks.
    
    // So basically you can move in 3 ways between the master and the goal with
    // out basic layout: e.g. when master upper left, goal lower right
    //  - Half square by going left / down
    //  - Half square by going down / left
    // This holds true for the other 3 orientations as well
    // However...we can't make assumptions, so need to count the minimum # of
    // blocks between the 3 paths
    
    
    int mx, my, gx, gy;
    BoardManager manager;
    auto master = manager.getPieceDimensions(node.getState(), 2);
    auto goal = manager.getPieceDimensions(node.getState(), -1);
    
    calculateDxDy(mx, my, gx, gy, master, goal);
    
    bool left{}, top{};
    if(mx < gx)
        left = true;
    if(my < gy)
        top = true;
    
    auto gameboard = node.getState().getBoard();
    
    unordered_set<int> upper_right;
    unordered_set<int> lower_left;
    
    // go right and down (master is above and to the left of goal)
    if(left && top){
        int start_right = mx, stop_right = gx;
        int start_down = my, stop_down = gy;
        int num_rights = 0, num_downs = 0;
        
        /// Going right, then down
        for(int col_num = start_right; col_num < stop_right; ++col_num){
            upper_right.insert(gameboard[my][col_num]);
            ++num_rights;
        }
        for(int row_num = start_down; row_num < stop_down; ++row_num){
            upper_right.insert(gameboard[row_num][mx]);
            ++num_downs;
        }
        
        /// Going down, then right
        for(int row_num = start_down; row_num < stop_down; ++row_num){
            lower_left.insert(gameboard[row_num][mx]);
        }
        
        for(int col_num = start_right; col_num < stop_right; ++col_num){
            lower_left.insert(gameboard[my][col_num]);
        }
    }
    // go right and up (master is below and to the left of goal)
    else if(left && !top){
        int start_right = mx, stop_right = gx;
        int start_up = my, stop_up = gy;
        int num_rights = 0, num_ups = 0;
        
        /// Going right, then up
        for(int col_num = start_right; col_num < stop_right; ++col_num){
            upper_right.insert(gameboard[my][col_num]);
            ++num_rights;
        }
        for(int row_num = start_up; row_num < stop_up; --row_num){
            upper_right.insert(gameboard[row_num][mx]);
            ++num_ups;
        }
        
        /// Going up, then right
        for(int row_num = start_up; row_num < stop_up; --row_num){
            lower_left.insert(gameboard[row_num][mx]);
        }
        for(int col_num = start_right; col_num < stop_right; ++col_num){
            lower_left.insert(gameboard[my][col_num]);
        }
    }
    // go left and down (master is above and to the right of goal)
    else if(!left && top){
        int start_left = mx, stop_left = gx;
        int start_down = my, stop_down = gy;
        int num_lefts = 0, num_downs = 0;
       
        /// Going left, then down
        for(int col_num = start_left; col_num > stop_left; --col_num){
            upper_right.insert(gameboard[my][col_num]);
            ++num_lefts;
        }
        for(int row_num = start_down; row_num < stop_down; ++row_num){
            upper_right.insert(gameboard[row_num][mx]);
            ++num_downs;
        }
        
        /// Going down, then left
        for(int row_num = start_down; row_num < stop_down; ++row_num){
            lower_left.insert(gameboard[row_num][mx]);
        }
        for(int col_num = start_left; col_num > stop_left; --col_num){
            lower_left.insert(gameboard[my][col_num]);
        }
    }
    // go left and up (master is below and to the right of goal)
    else{
        int start_left = mx, stop_left = gx;
        int start_up = my, stop_up = gy;
        int num_lefts = 0, num_ups = 0;
        
        /// Going left, then up
        for(int col_num = start_left; col_num > stop_left; --col_num){
            upper_right.insert(gameboard[my][col_num]);
            ++num_lefts;
        }
        for(int row_num = start_up; row_num > stop_up; --row_num){
            upper_right.insert(gameboard[row_num][mx]);
            ++num_ups;
        }
        
        /// Going up, then left
        for(int row_num = start_up; row_num > stop_up; --row_num){
            lower_left.insert(gameboard[row_num][mx]);
        }
        for(int col_num = start_left; col_num > stop_left; --col_num){
            lower_left.insert(gameboard[my][col_num]);
        }
    }
    
    // Make sure to get rid of any stuff we can't move (though it shouldn't be in there)
    // Basically just an extra check if I'm off by 1 above anywhere
    upper_right.insert(1);
    upper_right.insert(-1);
    upper_right.erase(-1);
    upper_right.erase(1);
    
    lower_left.insert(1);
    lower_left.insert(-1);
    lower_left.erase(-1);
    lower_left.erase(1);
    
    size_t min_1 = std::min(upper_right.size(), lower_left.size());
    return min_1;
}

size_t sbpHeuristics::getManhattanAndBlocking(const sbpSearchNode &node){
    size_t manhattan = getManhattanDistance(node);
    size_t blocking = getBlockingCount(node);
    return manhattan + blocking;
}

size_t sbpHeuristics::getBestGuess(const sbpSearchNode &node){
    // No need to separatly max manhattan and blocking since their
    // total combine will be returned from getManhattanAndBlocking
    size_t max_1 = std::max(getEucDistance(node), getDiagonalDistance(node));
    return std::max(getManhattanAndBlocking(node), max_1);
}

// ----- Helpers to keep content of heuristics short and easy to read ----------
void sbpHeuristics::getDxDy(int &dist_x, int &dist_y, const sbpSearchNode &node){
    BoardManager manager;
    auto master = 2;
    auto goal = -2;
    auto state = node.getState();
    
    auto master_loc = manager.getPieceDimensions(state, master);
    auto goal_loc = manager.getPieceDimensions(state, goal);
    
    int master_x, master_y, goal_x, goal_y;
    calculateDxDy(master_x, master_y, goal_x, goal_y, master_loc, goal_loc);
    
    dist_x = std::abs(master_x - goal_x);
    dist_y = std::abs(master_y - goal_y);
}

void sbpHeuristics::calculateDxDy(int &master_x,
                                  int &master_y,
                                  int &goal_x,
                                  int &goal_y,
                                  const pair<pair<int, int>, pair<int, int>> master,
                                  const pair<pair<int, int>, pair<int, int>> goal){
    auto master_upper_left = master.first;
    auto master_lower_right = master.second;
    auto goal_upper_left = goal.first;
    auto goal_lower_right = goal.second;
    
    // Now figure out if we're left/right and above/below the goal
    // Since the blocks aren't limited in their dimensions, the manhattan
    // heuristic will overestimate if one makes bad assumptions, so these
    // checks will tell me whether to use the upper left corner, or lower right
    // corner of the master block for the calculations
    
    // Check if master and goal are on the same row(s)
    if((master_upper_left.first == goal_upper_left.first) && (master_lower_right.first == goal_lower_right.first)){
        // Now we know we're on the same row(s), check for left / right
        if(master_upper_left.second <= goal_upper_left.second){ // master is to left (or equal)
            setLowerRightDimension(master_x, master_y, goal_x, goal_y, master_lower_right, goal_lower_right);
        }
        else{ // master is to the right, use upper left corner for dimensions
            setUpperLeftDimensions(master_x, master_y, goal_x, goal_y, master_upper_left, goal_upper_left);
        }
    }
    // Check if master and goal are on the same column(s)
    else if((master_upper_left.second == goal_upper_left.second) && (master_lower_right.second == goal_lower_right.second)){
        if(master_upper_left.first >= goal_upper_left.first){ // master is above (or equal)
            setLowerRightDimension(master_x, master_y, goal_x, goal_y, master_lower_right, goal_lower_right);
        }
        else{
            setUpperLeftDimensions(master_x, master_y, goal_x, goal_y, master_upper_left, goal_upper_left);
        }
    }
    // Check if master is above goal (L / R doesn't matter)
    else if(master_lower_right.first >= goal_upper_left.first){
        setLowerRightDimension(master_x, master_y, goal_x, goal_y, master_lower_right, goal_lower_right);
    }
    // Check if master is below goal (L / R doesn't matter)
    else if(master_upper_left.first <= goal_lower_right.first){
        setUpperLeftDimensions(master_x, master_y, goal_x, goal_y, master_upper_left, goal_upper_left);
    }
    else{
        std::cout << "Yeah....I felt like I was missing something\n";
        throw std::logic_error("Manhattan Distance, else clause....what'd I miss?");
    }
    
}

void sbpHeuristics::setUpperLeftDimensions(int &m_x,
                                           int &m_y,
                                           int &g_x,
                                           int &g_y,
                                           const pair<int, int> &master_upper_left,
                                           const pair<int, int> &goal_upper_left){
    m_x = master_upper_left.second;
    m_y = master_upper_left.first;
    g_x = goal_upper_left.second;
    g_y = goal_upper_left.first;
}

void sbpHeuristics::setLowerRightDimension(int &m_x,
                                           int &m_y,
                                           int &g_x,
                                           int &g_y,
                                           const pair<int, int> &master_lower_right,
                                           const pair<int, int> &goal_lower_right){
    m_x = master_lower_right.second;
    m_y = master_lower_right.first;
    g_x = goal_lower_right.second;
    g_y = goal_lower_right.first;
}
