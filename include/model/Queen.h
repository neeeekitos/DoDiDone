#ifndef E_CHESS_QUEEN_H
#define E_CHESS_QUEEN_H


#include "Piece.h"

/**
 * Represents a queen
 */
class Queen : public Piece {

public:
    /**
     * Constructor of a queen with a color
     * @param aColor The given color
     */
    Queen(PieceColor aColor);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();

};


#endif //E_CHESS_QUEEN_H
