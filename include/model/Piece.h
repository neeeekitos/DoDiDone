//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_PIECE_H
#define E_CHESS_PIECE_H

#include <string>
#include <vector>

#include "GameConstants.h"

enum PIECE_TYPE {
    PAWN,
    TOWER,
    KING,
    KNIGHT,
    QUEEN,
    BISHOP,
    NONE
};

const string PIECE_NAME[7] = {
        "Pawn",
        "Tower",
        "King",
        "Knight",
        "Queen",
        "Bishop",
        "None"
};

using namespace std;

class Piece {

public:

    //virtual string getImage();

    Piece();

    Piece(PieceColor aColor);

    bool isEmpty();

    virtual char PieceToFEN();

    PieceColor GetColor() const;

    int GetType() const;

    const vector <int> & GetMoveDirections() const ;

    bool DirectionIsLimited();

    virtual DestinationsSet GetPossibleMoves ();

    virtual void NotifyMove (Move mv);

private :
    /**
     * This represents the color of the piece
     */
    PieceColor color = EMPTY;

protected:
    vector <int> moveDirections;
    bool directionIsLimited;
    int type;

    Piece(PieceColor aColor, vector<int> aMoveDirections, bool aDirectionIsLimited);


};


#endif //E_CHESS_PIECE_H
