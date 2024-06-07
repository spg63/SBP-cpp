//
//  sbpPiece.hpp
//  CS510
//
//  Created by Sean Grimes on 1/15/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#ifndef sbpPiece_hpp
#define sbpPiece_hpp

#include <stdexcept>
#include "blockType.hpp"

class sbpPiece{
public:
    sbpPiece(int numID, int width, int height, int row, int col);
    int _width;
    int _height;
    int _num_id;
    
    // NOTE: This is the location of the upper left 'brick' of the piece, the
    //       full dimensions can be calculated based on it's width and height
    int _row_num;
    int _col_num;
    blockType type;
};


#endif /* sbpPiece_hpp */
