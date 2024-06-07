//
//  sbpState.cpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpState.hpp"

void sbpState::loadGameState(const string &filename){
    // This functions reads a file line by line
    vector<string> filelines = FileUtils::readLineByLine(filename);
    
    // For each line, split it on the comma
    auto file_line_num = 0;
    for(auto &&line : filelines){
        // Remove the trailing comma...cause it's in the way
        if(StrUtils::ends_with_string(line, ",")){
            line = line.substr(0, line.length() - 1);
        }
        
        auto split = StrUtils::splitStr(line, ',');
        
        // If on the first line of the file, set the dimensions
        if(file_line_num == 0){
            file_line_num++;
            _width = NumUtils::strToInt(split[0]);
            _height = NumUtils::strToInt(split[1]);
            if(_width <= 0 || _height <= 0)
                throw std::logic_error("width and height must be greater than 0");
            continue;
        }
        
        vector<int> mat_row;
        // Now we're looking at the rows of the matrix
        for(auto &&number : split){
            mat_row.push_back(NumUtils::strToInt(number));
        }
        _gameboard.push_back(mat_row);
    }
}

void sbpState::outputGameState() const{
    cout << _width << ',' << _height << ",\n";
    for(auto &&vec : _gameboard){
        for(auto &&ele : vec){
            cout << ele << ',';
        }
        cout << '\n';
    }
}

sbpState sbpState::clone() const{
    sbpState copy = *this;
    return copy;
}

vector<vector<int>> sbpState::getBoard() const{
    return _gameboard;
}

void sbpState::modifyBoard(int row, int col, int newval){
    if(newval == 1)
        throw std::logic_error("Why you modifying a wall??");
    if((row > _gameboard.size()) || (row < 0))
        throw std::out_of_range("Out of gameboard bounds");
    if((col > _gameboard[0].size()) || (col < 0))
        throw std::out_of_range("Out of gameboard bounds");
    
    _gameboard[row][col] = newval;
}

bool sbpState::gameStateSolved() const{
    for(auto &&vec : _gameboard){
        for(auto &&cell : vec){
            if(cell == -1)
                return false;
        }
    }
    return true;
}

bool sbpState::stateEqual(const sbpState &other) const{
    return stateEqual(*this, other);
}

bool sbpState::stateEqual(const sbpState &me, const sbpState &other) const{
    // Simple Checks First
    if((me._gameboard.size() == 0) || (other._gameboard.size() == 0)){
        throw std::logic_error("State size *shouldn't* be zero");
    }
    
    if(me._gameboard.size() != other._gameboard.size())
        return false;
    
    if(me._gameboard[0].size() != other._gameboard[0].size())
        return false;
    
    // Now we know that both gameboards have some content, and size is the same
    // Can safely run through both without out-of-bounds issues
    auto height = me._gameboard.size();
    auto width = me._gameboard[0].size();
    for(auto i = 0; i < height; ++i){
        for(auto j = 0; j < width; ++j){
            if(me._gameboard[i][j] != other._gameboard[i][j])
                return false;
        }
    }
    return true;
}

void sbpState::normalizeState(){
    normalizeState(*this);
}

void sbpState::normalizeState(sbpState &state){
    int nextIdx = 3;
    auto h = state._gameboard.size();
    auto w = state._gameboard[0].size();
    for(auto i = 0; i < h; ++i){
        for(auto j = 0; j < w; ++j){
            if(state._gameboard[i][j] == nextIdx){
                ++nextIdx;
            }
            else if(state._gameboard[i][j] > nextIdx){
                swapIdx(state, nextIdx, state._gameboard[i][j]);
                ++nextIdx;
            }
        }
    }
}

void sbpState::swapIdx(sbpState &state, int idx1, int idx2){
    auto h = state._gameboard.size();
    auto w = state._gameboard[0].size();
    for(auto i = 0; i < h; ++i){
        for(auto j = 0; j < w; ++j){
            if(state._gameboard[i][j] == idx1)
                state.modifyBoard(i, j, idx2);
            else if(state._gameboard[i][j] == idx2)
                state.modifyBoard(i, j, idx1);
        }
    }
}

// ----- Needed for hashing in unordered_set
std::size_t stateHash::operator()(const sbpState &state) const{
    
    // Do note: This is very very similar to the hash function found
    // in the boost library, found on stackoverflow.com:
    // http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
    // Posted by: Holkann
    
    std::size_t seed = 0;
    for(auto &&vec : state.getBoard()){
        for(auto &&val : vec){
            seed ^= val + 0x9e3770b9 + (seed << 6) + (seed >> 2);
        }
    }
    
    return seed;
    
}

bool operator==(const sbpState &lhs, const sbpState &rhs){
    return lhs.stateEqual(rhs);
}








