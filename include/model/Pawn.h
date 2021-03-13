#ifndef E_CHESS_PAWN_H
#define E_CHESS_PAWN_H

#include "../../include/model/GameConstants.h"
#include "Piece.h"

using namespace std;


/**
 * Represents a move
 */
class Pawn : public Piece {

public:
    /**
     * This variable determines if the current pawn can do an "en passant"
     * move. It is eventually set by another pawn making its FIRST MOVE and
     * landing beside the current pawn
     */
    bool inPassing;

    /**
     * This variable tells wether the pawn is in the first move status
     * (initial status). If the pawn is in its first move status, it can
     * move two squares forward. Else, it can only move one square
     */
    bool firstMove;

    /**
     * Default constructor for a pawn
     * @param aColor : PieceColor
     */
    Pawn(PieceColor aColor);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();

    /**
     * Returns the possible moves of the current pawn
     * @return
     */
    virtual DestinationsSet GetPossibleMoves ();

    /**
     * This is a service method that allows to notify the pawn that it
     * did a move
     * @param mv The move
     */
    virtual void NotifyMove (Move mv);


private:

    /**
     * represents the direction of the pawn
     */
    vector <int> eatingDirections;

    /**
     * if this pawn is allowed to do an in passing move, this is
     * the in passing destination
     */
    Coordinate inPassingMove;

    /**
     * If this pawn is allowed to do an in passing move, this is
     * the piece to it when doing the move
     */
    Coordinate inPassingEatablePawn;

};


#endif //E_CHESS_PAWN_H
