#ifndef E_CHESS_KING_H
#define E_CHESS_KING_H

#include "Piece.h"
#include "Chessboard.h"
#include "GameConstants.h"

// Standard library
#include <vector>

using namespace std;

/**
 * This class represents a King
 */
class King : public Piece {
public:
    /**
     * A constructor of a king
     * @param color The color of the king
     */
    King(PieceColor color);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();

    /**
     * This is a service method that allows to notify the king that it
     * did a move
     * @param mv The move
     */
    virtual void NotifyMove (Move mv) override;

    /**
     * Tells wether this king already did its first move
     * @return
     */
    bool IsFirstMoveDone();

    /**
     * This variable is set to false as long as the king has not moved
     */
    bool firstMoveDone;

private:

    /**
     * The move list of a king. A move list is a relative translation
     * in the chess board
     */
    vector<int> movelists{-11, -10, -9, -1, 1, 9, 10, 11};

    /**
     * Represents the castle moves of this king
     */
    vector<int> casleMove{-2, 2};
};


#endif //E_CHESS_KING_H
