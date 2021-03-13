//
// Created by Nikita TEREKHOV on 06/03/2021.
//

#ifndef E_CHESS_AI_H
#define E_CHESS_AI_H

#include <map>
#include <list>
#include <iostream>


#include "../model/GameConstants.h"
#include "../model/Chessboard.h"

using namespace std;

const int DEPTH_MINIMAX = 2;

const int PAWN_W = 10;
const int BISHOP_W = 30;
const int TOWER_W = 30;
const int KNIGHT_W = 50;
const int QUEEN_W = 90;
const int KING_W = 900;

typedef struct node
{
    Move * move;
    map<int, Piece*> eatenPieces; // mapping eatenPiece and its position
    node() {};
} Node;

class AI {
public:
    static AI * GetInstance();
    Move DoMove(Chessboard& chessboard);
    static void CalculateMove(Chessboard& chessboard, Move move, Node& node, bool restoreEatedPiece);
    Move RandomMove(Chessboard& chessboard);
    int Minimax(list<Node>& path, list<Node>& bestPath, int depth, bool maximizingPlayer);

    ~AI();
    AI(const AI&) = delete;
    void operator= (const AI&) = delete;

private:
    AI();
    int getScore(Chessboard& chessboard, PieceColor currentPlayer);
    int evaluate(Chessboard& chessboard, PieceColor currentPlayer);

    vector<Move> AIMovesPath;
    vector<Move> HumanMovesPath;
    AIMode aiMode = MINIMAX;
    static AI * ai_;
};

#endif //E_CHESS_AI_H