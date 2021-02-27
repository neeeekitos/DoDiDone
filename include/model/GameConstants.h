//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_CONSTANTESDEPLACEMENT_H
#define E_CHESS_CONSTANTESDEPLACEMENT_H

#include <pair>
#include <vector>

typedef pair<int, int> Coordinate;

typedef pair <Coordinate, Coordinate> Move;

typedef vector<Move> MoveSet;

enum GameStatus {
    Check,
    Mate,
    CastlingPossible
};

class constantesDeplacement {

};


#endif //E_CHESS_CONSTANTESDEPLACEMENT_H
