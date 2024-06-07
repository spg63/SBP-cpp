//
//  sbpPiece.cpp
//  CS510
//
//  Created by Sean Grimes on 1/15/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "sbpPiece.hpp"

sbpPiece::sbpPiece(int numID, int width, int height, int row, int col)
: _num_id{numID}, _width{width}, _height{height}, _row_num{row}, _col_num{col}
{
    if(_width < 1 || _height < 1)
        throw std::logic_error("height / width must be greater than zero");
   
    if(_row_num < 0 || _col_num < 0)
        throw std::logic_error("Out of state bounds");
    
    if(_num_id < -1)
        throw std::logic_error("Oh");
    
    switch(_num_id){
        case -1: type = blockType::GOAL;
            break;
        case 0: type = blockType::EMPTY;
            break;
        case 1: type = blockType::WALL;
            break;
        case 2: type = blockType::MASTER;
            break;
        default:
            type = blockType::BASIC;
    }
}