#ifndef E_CHESS_KNIGHT_H
#define E_CHESS_KNIGHT_H

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

#include <vector>

using namespace std;

class Knight: public Piece {
    public:
    Knight(PieceColor color);
        /*
         * builder de Knight
         */

        virtual char PieceToFEN();
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
        vector<int> movelists{-21, -19, -12, -8, 8, 12, 19, 21};
};


#endif //E_CHESS_KNIGHT_H
