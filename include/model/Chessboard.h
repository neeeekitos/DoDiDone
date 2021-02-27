//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_CHESSBOARD_H
#define E_CHESS_CHESSBOARD_H

#include <string>
#include "GameConstants.h"
#include "Piece.h"



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

private:

    int convertCoordinates(const Coordinate &coor) const ;

    Piece& getPiece (int position);

    Chessboard();

    static Chessboard * chessBoard_;

    int shot;
    int halfShot;
    /**
     * This determines which player is allowed to play
     * This is the same thing as a color of a piece
     * This variable cannot be = EMPTY
     */
    PieceColor currentPLayer;

    //Piece board[CHESSGAMESIZE];
    vector <Piece> board;

};

#endif //E_CHESS_CHESSBOARD_H
