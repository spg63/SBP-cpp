//
//  sbpHeuristics.hpp
//  CS510 Assignment 2
//
//  Created by Sean Grimes on 1/30/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpHeuristics_hpp
#define sbpHeuristics_hpp
#include "sbpSearchNode.hpp"
#include "sbpState.hpp"
#include "BoardManager.hpp"
#include <unordered_set>
#include <algorithm>
#include <utility>
using std::pair;
using std::unordered_set;

class sbpHeuristics{
public:
    static size_t getManhattanDistance(const sbpSearchNode &node);
    static size_t getDiagonalDistance(const sbpSearchNode &node);
    static size_t getEucDistance(const sbpSearchNode &node);
    static size_t getManhattanAndBlocking(const sbpSearchNode &node);
    static size_t getBlockingCount(const sbpSearchNode &node);
    static size_t getBestGuess(const sbpSearchNode &node);
    
private:
    /*
     * Please Note: This all works on reference. Some people get annoyed by this,
     * talking about side effects and all. Personally, I think this makes life 
     * a lot easier * as long as one understands what's happening *
     *  THUS, this note.
     */
    static void getDxDy(int &dist_x, int &dist_y, const sbpSearchNode &node);
    
    static void calculateDxDy(int &mx,
                       int &my,
                       int &gx,
                       int &gy,
                       const pair<pair<int, int>, pair<int, int>> master,
                       const pair<pair<int, int>, pair<int, int>> goal);
    
    static void setUpperLeftDimensions(int &m_x,
                                int &m_y,
                                int &g_x,
                                int &g_y,
                                const pair<int, int> &master_upper_left,
                                const pair<int, int> &goal_upper_left);
    
    static void setLowerRightDimension(int &m_x,
                                int &m_y,
                                int &g_x,
                                int &g_y,
                                const pair<int, int> &master_lower_right,
                                const pair<int, int> &goal_lower_right);

};

#endif /* sbpHeuristics_hpp */
