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

Move AI::DoMove(Chessboard& chessboard) {
    aiMode = MINIMAX;
    Move move;
    if (aiMode == RANDOM) move = RandomMove(chessboard);
    else if (aiMode == MINIMAX) {
        cout << "generating move " << endl;
        bool maxOrMinPlayer = chessboard.GetCurrentPlayer() == WHITE;
        cout << "player is maximiwing (white)" << maxOrMinPlayer << endl;
        list<Node> bestPath;
        list<Node> path;
        Minimax(path, bestPath, DEPTH_MINIMAX, maxOrMinPlayer);
        auto lastElementIt = bestPath.end();
        --lastElementIt;
        move = *(lastElementIt->move);
    }
    return move;
}

Move AI::RandomMove(Chessboard& chessboard) {

    DestinationsSet movablePieces = chessboard.GetMovablePieces(chessboard.GetCurrentPlayer());

    // choose a random piece to move
    Coordinate initialPosition = movablePieces[rand() % movablePieces.size()];

    DestinationsSet possibleMoves = chessboard.GetPossibleMoves(initialPosition,false);

    int index = rand() % possibleMoves.size();
    Coordinate randomPosition = possibleMoves[index];

    Move randomMove = make_pair(initialPosition, randomPosition);
    return randomMove;
}

/*
 * returns Heuristic evaluation
 */
int AI::evaluate(Chessboard& chessboard, PieceColor pieceColor) {

    // positive result if white piece is a current player, negative otherwise
    return getScore(chessboard, WHITE) - getScore(chessboard, BLACK);

    /* if (pieceColor == WHITE)
         return getScore(chessboard, WHITE) - getScore(chessboard, BLACK);
     else
         return getScore(chessboard, BLACK) - getScore(chessboard, WHITE);*/

}

int AI::getScore(Chessboard& chessboard, PieceColor pieceColor) {

    int weightCounter = 0;
    for (auto pieceCoordinate : chessboard.GetAllPieces(pieceColor)) {
        switch (chessboard.getPiece(chessboard.convertCoordinates(pieceCoordinate))->GetType()) {
            case PAWN: weightCounter += PAWN_W; break;
            case BISHOP: weightCounter += BISHOP_W; break;
            case TOWER: weightCounter += TOWER_W; break;
            case KNIGHT: weightCounter += KNIGHT_W; break;
            case QUEEN: weightCounter += QUEEN_W; break;
            case KING: weightCounter += KING_W; break;
        }
    }
    return weightCounter;
}

int AI::Minimax(list<Node>& path, list<Node>& bestPath, int depth, bool maximizingPlayer) {

    Chessboard * board = Chessboard::GetInstance();

    PieceColor pieceColor = maximizingPlayer ? WHITE : BLACK;

    if (depth == 0 || board->GameOver(pieceColor)) {
        int eval = evaluate(*board, pieceColor);
        return eval;
    }

    DestinationsSet movablePieces = board->GetMovablePieces(pieceColor);

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        Move bestMove;
        for (auto piece : movablePieces) {
            for (auto moveTo : board->GetPossibleMoves(piece, false)) {
                Node node;

                // move piece in the chessboard and remember eated pieces (in some cases)
                Move possibleMove = make_pair(piece, moveTo);
                node.move = &possibleMove;
                if (!board->GetPiece(possibleMove.second)->isEmpty()) {
//                    cout <<" is eating move, I remember it" << endl;
                    node.eatenPieces.insert(make_pair(board->convertCoordinates(possibleMove.second), board->GetPiece(possibleMove.second)));
                }
                path.push_back(node);
//                cout << "white piece moves " << endl;
                CalculateMove(*board, possibleMove, node, false);

                // evaluate current chessboard configuration
                board->ChangePlayer();
                int eval = Minimax(bestPath, path, depth - 1, false);
                cout << "color " << pieceColor << ", depth : "<< depth << " , eval " << eval << " with possible move is from x=" << possibleMove.first.first << ", y=" << possibleMove.first.second
                     << " to x=" << possibleMove.second.first << ", y=" << possibleMove.second.second << endl;

                maxEval = max(maxEval, eval);
                if (maxEval == eval) bestMove = possibleMove;

                // undo move
                path.pop_back();
//                cout << "undoing move" << endl;

                CalculateMove(*board, make_pair(possibleMove.second, possibleMove.first), node, true);

            }
        }

        Node node;
        node.move = &bestMove;
        bestPath.push_back(node);

        return maxEval;
    } else {
        int minEval = INT_MAX;
        Move bestMove;
        for (auto piece : movablePieces) {
            for (auto moveTo : board->GetPossibleMoves(piece, false)) {

                Node node;

                // move piece in the chessboard and remember eated piece (in some cases)
                Move possibleMove = make_pair(piece, moveTo);
                node.move = &possibleMove;
                if (!board->GetPiece(possibleMove.second)->isEmpty()) {
//                    cout <<" is eating move, i remember it" << endl;

                    node.eatenPieces.insert(make_pair(board->convertCoordinates(possibleMove.second), board->GetPiece(possibleMove.second)));
                }
                path.push_back(node);
//                cout << "black piece moves " << endl;
                CalculateMove(*board, possibleMove, node, false);

                // evaluate current chessboard configuration
                board->ChangePlayer();
                int eval = Minimax(bestPath, path, depth - 1, true);
                cout << "color " << pieceColor << ", depth : "<< depth << " , eval " << eval << " with possible move is from x=" << possibleMove.first.first << ", y=" << possibleMove.first.second
                     << " to x=" << possibleMove.second.first << ", y=" << possibleMove.second.second << endl;

                /*if (possibleMove.first.first == 0 && possibleMove.first.second == 1
                    && possibleMove.second.first == 0 && possibleMove.second.second == 0) exit(-1);*/

                // undo move
                path.pop_back();
                cout << "undoing move" << endl;
                CalculateMove(*board, make_pair(possibleMove.second, possibleMove.first), node, true);

                minEval = min(minEval, eval);
                if (minEval == eval) bestMove = possibleMove;
            }
        }
        Node node;
        node.move = &bestMove;
        bestPath.push_back(node);

        return minEval;
    }
}

void AI::CalculateMove(Chessboard &chessboard, Move move, Node& node, bool restoreEatedPiece) {


    Chessboard &c = *Chessboard::GetInstance();
    c.NotifyMove();
    c.nextMoveIsPassingAuthorized = false;

    // check if it is an eating move
    if ( !c.GetPiece(move.second)->isEmpty() ) {
        c.EatPiece(move.second, c.GetPiece(move.second)->GetColor());
        c.SetPiece(move.second, new Piece());
    }
    Piece *temp = c.GetPiece(move.second);
    c.SetPiece(move.second, c.GetPiece(move.first));
    c.SetPiece(move.first, temp);

    if (!c.nextMoveIsPassingAuthorized) {
        c.inPassingAuthorised = nullptr;
    }

    // check if the piece was eaten
    auto it = node.eatenPieces.find(chessboard.convertCoordinates(move.first));
    if (it != node.eatenPieces.end()) {
//        cout << "-->>>> restoring eated pieces <<<<--" << endl;
        Coordinate cor = Chessboard::ConvertOneDimensionPositionToCoordinate(it->first);
        chessboard.SetPiece(cor, it->second);
    }
}
