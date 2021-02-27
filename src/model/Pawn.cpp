//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Pawn.h"

#include <vector>

using namespace std;

Pawn::Pawn(PieceColor aColor)
    : Piece(aColor){

    int direction = (aColor == WHITE ? -1 : 1);
    this->moveDirections = {direction * 10, direction *20};
    this->directionIsLimited = true;

}


char Pawn::PieceToFEN() {
    return (this->GetColor() == WHITE ? 'p' : 'P');
}