//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_PAWN_H
#define E_CHESS_PAWN_H

#include "../../include/model/GameConstants.h"
#include "Piece.h"

using namespace std;

class Pawn : public Piece {

public:
    /**
     * This variable determines if the current pawn can do an "en passant"
     * move. It is eventually set by another pawn making its FIRST MOVE and
     * landing beside the current pawn
     */
    bool inPassing;

    /**
     * This variable tells wether the pawn is in the first move status
     * (initial status). If the pawn is in its first move status, it can
     * move two squares forward. Else, it can only move one square
     */
    boolean firstMove;

    /**
     * Default constructor for a pawn
     * @param aColor : PieceColor
     */
    Pawn(PieceColor aColor);

};


#endif //E_CHESS_PAWN_H
