//
//  sbpMove.cpp
//  CS510
//
//  Created by Sean Grimes on 1/13/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpMove.hpp"

sbpMove::sbpMove(int piece_num, Direction dir){
    move = std::make_pair(piece_num, dir);
}

int sbpMove::getPieceID()const {
    return move.first;
}

Direction sbpMove::getMoveDirection()const {
    return move.second;
}

std::string sbpMove::getStrType()const {
    switch(this->move.second){
        case Direction::UP: return std::string("UP");
            break;
        case Direction::DOWN: return std::string("DOWN");
            break;
        case Direction::LEFT: return std::string("LEFT");
            break;
        case Direction::RIGHT: return std::string("RIGHT");
            break;
        case Direction::NO_MOVE: return std::string("NO_MOVE");
            break;
        default: return std::string("WFK");
    }
}

std::string sbpMove::getPieceAndDirection() const{
    auto id = std::string(StrUtils::numToString(getPieceID()));
    auto dir = std::string(getStrType());
    return std::string("(" + id + "," + dir + ")");
}