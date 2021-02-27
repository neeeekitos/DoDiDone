//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_PIECE_H
#define E_CHESS_PIECE_H

#include <string>

#include "GameConstants.h"

class Piece {

public:

    virtual string getImage() = 0;

    Piece(PieceColor aColor);

    boolean isEmpty();

    virtual char PieceToFEN();

private :
    /**
     * This represents the color of the piece
     */
    PieceColor color = EMPTY;

};


#endif //E_CHESS_PIECE_H
