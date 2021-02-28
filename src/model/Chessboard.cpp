//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Chessboard.h"
#include "../../include/model/Piece.h"
#include "../../include/model/Pawn.h"
#include "../../include/model/Bishop.h"
#include "../../include/model/King.h"
#include "../../include/model/Knight.h"
#include "../../include/model/Queen.h"
#include "../../include/model/Tower.h"
#include "../../include/model/GameConstants.h"
#include <iostream>

using namespace std;

Chessboard* Chessboard::chessBoard_ = nullptr;

Chessboard::Chessboard() {
    this->board = {
        Tower(BLACK), Knight(BLACK), Bishop(BLACK),Queen(BLACK), King(BLACK), Bishop(BLACK), Knight(BLACK), Tower(BLACK),
        Pawn(BLACK), Pawn(BLACK), Pawn(BLACK), Pawn(BLACK), Pawn(BLACK), Pawn(BLACK), Pawn(BLACK), Pawn(BLACK),
        Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
        Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
        Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
        Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(),
        Pawn(WHITE), Pawn(WHITE), Pawn(WHITE), Pawn(WHITE), Pawn(WHITE), Pawn(WHITE), Pawn(WHITE), Pawn(WHITE),
        Tower(WHITE), Knight(WHITE), Bishop(WHITE), Queen(WHITE), King(WHITE), Bishop(WHITE), Knight(WHITE), Tower(WHITE)
    };

    this->currentPLayer = WHITE;

}

Chessboard * Chessboard::GetInstance() {
    if (Chessboard::chessBoard_ == nullptr) {
        Chessboard::chessBoard_ = new Chessboard();
    }
    return Chessboard::chessBoard_;
}

Piece & Chessboard::getPiece(int position) {
    return this->board[position];
}

int Chessboard::convertCoordinates(const Coordinate &coor) const {
    return coor.first * 8 + coor.second;
}

int Chessboard::GetPositionInBoundariesTable(int position) {
    return positionInBoundariesTable[position];
}

int Chessboard::GetValueInBoundariesTable(int position) {
    return boundaries[position];
}

Coordinate Chessboard::ConvertOneDimensionPositionToCoordinate(int position) {
    int x = position / 8;
    int y = position % 8;
    return make_pair(x, y);
}

DestinationsSet Chessboard::GetPossibleMoves(Coordinate coor, bool justEatableMoves) {
    DestinationsSet mvSet;
    int oneDimentionPosition = convertCoordinates(coor);
    Piece piece = this->getPiece(oneDimentionPosition);
    PieceColor currentPieceColor = piece.GetColor();
    const vector<int> directions = piece.GetMoveDirections();
    bool directionIsLimited = piece.DirectionIsLimited();
    int currentPiecePositionInBoundariesTable = this->GetPositionInBoundariesTable(oneDimentionPosition);

    for (int direction : directions) {
        if ( ! directionIsLimited ) {       // If the direction of the piece is unlimited
            int nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
            int nextDestinationValueInBoundariesTable = GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            while (nextDestinationValueInBoundariesTable != -1 &&
                   this->getPiece(nextDestinationValueInBoundariesTable).GetColor() == EMPTY
                    ) {
                cout << nextDestinationValueInBoundariesTable << endl;
                Coordinate destinationCoordinates = this->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
                nextDestinationPositionInBoundariesTable += direction;
                nextDestinationValueInBoundariesTable = GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            }
            if (nextDestinationValueInBoundariesTable != -1 && this->getPiece(nextDestinationValueInBoundariesTable).GetColor() != currentPieceColor) {
                Coordinate destinationCoordinates = this->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
            }
        } else {
            int nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
            int nextDestinationValueInBoundariesTable = GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
            if (
                    nextDestinationValueInBoundariesTable != -1 &&
                    this->getPiece(nextDestinationValueInBoundariesTable).GetColor() != currentPieceColor
                    ) {
                Coordinate destinationCoordinates = this->ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
                mvSet.push_back(destinationCoordinates);
            }
        }

    }
    return mvSet;
}
