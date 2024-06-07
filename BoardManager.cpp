//
//  BoardManager.cpp
//  CS510
//
//  Created by Sean Grimes on 1/15/16.
//  Copyright © 2016 Sean Grimes. All rights reserved.
//

#include "BoardManager.hpp"

vector<sbpMove> BoardManager::allMovesHelp(const sbpState &state, int pieceID){
    auto dimensions = getPieceDimensions(state, pieceID);
    //          lower right row            upper left row
    int height = (dimensions.second.first - dimensions.first.first) + 1;
    //           lower right col             upper left col
    int width = (dimensions.second.second - dimensions.first.second) + 1;
    auto board = state.getBoard();
    
    auto upper_left_corner = dimensions.first;
    auto lower_right_corner = dimensions.second;
    
    // Which directions can we move
    bool up     = true;
    bool down   = true;
    bool left   = true;
    bool right  = true;
    
    // NOTE: the boarder wall should prevent against out of bounds errors
    // Check if we can move up by looking at the row above for the given width
    // and starting at the proper column
    auto row_above = upper_left_corner.first - 1;
    for(auto i = upper_left_corner.second; i < upper_left_corner.second + width; ++i){
        // If ID == 2, i.e. the master brick, it can go on "-1", otherwise -1 is illegal
        if(pieceID == 2){
            if((board[row_above][i] != 0) && (board[row_above][i] != -1)){
                up = false;
                break;
            }
        }
        else{
            if(board[row_above][i] != 0){
                up = false;
                break;
            }
        }
    }
    
    // Since my dimensions are the up-left, low-right corners, now we start at the
    // bottom right of the block, and move left across the columns at the row below
    // the block
    auto row_below = lower_right_corner.first + 1;
    for(auto i = lower_right_corner.second; i > lower_right_corner.second - width; --i){
        if(pieceID == 2){
            if((board[row_below][i] != 0) && (board[row_below][i] != -1)){
                down = false;
                break;
            }
        }
        else{
            if(board[row_below][i] != 0){
                down = false;
                break;
            }
        }
    }
    
    // Now lets check if we can move left, same process as above
    // Check the column to the left, by moving down a row each iteration
    auto col_left = upper_left_corner.second - 1;
    for(auto i = upper_left_corner.first; i < upper_left_corner.first + height; ++i){
        if(pieceID == 2){
            if((board[i][col_left] != 0) && (board[i][col_left] != -1)){
                left = false;
                break;
            }
        }
        else{
            if(board[i][col_left] != 0){
                left = false;
                break;
            }
        }
    }
    
    // Check right, same as above, but since we're starting in the lower right
    // corner we need to move up the rows instead of moving down
    auto col_right = lower_right_corner.second + 1;
    for(auto i = lower_right_corner.first; i > lower_right_corner.first - height; --i){
        if(pieceID == 2){
            if((board[i][col_right] != 0) && (board[i][col_right] != -1)){
                right = false;
                break;
            }
        }
        else{
            if(board[i][col_right] != 0){
                right = false;
                break;
            }
        }
    }
    
    vector<sbpMove> possibleMoves;
    // order: up, down, left, right
    if(up)
        possibleMoves.emplace_back(sbpMove(pieceID, Direction::UP));
    if(down)
        possibleMoves.emplace_back(sbpMove(pieceID, Direction::DOWN));
    if(left)
        possibleMoves.emplace_back(sbpMove(pieceID, Direction::LEFT));
    if(right)
        possibleMoves.emplace_back(sbpMove(pieceID, Direction::RIGHT));
    if(possibleMoves.size() == 0)
        possibleMoves.emplace_back(sbpMove(pieceID, Direction::NO_MOVE));
    
    return possibleMoves;
}

vector<sbpMove> BoardManager::allMoves(const sbpState &state){
    int minID, maxID;
    minID = maxID = 2;
    vector<sbpMove> allPossibleMoves;
    
    // Determine the max pieceID in the current state
    for(auto &&vec : state.getBoard()){
        for(auto &&ele : vec){
            if(maxID < ele)
                maxID = ele;
        }
    }
    // Simply run through pieces 2 - maxID and get their possible moves
    // They will be sorted by ID based on the loop order, and the allMovesHelp
    // function returns in the up-down-left-right order, so no sorting
    // necessary, just return the list
    vector<sbpMove> moves_per_ID;
    for(auto start = minID; start <= maxID; start++){
        moves_per_ID = allMovesHelp(state, start);
        for(int i = 0; i < moves_per_ID.size(); ++i){
            if(moves_per_ID[i].getMoveDirection() != Direction::NO_MOVE)
                allPossibleMoves.push_back(moves_per_ID[i]);
        }
    }
    return allPossibleMoves;
}

