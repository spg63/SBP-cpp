//
//  sbpState.hpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpState_hpp
#define sbpState_hpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "FileUtils.hpp"
#include "StrUtils.hpp"
#include "NumUtils.hpp"

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;
using std::cout;

class sbpState{
public:
    void loadGameState(const string &filename);
    void outputGameState() const;
    sbpState clone() const;
    vector<vector<int>> getBoard() const;
    void modifyBoard(int row, int col, int newval);
    bool gameStateSolved() const;
    // Not sure which way will be best yet... the method that takes 2 objects
    // is the one that's actually implemented, the implicit method just passes
    // the dereferenced (*this) this pointer along as the 'me' parameter
    bool stateEqual(const sbpState &other) const;
    bool stateEqual(const sbpState &me, const sbpState &other) const;
    
    // Again, not sure whether this will need to modify random states, or just
    // "this" state, so both are implemented for now, will remove one when the
    // requirements for HW2 are available
    // Algorithm: Taken almost word for word from the assignment PDF
    // Assumed author: Christopher Geib
    // NOTE: I changed the matrix indicies from [j][i] to [i][j], they were
    //       reversed for some reason...
    void normalizeState();
    void normalizeState(sbpState &state);
    void swapIdx(sbpState &state, int idx1, int idx2);
   
private:
    int _width;
    int _height;
    vector<vector<int>> _gameboard;
    
private:
    
};

    bool operator==(const sbpState &lhs, const sbpState &rhs);

class stateHash{
public:
    std::size_t operator() (const sbpState &state) const;
};

class stateCompare{
public:
    bool operator() (const sbpState &lhs, const sbpState &rhs) const;
};

#endif /* sbpState_hpp */
