//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Pawn.h"
#include "../../include/model/Chessboard.h"
#include "../../include/controller/GameController.h"

#include <vector>
#include <iostream>

using namespace std;

Pawn::Pawn(PieceColor aColor)
    : Piece(aColor){

    int direction = (aColor == WHITE ? -1 : 1);
    this->moveDirections = {direction * 10, direction *20};
    this->eatingDirections = {direction * 9, direction * 11};
    this->directionIsLimited = true;
    this->firstMove = true;
    this->inPassing = false;
    this->type = PAWN;
}


char Pawn::PieceToFEN() {
    return (this->GetColor() == WHITE ? 'p' : 'P');
}

DestinationsSet Pawn::GetPossibleMoves() {
    Chessboard * cb = Chessboard::GetInstance();
    int position = cb->GetPosition(this);
    DestinationsSet mvSet;

    int currentPiecePositionInBoundariesTable = Chessboard::GetPositionInBoundariesTable(position);

    int nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + this->moveDirections[0];
    int nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);

    if (nextDestinationValueInBoundariesTable != -1 && cb->getPiece(nextDestinationValueInBoundariesTable)->isEmpty()) {
        Coordinate destinationCoordinates = Chessboard::ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
        mvSet.push_back(destinationCoordinates);
    }

    if (this->firstMove && !mvSet.empty()) {
        nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + this->moveDirections[1];
        nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
        if (nextDestinationValueInBoundariesTable != -1 && cb->getPiece(nextDestinationValueInBoundariesTable)->isEmpty()) {
            Coordinate destinationCoordinates = Chessboard::ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
            mvSet.push_back(destinationCoordinates);
        }
    }

    for (int direction : this->eatingDirections) {
        nextDestinationPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
        nextDestinationValueInBoundariesTable = cb->GetValueInBoundariesTable(nextDestinationPositionInBoundariesTable);
        if (nextDestinationValueInBoundariesTable == -1) continue;
        PieceColor targetPieceColor = cb->GetPiece(nextDestinationValueInBoundariesTable)->GetColor();
        if (targetPieceColor != EMPTY && targetPieceColor != this->GetColor()) {
            Coordinate destinationCoordinates = Chessboard::ConvertOneDimensionPositionToCoordinate(nextDestinationValueInBoundariesTable);
            mvSet.push_back(destinationCoordinates);
        }
    }

    if ( inPassing ) {
        mvSet.push_back(inPassingMove);
    }

//    if (this->GetColor() == BLACK && cb->GetGameStatus1().blackCheck || this->GetColor() == WHITE && cb->GetGameStatus1().whiteCheck) {
//        GameController * controller = GameController::GetInstance();
//        DestinationsSet filtered;
//        for (pair<int, int> destination : mvSet) {
//            cout << "move" << endl;
//            Coordinate currentPiecePosition = cb->ConvertOneDimensionPositionToCoordinate(position);
//            controller->MakeMove(make_pair(currentPiecePosition, destination));
//            cout << "out of makemove" << endl;
//            if (this->GetColor() == BLACK && !cb->GetGameStatus1().blackCheck || this->GetColor() == WHITE && !cb->GetGameStatus1().whiteCheck) {
//                filtered.push_back(destination);
//            }
//            Transition t;
//            t.mv = make_pair(currentPiecePosition, destination);
//        }
//        return filtered;
//    }

    return mvSet;

}

void Pawn::NotifyMove(Move mv) {
    int moveLength = mv.second.first - mv.first.first;
    moveLength = (moveLength < 0 ? - moveLength : moveLength);
    Chessboard * cb = Chessboard::GetInstance();
    if (this->firstMove && moveLength == 2) {
        int position = cb->GetPosition(this);
        int currentPiecePositionInBoundariesTable = Chessboard::GetPositionInBoundariesTable(position);
        vector <int> inPassingCheck = { -1 , 1};
        for (int direction : inPassingCheck) {
            int targetPositionInBoundariesTable = currentPiecePositionInBoundariesTable + direction;
            int valueInBoundariesTable = cb->GetValueInBoundariesTable(targetPositionInBoundariesTable);
            if (valueInBoundariesTable != -1) {
                Pawn * p = dynamic_cast<Pawn *> (cb->getPiece(valueInBoundariesTable));
                if (p != NULL && p->GetColor() != this->GetColor()) {
                    p->inPassingMove = make_pair((mv.first.first + mv.second.first) / 2, mv.first.second);
                    p->inPassingEatablePawn = mv.second;
                    p->inPassing = true;
                    cb->inPassingAuthorised = p;
                    cb->nextMoveInPassingAuthorized = true;
                }
            }
        }
    }
    if (cb->inPassingAuthorised == this && mv.second == this->inPassingMove) {
        cb->EatPiece(this->inPassingEatablePawn, this->GetColor());
    }

    this->firstMove = false;
    this->inPassing = false;
}