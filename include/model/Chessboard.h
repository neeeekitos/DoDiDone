//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_CHESSBOARD_H
#define E_CHESS_CHESSBOARD_H

#include <string>
#include "GameConstants.h"
#include "Piece.h"
#include "Pawn.h"

#define CHESSBOARDSIZE 64

class Chessboard {
public:

    //les spots du plateau où la pièce courante peut aller
    //validSpots;

    //la pièce courante sélectionnée
    //currentPiece;

    static Chessboard * GetInstance();

    Chessboard(const Chessboard& anotherChessBoard) = delete;

    void operator= (const Chessboard & aChessBoard) = delete;

    // string BoardToFen();

    DestinationsSet GetPossibleMoves(Coordinate coor, bool justEatableMoves);

    //void MakeMove(Move);

    static int GetPositionInBoundariesTable(int position);

    int GetValueInBoundariesTable(int position);

    static Coordinate ConvertOneDimensionPositionToCoordinate(int position);

    bool IsValidMove(Move mv);

    Piece * GetPiece(Coordinate cor);

    void SetPiece(Coordinate& cor, Piece * piece);

    friend ostream & operator << (ostream & out, Chessboard & cb);

    const Piece* const GetPiece (int position) const;

    /**
     * Returns the position of the given piece in the board of pieces
     * @param p : a pointer to a given piece
     * @return : the 1-dimension position of the piece in the chessboard
     */
    int GetPosition(const Piece * p) const;


    Piece * getPiece (int position);

    void EatPiece (Coordinate coordinate, PieceColor pieceColor);

    void ChangePlayer();

    Pawn * inPassingAuthorised;

    bool nextMoveIsPassingAuthorized;

    PieceColor GetCurrentPlayer();

    DestinationsSet GetMovablePieces (PieceColor);

    string chessboardToFen();

    void NotifyMove();

    void SaveGame();

    bool FenCastlingIsPossible(PieceColor color, CastlingSide castlingSide);

    vector<string> GetBackupFileInformations();

    void Load(string fen);

    Piece * GeneratePiece (char fenChar);

    virtual ~Chessboard();

private:

    int convertCoordinates(const Coordinate &coor) const ;

    Chessboard();

    static Chessboard * chessBoard_;

    int shots;
    int halfShots;
    /**
     * This determines which player is allowed to play
     * This is the same thing as a color of a piece
     * This variable cannot be = EMPTY
     */
    PieceColor currentPlayer;

    //Piece board[CHESSGAMESIZE];
    vector <Piece*> board;

    vector <Piece*> eatenByBlack;
    vector <Piece*> eatenByWhite;

    bool castlingIsPossible(PieceColor color, CastlingSide castlingSide);

    static inline const string SAVING_PATH = "files/backup/";

    static inline const string SAVING_FILE = SAVING_PATH + "save.txt";

};

#endif //E_CHESS_CHESSBOARD_H
