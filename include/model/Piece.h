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

    virtual string getImage() = 0;

    Piece(PieceColor aColor);

    boolean isEmpty();

    virtual char PieceToFEN();

private :
    /**
     * This represents the color of the piece
     */
    PieceColor color = EMPTY;

protected:
    vector <int> moveDirections;
    boolean directionIsLimited;

    Piece (Piece aColor, vector<int> aMoveDirections, bool aDirectionIsLimited);

};


#endif //E_CHESS_PIECE_H
