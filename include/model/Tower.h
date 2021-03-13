#ifndef E_CHESS_TOWER_H
#define E_CHESS_TOWER_H

#include "GameConstants.h"
#include "Piece.h"

/**
 * This class represents a tower
 */
class Tower : public Piece {

public:

    /**
     * Constructor of a tower
     * @param aColor
     */
    Tower(PieceColor aColor);

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();

    /**
     * Allows to notify this tower that it moved
     * @param mv The move
     */
    virtual void NotifyMove (Move mv) override;

    /**
     * Tells wether the tower did its first move
     * @return
     */
    bool IsFirstMoveDone ();

    /**
     * This variable is set to false as long as the tower has not moved
     */
    bool firstMoveDone;

};


#endif //E_CHESS_TOWER_H
