//
// Created by Nikita TEREKHOV on 06/03/2021.
//

#ifndef E_CHESS_AI_H
#define E_CHESS_AI_H

#include "../model/GameConstants.h"
#include "../model/Chessboard.h"

const int DEPTH_MINIMAX = 3;

const int PAWN_W = 10;
const int BISHOP_W = 30;
const int TOWER_W = 30;
const int KNIGHT_W = 50;
const int QUEEN_W = 90;
const int KING_W = 900;

struct node
{
    Chessboard * chessboard;
    vector< node* > suc;
    node() {};
    node(Chessboard* cb) : chessboard(cb) {}
};

class AI {
public:
    static AI * GetInstance();
    void DoMove(Chessboard& chessboard);
    static void CalculateMove(Chessboard& chessboard, Move move);
    Move RandomMove(Chessboard& chessboard);
    int Minimax(Chessboard& board, int depth, bool maximizingPlayer);

    ~AI();
    AI(const AI&) = delete;
    void operator= (const AI&) = delete;

private:
    AI();
    int getScore(Chessboard& chessboard, PieceColor currentPlayer);
    int evaluate(Chessboard& chessboard, PieceColor currentPlayer);

    vector<Move> AIMovesPath;
    vector<Move> HumanMovesPath;
    AIMode aiMode;
    static AI * ai_;
};

#endif //E_CHESS_AI_H
