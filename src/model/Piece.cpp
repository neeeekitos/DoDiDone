//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Piece.h"

Piece::Piece(PieceColor aColor): color(aColor) {}

//Piece (Piece aColor, vector aMoveDirections, boolean aDirectionIsLimited):
  //  color(aColor), moveDirections(aMoveDirections), directionIsLimited(aDirectionIsLimited) {}

bool Piece::isEmpty() {
    return (this->color == EMPTY);
}

char Piece::PieceToFEN() {
    return ' ';
}
