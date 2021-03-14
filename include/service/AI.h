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
#include "../controller/GameController.h"

using namespace std;

const int DEPTH_MINIMAX = 3;

const int PAWN_W = 10;
const int BISHOP_W = 30;
const int TOWER_W = 30;
const int KNIGHT_W = 50;
const int QUEEN_W = 90;
const int KING_W = 900;

class AI {
public:
    /**
     * Returns the singleton instance of the ai service
     * @return
     */
    static AI * GetInstance();

    /**
     * Make a move in the chessboard : using minimax algorithm or randomly
     * @param A Chessboard instance
     * @return The object of type Move
     */
    Move DoMove(Chessboard& chessboard);

    /**
     * Make a temporary move on the chessboard to be evaluted by minimax algorithm
     * @param mv a Move
     * @return The object Transition containing a move
     */
    static Transition CalculateMove(Move move);

    /**
     * Calculates a random move
     * @param A Chessboard instance
     * @return The object of type Move
     */
    Move RandomMove(Chessboard& chessboard);

    /**
     * Calculates a optimal move, the optimum criteria depending
     * on the chosen depth represented by the constant DEPTH_MINIMAX
     * @param list containing the path of the optimal calculated moves
     * @param the actual depth of the algorithm evaluation
     * @param maximizingPlayer is true, if it's a white piece, false otherwise
     * @return The object of type Move
     */
    int Minimax(list<Transition>& bestPath, int depth, bool maximizingPlayer);

    ~AI();
    AI(const AI&) = delete;
    void operator= (const AI&) = delete;

private:
    AI();

    /**
     * Gets a score depending on the current chessboard configuration
     * @param A Chessboard instance
     * @param A color of the current player
     * @return A score
     */
    int getScore(Chessboard& chessboard, PieceColor currentPlayer);

    /**
     * Gets a heuristic evaluation of the current chessboard configuration
     * @param A Chessboard instance
     * @param A color of the current player
     * @return A heuristic evaluation
     */
    int evaluate(Chessboard& chessboard, PieceColor currentPlayer);

    AIMode aiMode = MINIMAX;
    static AI * ai_;
};

#endif //E_CHESS_AI_H