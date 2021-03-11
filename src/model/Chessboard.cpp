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
#include "../../include/controller/GameController.h"

#include <iostream>
#include <fstream>

using namespace std;

Chessboard* Chessboard::chessBoard_ = nullptr;

Chessboard::Chessboard() {
    this->board = {
        new Tower(BLACK), new Knight(BLACK), new Bishop(BLACK),new Queen(BLACK), new King(BLACK), new Bishop(BLACK), new Knight(BLACK), new Tower(BLACK),
        new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK), new Pawn(BLACK),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(), new Piece(),
        new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE), new Pawn(WHITE),
        new Tower(WHITE), new Knight(WHITE), new Bishop(WHITE), new Queen(WHITE), new King(WHITE), new Bishop(WHITE), new Knight(WHITE), new Tower(WHITE)
    };

    this->halfShots = 0;
    this->shots = 1;
    this->currentPlayer = WHITE;
    this->inPassingAuthorised = nullptr;

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
    DestinationsSet dest;
    if (this->getPiece(oneDimentionPosition)->GetColor() != this->currentPlayer) {
        return dest;
    }
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


DestinationsSet Chessboard::GetMovablePieces(PieceColor color) {
    DestinationsSet movablePieces;
    for (int i = 0; i < CHESSBOARDSIZE; ++i) {
        if (this->board[i]->GetColor() == color) {
            Coordinate cor = ConvertOneDimensionPositionToCoordinate(i);
            if ( ! this->GetPossibleMoves(cor, false).empty() ) {
                movablePieces.push_back(cor);
            }
        }
    }
    return movablePieces;
}


string Chessboard::chessboardToFen() {
    string str;
    // Generate the FEN string
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char c = this->GetPiece(make_pair(i,j))->PieceToFEN();
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                str += c;
            } else {
                int counter = 0;
                for ( ; j < 8 ; j++) {
                    char c = this->GetPiece(make_pair(i,j))->PieceToFEN();
                    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                        --j;
                        break;
                    }
                    ++ counter;
                }
                str += to_string(counter);
            }
        }
        if (i != 7) str += '/';
    }

    // next player
    char currentPlayerCar = (this->currentPlayer == BLACK ? 'b' : 'w');
    str += " ";
    str += currentPlayerCar;

    string castlingString;
    if (this->FenCastlingIsPossible(WHITE, KINGSIDE)) castlingString += "K";
    if (this->FenCastlingIsPossible(WHITE, QUEENSIDE)) castlingString += "Q";
    if (this->FenCastlingIsPossible(BLACK, KINGSIDE)) castlingString += "k";
    if (this->FenCastlingIsPossible(BLACK, QUEENSIDE)) castlingString += "q";
    if (castlingString != "") {
        str += " " + castlingString;
    }

    if (this->inPassingAuthorised != nullptr) {
        int position = this->GetPosition(this->inPassingAuthorised);
        str += " " + to_string(position);
    } else {
        str += " -";
    }

    str += " " + to_string(this->halfShots) + " " + to_string(this->shots);

    if (GameController::GetInstance()->GetGameMode() == AI) {
        str += " a";
    } else {
        str += " m";
    }

    return str;
}

void Chessboard::NotifyMove() {
    ++this->halfShots;
    this->shots = this->halfShots / 2;
}

void Chessboard::SaveGame() {
    vector <string> savedFen = this->GetBackupFileInformations();
    if ( savedFen.size() >= 10 ) {
        savedFen.erase(savedFen.begin());
    }
    string line = this->chessboardToFen();
    savedFen.push_back( line );
    ofstream file (SAVING_FILE);
    cout << "trying to push" << endl;
    for (string st : savedFen) {
        cout << "pushing string line" << endl;
        file << st << "\n";
    }
    file.close();
}

