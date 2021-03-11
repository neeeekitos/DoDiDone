//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_TOWER_H
#define E_CHESS_TOWER_H

#include "GameConstants.h"
#include "Piece.h"

class Tower : public Piece {

public:
    Tower(PieceColor aColor);

    virtual char PieceToFEN();

    virtual void NotifyMove (Move mv) override;

    bool IsFirstMoveDone ();

    /**
     * This variable is set to false as long as the tower has not moved
     */
    bool firstMoveDone;

private :

};


#endif //E_CHESS_TOWER_H
