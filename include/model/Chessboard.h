//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_CHESSBOARD_H
#define E_CHESS_CHESSBOARD_H

#include "GameConstants.h"

class Chessboard {
public:
    Chessboard();
    //les spots du plateau où la pièce courante peut aller
    //validSpots;

    //la pièce courante sélectionnée
    //currentPiece;

public:
    MoveSet getPossibleMoved(Coordinate coor, boolean justEatableMoves);

};


#endif //E_CHESS_CHESSBOARD_H
