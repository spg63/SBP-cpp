//
//  sbpSearchNode.hpp
//  CS510 Assignment 2
//
//  Created by Sean Grimes on 1/31/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpSearchNode_hpp
#define sbpSearchNode_hpp
#include "sbpState.hpp"
#include "sbpMove.hpp"

class sbpSearchNode{
public:
    // Should only be used when creating the parent
    sbpSearchNode(sbpState state);
    // Will be used when creating children
    sbpSearchNode(sbpSearchNode *parent, sbpState state, vector<sbpMove> moveList, size_t pathCost);
    
    //sbpSearchNode(sbpSearchNode const &node);
    //sbpSearchNode &operator=(const sbpSearchNode &other);
    
    sbpSearchNode *getParent() const;
    sbpState getState() const;
    vector<sbpMove> getMoveList() const;
    size_t getPathCost() const;
    size_t getHeuristicCost() const;
    void setParent(sbpSearchNode *parent);
    void setState(sbpState state);
    void setMoveList(vector<sbpMove> ml);
    void setPathCost(size_t pc);
    void setHeuristicCost(size_t hc);
    
private:
    sbpSearchNode   *_parent;
    sbpState        _state;
    vector<sbpMove> _moveList;
    size_t          _pathCost;
    size_t          _heuristicEstimate;
    
};

class sbpSearchNodeCompare{
public:
    bool operator()(const sbpSearchNode &lhs, const sbpSearchNode &rhs) const;
};



#endif /* sbpSearchNode_hpp */
