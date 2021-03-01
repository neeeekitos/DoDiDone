//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_BISHOP_H
#define E_CHESS_BISHOP_H

// Edited by Rivaldo

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

// Standard library
#include <vector>

using namespace std;

class Bishop : public Piece {
    public:

    Bishop(PieceColor color);
        /*
         * builder de Bishop
         */

        char PieceToFEN();
        /*
         * get the FEN representation of a Piece
         */

        vector<int> eatableCase (Chessboard board);
        /*
         * List of all the case that can be eaten
         */

        bool isValidMove(Chessboard board, int pos);
        /*
         * Check if a move is valid or not
         */

        vector<int> movements(Chessboard board);
        /*
         * List of all the possible moves
         */

    private:
    vector<int> movelists{-11, -9, 9, 11};
};


#endif //E_CHESS_BISHOP_H
