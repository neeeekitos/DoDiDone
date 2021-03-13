#ifndef E_CHESS_BISHOP_H
#define E_CHESS_BISHOP_H

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

// Standard library
#include <vector>

using namespace std;

/**
 * This class represents a bishop
 */
class Bishop : public Piece {

public:

    /**
     * The constructor of a bishop
     * @param color
     */
    Bishop(PieceColor color);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    char PieceToFEN();

private:

    /**
     * The move list of a bishop. A move list is a relative translation
     * in the chess board
     */
    vector<int> movelists{-11, -9, 9, 11};
};


#endif //E_CHESS_BISHOP_H
