#ifndef E_CHESS_PIECE_H
#define E_CHESS_PIECE_H

#include <string>
#include <vector>

#include "GameConstants.h"

/**
 * Represents a piece type
 */
enum PIECE_TYPE {
    PAWN,
    TOWER,
    KING,
    KNIGHT,
    QUEEN,
    BISHOP,
    NONE
};

/**
 * Represents the name of the pieces
 */
const string PIECE_NAME[7] = {
        "Pawn",
        "Tower",
        "King",
        "Knight",
        "Queen",
        "Bishop",
        "None"
};

using namespace std;

/**
 * Represents a generic piece
 */
class Piece {

public:

    /**
     * Constructs a piece
     */
    Piece();

    /**
     * Constructs a piece with the given color
     * @param aColor
     */
    Piece( Piece& piece);

    Piece(PieceColor aColor);

    /**
     * Tells if the occupied block by this piece is empty
     * @return
     */
    bool isEmpty();

    /**
     * Converts the current piece to its corresponding FEN char
     * @return The FEN char
     */
    virtual char PieceToFEN();

    /**
     * Returns the color of this piece
     * @return
     */
    PieceColor GetColor() const;

    /**
     * Returns the type of this piece
     * @return
     */
    int GetType() const;

    /**
     * Returns the move direction of this piece
     * @return
     */
    const vector <int> & GetMoveDirections() const ;

    /**
     * Tells wether the direction is limited or unlimited
     * @return
     */
    bool DirectionIsLimited();

    /**
     * Returns the possible moves of the current piece
     * @return The coordinates of the possible destinations
     */
    virtual DestinationsSet GetPossibleMoves ();

    /**
     * Notify the current piece that it did a move
     * @param mv The move
     */
    virtual void NotifyMove (Move mv);

    /**
     * The destructor of the move
     */
    virtual ~ Piece();

private :

    /**
     * This represents the color of the piece
     */
    PieceColor color = EMPTY;

protected:
    /**
     * The move directions of the current piece
     */
    vector <int> moveDirections;

    /**
     * If the directions are limited or unlimited
     */
    bool directionIsLimited;

    /**
     * The type of this piece
     */
    PIECE_TYPE type;

    /**
     * The constructor of the current piece
     * @param aColor The color of the piece
     * @param aMoveDirections The move directions
     * @param aDirectionIsLimited If the direction is limited
     */
    Piece(PieceColor aColor, vector<int> aMoveDirections, bool aDirectionIsLimited);


};


#endif //E_CHESS_PIECE_H
