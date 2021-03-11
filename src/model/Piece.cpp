//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Piece.h"
#include <iostream>
#include <vector>
#include "../../include/model/Chessboard.h"

using namespace std;

Piece::Piece() {
    this->color = EMPTY;
    this->type = NONE;
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

PieceColor Piece::GetColor() const{
    return this->color;
}

int Piece::GetType() const {
    return this->type;
}

const vector<int> & Piece::GetMoveDirections() const {
    return this->moveDirections;
}

bool Piece::DirectionIsLimited() {
    return this->directionIsLimited;
}

DestinationsSet Piece::GetPossibleMoves() {
    Chessboard * cb = Chessboard::GetInstance();
    DestinationsSet mvSet;
    int oneDimentionPosition = cb->GetPosition(this);
    PieceColor currentPieceColor = this->GetColor();
    const vector<int> directions = this->GetMoveDirections();
    bool directionIsLimited = this->DirectionIsLimited();
    int currentPiecePositionInBoundariesTable = cb->GetPositionInBoundariesTable(oneDimentionPosition);

    for (int direction : directions) {
        if ( ! directionIsLimited ) {       // If the direction of the piece is unlimited
            int nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
            int nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            while (nextDestinationValueInBoundariesTable != -1 &&
                   cb->getPiece(nextDestinationValueInBoundariesTable)->GetColor() == EMPTY
                    ) {
                cout << nextDestinationValueInBoundariesTable << endl;
                Coordinate destinationCoordinates = cb->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
                nextDestinationPositionInBoundariesTable += direction;
                nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            }
            if (nextDestinationValueInBoundariesTable != -1 && cb->getPiece(nextDestinationValueInBoundariesTable)->GetColor() != currentPieceColor) {
                Coordinate destinationCoordinates = cb->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
            }
        } else {
            int nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
            int nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            if (
                    nextDestinationValueInBoundariesTable != -1 &&
                    cb->getPiece(nextDestinationValueInBoundariesTable)->GetColor() != currentPieceColor
                    ) {
                Coordinate destinationCoordinates = cb->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
            }
        }

    }
    return mvSet;
}

void Piece::NotifyMove(Move mv) {}

Piece::~Piece() {

}