bool Chessboard::castlingIsPossible(PieceColor color, CastlingSide castlingSide) {
    int kingInitialIndex = (color == BLACK ? 4 : 58);
    King * k = dynamic_cast<King *> (this->board[kingInitialIndex]);
    if (k == NULL || k->IsFirstMoveDone() ) return false;
    int towerRelativeIndex = (castlingSide == QUEENSIDE ? -4 : 3);
    Tower * t = dynamic_cast <Tower*> (this->board[kingInitialIndex + towerRelativeIndex]);
    if (t == NULL || t->IsFirstMoveDone() ) return false;
    int minIndex = (kingInitialIndex < kingInitialIndex + towerRelativeIndex ? kingInitialIndex : kingInitialIndex + towerRelativeIndex);
    int maxIndex = (kingInitialIndex < kingInitialIndex + towerRelativeIndex ? kingInitialIndex + towerRelativeIndex : kingInitialIndex);
    for (int i = minIndex; i <= maxIndex; ++i) {
        if ( ! this->board[i]->isEmpty() ) return false;
    }
    return true;
}

bool Chessboard::FenCastlingIsPossible(PieceColor color, CastlingSide castlingSide) {
    int kingInitialIndex = (color == BLACK ? 4 : 60);
    King * k = dynamic_cast<King *> (this->board[kingInitialIndex]);
    if (k == NULL || k->IsFirstMoveDone() ) return false;
    int towerRelativeIndex = (castlingSide == QUEENSIDE ? -4 : 3);
    Tower * t = dynamic_cast <Tower*> (this->board[kingInitialIndex + towerRelativeIndex]);
    if (t == NULL || t->IsFirstMoveDone() ) return false;
    return true;
}

vector<string> Chessboard::GetBackupFileInformations() {
    string line;
    vector <string> fenLines;
    ifstream file( SAVING_FILE );

    if ( file.is_open() ) {
        while ( getline(file, line) ) {
            fenLines.push_back(line);
        }
    }
    return fenLines;
}

Piece * Chessboard::GeneratePiece(char fenChar) {
    if ( !(fenChar >= 'A' && fenChar <= 'Z' || fenChar >= 'a' && fenChar <= 'z') || fenChar == ' ' ) return nullptr;
    PieceColor c;
    if (fenChar >= 'A' && fenChar <= 'Z') {
        c = WHITE;
    } else {
        c = BLACK;
    }

    if (fenChar == 'T' || fenChar == 't') return new Tower(c);
    if (fenChar == 'N' || fenChar == 'n') return new Knight(c);
    if (fenChar == 'B' || fenChar == 'b') return new Bishop(c);
    if (fenChar == 'Q' || fenChar == 'q') return new Queen(c);
    if (fenChar == 'K' || fenChar == 'k') return new King(c);
    if (fenChar == 'P' || fenChar == 'p') return new Pawn(c);

    return new Piece();
}


void Chessboard::Load(string fen) {
    int xPos = 7;
    int yPos = 0;
    int i = 0;

    while (fen[i] != ' ' && i < fen.length()) {
        yPos = 0;
        while ( fen[i] != '/' && fen[i] != ' ') {
            Coordinate c = make_pair(xPos, yPos);
            int position = convertCoordinates(c);
            if ( fen[i] >= 'A' && fen[i] <= 'Z' || fen[i] >= 'a' && fen[i] <= 'z' ) {
                delete this->board[position];
                this->board[position] = this->GeneratePiece(fen[i]);
                yPos ++;
            } else {
                int nbEmptyBlocks = fen[i] - '0';
                for (int j = 0; j < nbEmptyBlocks; ++j) {
                    c = make_pair(xPos, yPos);
                    position = convertCoordinates(c);
                    delete this->board[position];
                    this->board[position] = new Piece();
                    yPos ++;
                }
            }
            ++i;
        }
        --xPos;
        if (fen[i] == '/') {
            ++i;
        }
    }
    ++i;
    if (fen[i] == 'w') this->currentPlayer = WHITE;

}

Chessboard::~Chessboard() {
    for (int i = 0; i < this->board.size(); ++i) {
        delete this->board[i];
    }

    for (int i = 0; i < eatenByBlack.size(); ++i) {
        delete eatenByBlack[i];
    }

    for (int i = 0; i < eatenByWhite.size(); ++i) {
        delete eatenByWhite[i];
    }

    cout << "deleting chessboard finished" << endl;
}

