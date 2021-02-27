//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_QUEEN_H
#define E_CHESS_QUEEN_H


#include "Piece.h"

class Queen : public Piece {

public:
    Queen(PieceColor aColor);

    virtual char PieceToFEN();

};


#endif //E_CHESS_QUEEN_H
