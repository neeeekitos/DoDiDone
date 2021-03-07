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
        new Tower(BLACK), new Knight(BLACK), new Bishop(BLACK),new Queen(BLACK), new King(BLACK), new Bishop(BLACK), new Knight(BLACK), new Tower(BLACK),
        new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Pawn(BLACK), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE),
        new Tower(WHITE), new Knight(WHITE), new Bishop(WHITE), new Queen(WHITE), new King(WHITE), new Bishop(WHITE), new Knight(WHITE), new Tower(WHITE)
    };

    this->currentPlayer = WHITE;

}

Chessboard * Chessboard::GetInstance() {
    if (Chessboard::chessBoard_ == nullptr) {
        Chessboard::chessBoard_ = new Chessboard();
    }
    return Chessboard::chessBoard_;
}

Piece * Chessboard::getPiece(int position) {
    return this->board[position];
}

const Piece * const Chessboard::GetPiece(int position) const {
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
    int oneDimentionPosition = convertCoordinates(coor);
    return this->getPiece(oneDimentionPosition)->GetPossibleMoves();
}

bool Chessboard::IsValidMove(Move mv) {
    int source = convertCoordinates(mv.first);
    int destination = convertCoordinates(mv.second);
    Piece * sourcePiece = this->getPiece(source);
    Piece * destinationPiece = this->getPiece(destination);
    PieceColor sourceColor = sourcePiece->GetColor();
    PieceColor destinationColor = destinationPiece->GetColor();
    return sourceColor != destinationColor;
}


Piece * Chessboard::GetPiece(Coordinate cor) {
    int position = convertCoordinates(cor);
    return this->getPiece(position);
}

void Chessboard::SetPiece(Coordinate &cor, Piece * piece) {
    int position = convertCoordinates(cor);
    this->board[position] = piece;
}

ostream & operator << (ostream & out, Chessboard & cb) {
    for (int i = 0; i < 8; i++) {
        for ( int j = 0; j < 8; ++j){
            Coordinate cor = make_pair(i, j);
            int position = cb.convertCoordinates(cor);
            Piece * p = cb.getPiece(position);
            out << p->PieceToFEN() << "\t";
        }
        out << endl;
    }
    out << endl;
    return out;
}

int Chessboard::GetPosition(const Piece *p) const {
    for (int i = 0; i < CHESSBOARDSIZE; ++i)  {
        if (this->board[i] == p) {
            return i;
        }
    }
    return -1;
}

void Chessboard::EatPiece(Coordinate coordinate, PieceColor pieceColor) {
    int position = this->convertCoordinates(coordinate);
    if (pieceColor == BLACK) {
        eatenByBlack.push_back(this->GetPiece(coordinate));
    }
    if (pieceColor == WHITE) {
        eatenByWhite.push_back(this->GetPiece(coordinate));
    }
    this->board[position] = new Piece();
}

void Chessboard::ChangePlayer() {
    this->currentPlayer = (this->currentPlayer == BLACK ? WHITE : BLACK);
}

PieceColor Chessboard::GetCurrentPlayer() {
    return this->currentPlayer;
}