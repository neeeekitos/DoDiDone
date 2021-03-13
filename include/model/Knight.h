#ifndef E_CHESS_KNIGHT_H
#define E_CHESS_KNIGHT_H

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

#include <vector>

using namespace std;

/**
 * Represents a knight
 */
class Knight: public Piece {
public:

    /**
     * Constructor of a knight
     * @param color
     */
    Knight(PieceColor color);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();


private:

    /**
     * The move list of a knight. A move list is a relative translation
     * in the chess board
     */
    vector<int> movelists{-21, -19, -12, -8, 8, 12, 19, 21};
};


#endif //E_CHESS_KNIGHT_H
