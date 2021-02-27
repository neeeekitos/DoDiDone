//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_KING_H
#define E_CHESS_KING_H

// Edited by Rivaldo

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

// Standard library
#include <vector>

using namespace std;

class King: public Piece {
    public:
        King(PieceColor color);
        /*
         * builder de King
         */

        virtual char PieceToFEN();
        /*
         * get the FEN representation of a Piece
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
        vector<int> movelists{-11, -10, -9, -1, 1, 9, 10, 11};
        vector<int> moveroques{-2,2};
};



#endif //E_CHESS_KING_H
