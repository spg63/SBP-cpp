//
//  BoardManager.hpp
//  CS510
//
//  Created by Sean Grimes on 1/15/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef BoardManager_hpp
#define BoardManager_hpp

#include "sbpMove.hpp"
#include "sbpPiece.hpp"
#include "sbpState.hpp"
#include <vector>
#include <utility>
using std::vector;
using std::pair;
using std::make_pair;

class BoardManager{
public:
    // Will return all moves that the given piece can perform, sorted according to instruction PDF
    vector<sbpMove> allMovesHelp(const sbpState &state, int pieceID);
    
    // Will return all moves possible on a given state
    vector<sbpMove> allMoves(const sbpState &state);
    
    // Applies a given move to the given state, state is operated on by reference
    // NOTE: Sorry to the lisp lovers, but side effects are nice sometimes...
    void applyMove(sbpState &state, const sbpMove &move);
    
    // Same as above, but returns a new state instead of messing with the current one
    sbpState applyMoveCloning(const sbpState &state, const sbpMove &move);
    
    // returns dimensions <<row#,col#>,<row#,col#>> of the piece where the first pair is the upper left corner
    // and the second pair is the lower right corner
    pair<pair<int, int>, pair<int, int>> getPieceDimensions(const sbpState &state, int pieceID);
    
};

#endif /* BoardManager_hpp */