void BoardManager::applyMove(sbpState &state, const sbpMove &move){
    auto board = state.getBoard();
    auto dimensions = getPieceDimensions(state, move.getPieceID());
    int height = (dimensions.second.first - dimensions.first.first) + 1;
    int width = (dimensions.second.second - dimensions.first.second) + 1;
    
    // Deal with the four possible directions, assume move is valid
    if(move.getMoveDirection() == Direction::UP){
        auto left_col = dimensions.first.second;
        auto bot_row = dimensions.second.first;
        int row_cnt = 0;
        for(auto i = bot_row; i >= bot_row - height; --i){
            for(auto j = left_col; j < left_col + width; ++j){
                if(row_cnt == 0){
                    state.modifyBoard(i, j, 0);
                }
                else{
                    state.modifyBoard(i, j, move.getPieceID());
                }
            }
            ++row_cnt;
        }
    }
    else if(move.getMoveDirection() == Direction::DOWN){
        auto left_col = dimensions.first.second;
        auto top_row = dimensions.first.first;
        
        // To handle blocks with height > 1, we need to do one row at a time
        int row_cnt = 0; // Zero out the top row
        for(auto i = top_row; i <= top_row + height; ++i){ //<= because we're moving 1 passed the height
            for(auto j = left_col; j < left_col + width; ++j){
                if(row_cnt == 0){
                    state.modifyBoard(i, j, 0);
                }
                else{
                    state.modifyBoard(i, j, move.getPieceID());
                }
            }
            ++row_cnt;
        }
    }
    else if(move.getMoveDirection() == Direction::LEFT){
        int col_cnt = 0;
        auto right_col = dimensions.second.second;
        auto top_row = dimensions.first.first;
        // Move 'backwards', so we can zero out, then move the block
        for(auto j = right_col; j >= right_col - width; --j){ // move across the columns 'slowly'
            for(auto i = top_row; i < top_row + height; ++i){
                if(col_cnt == 0){
                    state.modifyBoard(i, j, 0);
                }
                else{
                    state.modifyBoard(i, j, move.getPieceID());
                }
            }
            ++col_cnt;
        }
        
    }
    else if(move.getMoveDirection() == Direction::RIGHT){
        int col_cnt = 0;
        auto left_col = dimensions.first.second;
        auto top_row = dimensions.first.first;
        // Move forwards, zero the first column, then the block
        for(auto j = left_col; j <= left_col + width; ++j){
            for(auto i = top_row; i < top_row + height; ++i){
                if(col_cnt == 0){
                    state.modifyBoard(i, j, 0);
                }
                else{
                    state.modifyBoard(i, j, move.getPieceID());
                }
            }
            ++col_cnt;
        }
    }
    else{
        throw std::runtime_error("Not a valid move direction...");
    }
}

sbpState BoardManager::applyMoveCloning(const sbpState &state, const sbpMove &move){
    sbpState cloned = state.clone();
    applyMove(cloned, move);
    return cloned;
}

//---------------------------------------
pair<pair<int, int>, pair<int, int>> BoardManager::getPieceDimensions(const sbpState &state, int pieceID){
    vector<vector<int>> board = state.getBoard();
    pair<int, int> start;
    pair<int, int> end;
    bool start_found = false;
    
    auto num_rows = board.size();
    auto num_cols = board[0].size();
    for(auto row = 0; row < num_rows; ++row){
        for(auto col = 0; col < num_cols; ++col){
            if((board[row][col] == pieceID) && (start_found == false)){
                start = make_pair(row, col);
                end = make_pair(row, col);
                start_found = true;
                continue;
            }
            // We are looking at a double/triper/whatever size block, grow the dimensions
            // as we move right or down
            else if((board[row][col] == pieceID) && (start_found == true)){
                end = make_pair(row, col);
            }
        }
    }
    
    return make_pair(start, end);
}












