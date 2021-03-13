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

int Chessboard::GetShots() const {
    return shots;
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

Status Chessboard::GetGameStatus() {

    return this->state;
}

void Chessboard::UpdateStatus() {
    this->UpdateCheckStatus();

    if (this->GetMovablePieces(this->currentPlayer).size() == 0) {
        this->state.stalemate = true;
        if ((this->currentPlayer == BLACK && this->state.blackCheck) || (this->currentPlayer == WHITE && this->state.whiteCheck)) {
            this->state.mate = true;
        }
    }

}

void Chessboard::UpdateCheckStatus() {

    this->state.whiteCheck = false;
    this->state.blackCheck = false;
    for (int i = 0; i < CHESSBOARDSIZE; ++i ) {
        Piece * p = this->getPiece(i);
        if ( !p->isEmpty() ) {
            Coordinate cor = ConvertOneDimensionPositionToCoordinate(i);
            DestinationsSet moves = this->GetPossibleMoves(cor);
            for (pair<int, int> dest : moves) {
                Piece * destPiece = this->GetPiece(dest);
                King * k = dynamic_cast <King *> (destPiece);
                if (k != nullptr) {
                    if (k->GetColor() == WHITE) {
                        this->state.whiteCheck = true;
                    } else {
                        this->state.blackCheck = true;
                    }
                }
            }
        }
    }

}

int Chessboard::GetValueInBoundariesTable(int position) {
    return boundaries[position];
}

Coordinate Chessboard::ConvertOneDimensionPositionToCoordinate(int position) {
    int x = position / 8;
    int y = position % 8;
    return make_pair(x, y);
}

DestinationsSet Chessboard::GetPossibleMoves(Coordinate coor, bool allPlayers) {
    //cout << "get possible moves" << endl;
    int oneDimentionPosition = convertCoordinates(coor);
    DestinationsSet dest;
    if (!allPlayers && this->getPiece(oneDimentionPosition)->GetColor() != this->currentPlayer) {
        return dest;
    }
    dest = this->getPiece(oneDimentionPosition)->GetPossibleMoves();
    King * k = dynamic_cast<King *> (this->getPiece(oneDimentionPosition));
    if ((this->GetGameStatus().whiteCheck && this->currentPlayer == WHITE) || (this->currentPlayer == WHITE && k != nullptr)) {
        DestinationsSet filtered;
        GameController * gc = GameController::GetInstance();
        for (pair<int, int> d : dest) {
            Transition t;
            Move mv = make_pair(coor, d);
            t.mv = mv;
            t.eatenPiece = false;
            Piece * p = gc->MakeMove(mv, false, true);
            if (p != nullptr) {
                t.eatenPiece = true;
                t.positionOfEatenPiece = this->convertCoordinates(d);
                t.eatenPieceColor = p->GetColor();
            }
            if ( !this->GetGameStatus().whiteCheck ) {
                filtered.push_back(d);
            }
            undoTransition(t);
            this->ChangePlayer();
            this->UpdateCheckStatus();
        }
        return filtered;
    }
    if ((this->GetGameStatus().blackCheck && this->currentPlayer == BLACK) || (this->currentPlayer == BLACK && k != nullptr)) {
        DestinationsSet filtered;
        GameController * gc = GameController::GetInstance();
        for (pair<int, int> d : dest) {
            Transition t;
            Move mv = make_pair(coor, d);
            t.mv = mv;
            t.eatenPiece = false;
            Piece * p = gc->MakeMove(mv, false, true);
            if (p != nullptr) {
                t.eatenPiece = true;
                t.positionOfEatenPiece = this->convertCoordinates(d);
                t.eatenPieceColor = p->GetColor();
            }
            if ( !this->GetGameStatus().blackCheck ) {
                filtered.push_back(d);
            }
            undoTransition(t);
            this->ChangePlayer();
            this->UpdateCheckStatus();
        }
        return filtered;
    }
    return dest;
}

bool Chessboard::IsGameOver() {
    return ((this->state.blackCheck || this->state.whiteCheck) && this->state.mate) || this->state.stalemate;
}

WINNER Chessboard::GetWinner() {
    if (this->IsGameOver() && this->state.whiteCheck) {
        return BLACKWINNER;
    }
    if (this->IsGameOver() && this->state.blackCheck) {
        return WHITEWINNER;
    }
    else {
        return EQUAL;
    }
}

void Chessboard::undoTransition(Transition & t) {
    int source = this->convertCoordinates(t.mv.second);
    int destination = this->convertCoordinates(t.mv.first);
    Piece * temp = this->board[destination];
    this->board[destination] = this->board[source];
    if (t.eatenPiece) {
        if (t.eatenPieceColor == WHITE) {
            Piece * eatenPiece = this->eatenByBlack[eatenByBlack.size() - 1];
            this->board[source] = eatenPiece;
            this->eatenByBlack.pop_back();
        } else {
            Piece * eatenPiece = this->eatenByWhite[eatenByWhite.size() - 1];
            this->board[source] = eatenPiece;
            this->eatenByWhite.pop_back();
        }
        delete temp;
    } else {
        this->board[source] = temp;
    }
}


DestinationsSet Chessboard::GetPossibleMoves(Coordinate coor) {
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
        eatenByWhite.push_back(this->GetPiece(coordinate));
    }
    if (pieceColor == WHITE) {
        eatenByBlack.push_back(this->GetPiece(coordinate));
    }
//    cout << "eatenByWhite : ";
//    for (Piece * p : eatenByWhite) {
//        cout << p->PieceToFEN() << " ";
//    }
//    cout << endl;
//    cout << "eatenByBlack : ";
//    for (Piece * p : eatenByBlack) {
//        cout << p->PieceToFEN() << " ";
//    }
//    cout << endl;
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

const std::vector<Piece *> &Chessboard::GetEatenPieces(PieceColor color) const {
    if (color == PieceColor::BLACK) {
        return eatenByWhite;
    } else {
        return eatenByBlack;
    }
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
    if (this->CastlingIsPossible(WHITE, KINGSIDE)) castlingString += "K";
    if (this->CastlingIsPossible(WHITE, QUEENSIDE)) castlingString += "Q";
    if (this->CastlingIsPossible(BLACK, KINGSIDE)) castlingString += "k";
    if (this->CastlingIsPossible(BLACK, QUEENSIDE)) castlingString += "q";
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

    if (GameController::GetInstance()->GetGameMode() == AIPLAYER) {
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

int Chessboard::SaveGame() {
    vector <string> savedFen = this->GetBackupFileInformations();
    if ( savedFen.size() >= 10 ) {
        savedFen.erase(savedFen.begin());
    }
    string line = this->chessboardToFen();
    savedFen.push_back( line );
    ofstream file (SAVING_FILE);
    if (file.is_open()) {
        for (string st : savedFen) {
            file << st << "\n";
        }
        file.close();
    }
    return savedFen.size();
}

bool Chessboard::CastlingIsPossible(PieceColor color, CastlingSide castlingSide) {
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
        file.close();
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
    else this->currentPlayer = BLACK;

    i+=2;
    if (fen[i] == 'K') {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 7);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = false;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = false;
        }
        ++i;
    } else {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 7);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = true;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = true;
        }
    }

    if (fen[i] == 'Q') {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 0);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = false;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = false;
        }
        ++i;
    } else {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 0);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = true;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = true;
        }
    }

    if (fen[i] == 'k') {
        Coordinate KingCoordinate = make_pair(0, 4);
        Coordinate towerCoordinate = make_pair(0, 7);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = false;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = false;
        }
        ++i;
    } else {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 0);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = true;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = true;
        }
    }

    if (fen[i] == 'q') {
        Coordinate KingCoordinate = make_pair(0, 4);
        Coordinate towerCoordinate = make_pair(0, 0);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = false;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = false;
        }
        ++i;
    } else {
        Coordinate KingCoordinate = make_pair(7, 4);
        Coordinate towerCoordinate = make_pair(7, 0);
        King * k = dynamic_cast <King *> (this->GetPiece(KingCoordinate));
        if (k != nullptr) {
            k->firstMoveDone = true;
        }
        Tower * t = dynamic_cast <Tower *> (this->GetPiece(towerCoordinate));
        if (t != nullptr) {
            t->firstMoveDone = true;
        }
    }

    ++i;

    if (fen[i] != '-') {
        string inPassingPosition = "";
        for (; fen[i] != ' '; ++i) {
            inPassingPosition += fen[i];
        }
        int position = stoi(inPassingPosition);
        Pawn * p = dynamic_cast <Pawn *> (this->GetPiece(ConvertOneDimensionPositionToCoordinate(position)));
        this->inPassingAuthorised = p;
    } else {
        ++i;
    }

    ++i;

    string halfShotsStr = "";
    for ( ; fen[i] != ' '; ++i) {
        halfShotsStr += fen[i];
    }
    this->halfShots = stoi(halfShotsStr);

    ++i;

    string shotsStr;
    for ( ; fen[i] != ' '; ++i) {
        shotsStr += fen[i];
    }
    this->shots = stoi(shotsStr);

    ++i;

    if (fen[i] == 'a') {
        GameController::GetInstance()->SetGameMode(AIPLAYER);
    } else {
        GameController::GetInstance()->SetGameMode(MULTIPLAYER);
    }

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
}

bool Chessboard::IsEatingMove(Move mv) {
    return (!this->GetPiece(mv.second)->isEmpty() &&
            this->GetPiece(mv.second)->GetColor() != this->GetPiece(mv.second)->GetColor());
}

DestinationsSet Chessboard::GetAllPieces(PieceColor color) {
    DestinationsSet allPieces;

    for (int i = 0; i < CHESSBOARDSIZE; ++i) {
        if (this->board[i]->GetColor() == color) {
            Coordinate cor = ConvertOneDimensionPositionToCoordinate(i);
            allPieces.push_back(cor);
        }
    }
    return allPieces;
}

bool Chessboard::GameOver(PieceColor pieceColor) {
    return false;
}

