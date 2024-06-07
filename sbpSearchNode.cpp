//
//  sbpSearchNode.cpp
//  CS510 Assignment 2
//
//  Created by Sean Grimes on 1/31/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpSearchNode.hpp"

//----- Node Class, the nodes that will make up the search tree(s)
sbpSearchNode::sbpSearchNode(sbpState state)
:_parent{nullptr}, _state{state}, _moveList{}, _pathCost{0}, _heuristicEstimate{0}
{}

sbpSearchNode::sbpSearchNode(sbpSearchNode *parent,
                             sbpState state,
                             vector<sbpMove> moveList,
                             size_t pathCost)
:_parent{parent}, _state{state}, _moveList{moveList}, _pathCost{pathCost}, _heuristicEstimate{0}
{}

sbpSearchNode* sbpSearchNode::getParent() const{
    return _parent;
}

sbpState sbpSearchNode::getState() const{
    return _state;
}

vector<sbpMove> sbpSearchNode::getMoveList() const{
    return _moveList;
}

size_t sbpSearchNode::getPathCost() const{
    return _pathCost;
}

size_t sbpSearchNode::getHeuristicCost() const{
    return _heuristicEstimate;
}

void sbpSearchNode::setParent(sbpSearchNode *parent){
    _parent = parent;
}

void sbpSearchNode::setState(sbpState state){
    _state = state;
}

void sbpSearchNode::setMoveList(vector<sbpMove> ml){
    _moveList = ml;
}

void sbpSearchNode::setPathCost(size_t pc){
    _pathCost = pc;
}

void sbpSearchNode::setHeuristicCost(size_t hc){
    _heuristicEstimate = hc;
}

// Please note here that when ties occur for the total f(n) [g + h]
// That the tie-breaker goes to the element with the lower cost of 'h' as that
// presumably has the least amount of moves left to make and the goal is never
// really that far away distance wise, but is move wise
bool sbpSearchNodeCompare::operator()(const sbpSearchNode &lhs, const sbpSearchNode &rhs) const{
    size_t lhs_total_cost = lhs.getHeuristicCost() + lhs.getPathCost();
    size_t rhs_total_cost = rhs.getHeuristicCost() + rhs.getPathCost();
    if(lhs_total_cost != rhs_total_cost)
        return lhs_total_cost > rhs_total_cost;
    else
        return lhs.getHeuristicCost() > rhs.getHeuristicCost();
}

