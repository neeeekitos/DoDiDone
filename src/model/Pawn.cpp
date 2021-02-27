//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Pawn.h"

#include <vector>

using namespace std;

Pawn::Pawn(PieceColor aColor)
    : Piece(aColor){

    int direction = (aColor == WHITE ? -1 : 1);
    bool directionIsLimited = true;
    vector<int> directions {direction * 8, direction *16};

    //Piece(aColor, directions, directionIsLimited);

}
