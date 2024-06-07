//
//  sbpMove.hpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpMove_hpp
#define sbpMove_hpp

#include <utility>
#include <string>
#include "Direction.hpp"
#include "StrUtils.hpp"
using std::pair;

class sbpMove{
public:
    sbpMove(int piece_num, Direction dir);
    
    int getPieceID() const;
    Direction getMoveDirection() const;
    std::string getStrType() const;
    std::string getPieceAndDirection() const;

private:
    // The actual move
    pair<int, Direction> move;
};

#endif /* sbpMove_hpp */
