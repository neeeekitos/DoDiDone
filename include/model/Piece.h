//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_PIECE_H
#define E_CHESS_PIECE_H

#include <string>
#include <vector>

#include "GameConstants.h"

using namespace std;

class Piece {

public:

    //virtual string getImage();

    Piece();

    Piece(PieceColor aColor);

    bool isEmpty();

    virtual char PieceToFEN();

    PieceColor GetColor ();

    const vector <int> & GetMoveDirections() const ;

    bool DirectionIsLimited();

private :
    /**
     * This represents the color of the piece
     */
    PieceColor color = EMPTY;

protected:
    vector <int> moveDirections;
    bool directionIsLimited;
    Piece(PieceColor aColor, vector<int> aMoveDirections, bool aDirectionIsLimited);

};


#endif //E_CHESS_PIECE_H
