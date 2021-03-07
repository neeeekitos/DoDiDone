//
// Created by Nikita TEREKHOV on 06/03/2021.
//
#include "../../include/service/AI.h"

using namespace std;

AI* AI::ai_ = nullptr;

AI * AI::GetInstance() {
    if (AI::ai_ == nullptr) {
        AI::ai_ = new AI;
    }
    return AI::ai_;
}

AI::AI() : aiMode(RANDOM) {}

void AI::DoMove(Chessboard& chessboard) {
    if (aiMode == RANDOM) RandomMove(chessboard);
    else if (aiMode == MINIMAX) {
        bool maxOrMinPlayer = chessboard.GetCurrentPlayer() == WHITE;
        Minimax(chessboard, DEPTH_MINIMAX, maxOrMinPlayer);
    }
}

Move AI::RandomMove(Chessboard& chessboard) {

    DestinationsSet movablePieces = chessboard.GetMovablePieces(chessboard.GetCurrentPlayer());

    // choose a random piece to move
    Coordinate initialPosition = movablePieces[rand() % movablePieces.size()];

    DestinationsSet possibleMoves = chessboard.GetPossibleMoves(initialPosition,false);

    Coordinate randomPosition = chessboard.ConvertOneDimensionPositionToCoordinate(
            rand() % possibleMoves.size());

    Move randomMove = make_pair(initialPosition, randomPosition);
    return randomMove;
}

/*
 * returns Heuristic evaluation
 */
int AI::evaluate(Chessboard& chessboard, PieceColor pieceColor) {

    // positive result if white piece is a current player, negative otherwise
    if (pieceColor == WHITE)
        return getScore(chessboard, WHITE) - getScore(chessboard, BLACK);
    else
        return getScore(chessboard, BLACK) - getScore(chessboard, WHITE);
}

int AI::getScore(Chessboard& chessboard, PieceColor pieceColor) {

    int weightCounter = 0;
    for (auto piece : chessboard.GetAllPieces(pieceColor)) {
        switch (piece.GetType()) {
            case PAWN: weightCounter += PAWN_W;
            case BISHOP: weightCounter += BISHOP_W;
            case TOWER: weightCounter += TOWER_W;
            case KNIGHT: weightCounter += KNIGHT_W;
            case QUEEN: weightCounter += QUEEN_W;
            case KING: weightCounter += KING_W;
        }
    }
    return weightCounter;
}

int AI::Minimax(Chessboard& chessboard, int depth, bool maximizingPlayer) {

    PieceColor pieceColor = chessboard.GetCurrentPlayer();
    if (depth == 0 || chessboard.GameOver(chessboard.GetCurrentPlayer())) {
        return evaluate(chessboard, pieceColor);
    }

    DestinationsSet movablePieces = chessboard.GetMovablePieces(pieceColor);

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto piece : movablePieces) {
            for (auto moveTo : chessboard.GetPossibleMoves(piece, false)) {
                // move piece in the chessboard
                Move possibleMove = make_pair(piece, moveTo);
                CalculateMove(chessboard, possibleMove);

                // evaluate current chessboard configuration
                int eval = Minimax(chessboard, depth - 1, false);
                maxEval = max(maxEval, eval);
                return maxEval;
            }
        }
    } else {
        int minEval = INT_MAX;
        for (auto piece : movablePieces) {
            for (auto moveTo : chessboard.GetPossibleMoves(piece, false)) {
                // move piece in the chessboard
                Move possibleMove = make_pair(piece, moveTo);
                CalculateMove(chessboard, possibleMove);

                // evaluate current chessboard configuration
                int eval = Minimax(chessboard, depth - 1, true);
                minEval = min(minEval, eval);
                return minEval;
            }
        }
    }
}

void AI::CalculateMove(Chessboard &chessboard, Move move) {
    chessboard.nextMoveIsPassingAuthorized = false;
    Piece * temp = chessboard.GetPiece(move.first);
    chessboard.SetPiece(move.first, chessboard.GetPiece(move.second));
    chessboard.SetPiece(move.second, temp);

    // ça met le first move à false
    temp->NotifyMove(move);
    if ( !chessboard.nextMoveIsPassingAuthorized ) {
        chessboard.inPassingAuthorised = nullptr;
    }
}

