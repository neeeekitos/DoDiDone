//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Piece.h"
#include <vector>

using namespace std;

Piece::Piece() {
    this->color = EMPTY;
}

Piece::Piece(PieceColor aColor): color(aColor) {}

Piece::Piece(PieceColor aColor, vector<int> aMoveDirections, bool aDirectionIsLimited):
        color(aColor), moveDirections(aMoveDirections), directionIsLimited(aDirectionIsLimited) {}

bool Piece::isEmpty() {
    return (this->color == EMPTY);
}

char Piece::PieceToFEN() {
    return '-';
}

PieceColor Piece::GetColor() {
    return this->color;
}

const vector<int> & Piece::GetMoveDirections() const {
    return this->moveDirections;
}

bool Piece::DirectionIsLimited() {
    return this->directionIsLimited;
}