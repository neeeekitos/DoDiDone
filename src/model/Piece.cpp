//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Piece.h"
#include <vector>

using namespace std;

Piece::Piece(PieceColor aColor): color(aColor) {}

Piece::Piece (Piece aColor, vector<int> aMoveDirections, bool aDirectionIsLimited):
        color(aColor), moveDirections(aMoveDirections), directionIsLimited(aDirectionIsLimited) {}

boolean Piece::isEmpty() {
    return (this->color == EMPTY);
}

char Piece::PieceToFEN() {
    return '';
}
