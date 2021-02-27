//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_CONSTANTESDEPLACEMENT_H
#define E_CHESS_CONSTANTESDEPLACEMENT_H

using namespace  std;
#include <vector>

typedef pair<int, int> Coordinate;

typedef pair <Coordinate, Coordinate> Move;

typedef vector<Move> MoveSet;

enum PieceColor {
    EMPTY,
    BLACK,
    WHITE
};

enum GameStatus {
    Check,
    Mate,
    CastlingPossible
};

class constantesDeplacement {

};


#endif //E_CHESS_CONSTANTESDEPLACEMENT_H
