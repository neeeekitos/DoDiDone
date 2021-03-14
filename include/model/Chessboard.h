#ifndef E_CHESS_CHESSBOARD_H
#define E_CHESS_CHESSBOARD_H

#include <string>
#include "GameConstants.h"
#include "Piece.h"
#include "Pawn.h"

#define CHESSBOARDSIZE 64


/**
 * Represents the status of the chess game
 */
struct Status{
    bool blackCheck;
    bool whiteCheck;
    bool mate;
    bool stalemate;
};


/**
 * Represents a transition :
 *      A move
 *      A boolean telling us if we ate a piece by doing the move
 *      The position of the eventually eaten piece by doing that move
 *      The color of the eventually eaten piece
 */
struct Transition {
    Move mv;
    bool eatenPiece;
    int positionOfEatenPiece;
    PieceColor eatenPieceColor;
    bool operator==(const Transition& tr) const{

        return (this->mv.first.first == tr.mv.first.first
            && this->mv.first.second == tr.mv.first.second
            && this->mv.second.first == tr.mv.second.first
            && this->mv.second.second == tr.mv.second.second);
    }
};

/**
 * This class represents the chessboard. It is implemented as a singleton
 * in the while program
 */
class Chessboard {
public:

    /**
     * This returns the singleton instance
     * @return a pointer to the singleton instance
     */
    static Chessboard *GetInstance();

    /**
     * This is the copy constructor of the chessboard. As we implemented
     * this class as a singleton, we delete this method to prevent copying
     * the instance
     * @param anotherChessBoard
     */
    Chessboard(const Chessboard &anotherChessBoard) = delete;

    /**
     * This is the affectation operator. In normal time, it calls the copy
     * constructor. Thus, we delete this operator to prevent copying the instance
     * @param aChessBoard
     */
    void operator=(const Chessboard &aChessBoard) = delete;

    /**
     * This methods gets the possible moves of the piece situated in the
     * corresponding given coordinate
     * @param coor The coordinates of the piece
     * @param allPlayers This variable tells if we should return the possible
     * moves only if the current player is the same as the piece color, or
     * in all cases
     * @return The possible moves (as destination set)
     */
    DestinationsSet GetPossibleMoves(Coordinate coor, bool allPlayers);

    /**
     * This method takes a position of a piece in parameter. It returns its
     * corresponding index in the boundaries table (defined in GameConstants)
     * @param position The given position
     * @return The The position in boundaries table
     */
    static int GetPositionInBoundariesTable(int position);

    /**
     * This method takes a position of a piece in parameter. It returns its
     * corresponding "value" in boundaries table
     * @param position The given position
     * @return
     */
    int GetValueInBoundariesTable(int position);

    /**
     * This method updates the status of the game (Check, mate, stalemate... etc)
     */
    void UpdateStatus();

    /**
     * This method returns the current status of the game
     * @return A struct representing the flags of status of the game
     */
    Status GetGameStatus();

    /**
     * This method converts a one dimension position to 2 dimensions
     * coordinates
     * @param position The given position
     * @return The result coordinate
     */
    static Coordinate ConvertOneDimensionPositionToCoordinate(int position);

    /**
     * Tells wether the given move is a valid move
     * Contract :
     *      The coordinates of the move must be a valid coordinates
     * @param mv
     * @return
     */
    bool IsValidMove(Move mv);

    /**
     * This method returns the piece situated on the given coordinates in the
     * chess board
     * Contract :
     *      The given coordinates must be valid
     * @param cor The given coordinates
     * @return A pointer to the piece
     */
    Piece *GetPiece(Coordinate cor);

    /**
     * This method replaced the piece situated in the given coordinates by
     * the given piece. It also frees the variable previously being in the
     * given position.
     * @param cor The given coordinates
     * @param piece The given piece
     */
    void SetPiece(Coordinate &cor, Piece *piece);

    /**
     * Displays the chess board in console
     * @param out
     * @param cb
     * @return
     */
    friend ostream &operator<<(ostream &out, Chessboard &cb);

    /**
     * This method returns a const pointer to the piece situated in
     * the given one dimension position
     * @param position
     * @return A const pointer to the piece
     */
    const Piece *const GetPiece(int position) const;

    /**
     * Returns the possible moves of the piece situated on the given
     * 2 dimensions coordinates
     * @param coor The given coordinates
     * @return A destinations set representing the possible destinations
     */
    DestinationsSet GetPossibleMoves( Coordinate coor);

    /**
     * Returns the position of the given piece in the board of pieces
     * @param p : a pointer to a given piece
     * @return : the 1-dimension position of the piece in the chessboard
     */
    int GetPosition(const Piece *p) const;

    /**
     * Returns a pointer to the piece situated on the given one dimension
     * position
     * @param position The given position
     * @return A pointer to the piece
     */
    Piece *getPiece(int position);

    /**
     * This method simulates eating a piece situated in the given coordinates
     * on the chessboard. It pushes the eated piece to the corresponding vector
     * eatenByBlack/eatenByWhite depending on the give pieceColor parameter
     * @param coordinate The coordinates of the piece to eat
     * @param pieceColor The color of the piece to eat
     */
    void EatPiece(Coordinate coordinate, PieceColor pieceColor);

    /**
     * This method changes the current player
     */
    void ChangePlayer();

    /**
     * Returns the current player
     * @return
     */
    PieceColor GetCurrentPlayer();

    /**
     * Returns all the movable pieces of the given color
     * @param color The color of movable pieces to return
     * @return A set of coordinates of the movable pieces
     */
    DestinationsSet GetMovablePieces(PieceColor color);

    /**
     * Returns the number of shots in the game
     * @return
     */
    int GetShots() const;

    /**
     * Transoforms the current chessboard to its corresponding
     * FEN representation
     * @return string representing the FEN format of the current
     * configuration of the chessboard
     */
    string chessboardToFen();

    /**
     * Notifies the chess board that a move has been done
     */
    void NotifyMove();

    /**
     * Saved the game into a backup file.
     * @return The number of saved games
     */
    int SaveGame();

    /**
     * This method tells wether the castling of the king of the given color
     * in the given side is possible
     * @param color The king color
     * @param castlingSide The castling side to check
     * @return
     */
    bool CastlingIsPossible(PieceColor color, CastlingSide castlingSide);

    /**
     * Returns vector in FEN format of all the saved games
     * @return
     */
    vector<string> GetBackupFileInformations();

    /**
     * Loads the game using the given FEN string
     * @param fen
     */
    void Load(string fen);

    /**
     * It generates a piece that corresponds to the given FEN char
     * @param fenChar
     * @return
     */
    Piece *GeneratePiece(char fenChar);

    /**
     * Returns pieces eaten by the given player
     * @param player
     * @return
     */
    const std::vector<Piece *> &GetEatenPieces(PieceColor player) const;

    /**
     * Returns all the pieces of the chessboard
     * @param color The color of the pieces
     * @return
     */
    DestinationsSet GetAllPieces (PieceColor color);

    /**
     * Tells if the game is over
     * @param pieceColor
     * @return
     */
    bool GameOver(PieceColor pieceColor);

    /**
     * Destructor of a chessboard
     */
    virtual ~Chessboard();

    /**
     * Tells wether the given move allows us to eat a piece
     * @param mv
     * @return
     */
    bool IsEatingMove(Move mv);

    /**
     * Undo a given transition. A transition is a struct made of
     * a move, a position of the eventually eaten piece when doing the
     * move, and the eaten piece color
     * @param t The given transition
     */
    void undoTransition(Transition& t);

    /**
     * Updates the "check" status of the current game
     */
    void UpdateCheckStatus();

    /**
     * Tells wether the game is over or not
     * @return
     */
    bool IsGameOver();

    /**
     * Returns the winner of the game.
     * This result of this method is only valid if the game is over
     * @return
     */
    WINNER GetWinner();

    /**
     * Represents an "in passing authorised" pawn if there is one
     */
    Pawn *inPassingAuthorised;

    /**
     * Tells wether the next move allows in passing move to the
     * pawn stored in inPassingAuthorised
     */
    bool nextMoveInPassingAuthorized;

    /**
     * Converts 2 dimensions coordinates to a one dimension position in the
     * chess board
     * @param coor The given coordinates
     * @returno The corresponding position
     */
    int convertCoordinates(const Coordinate &coor) const;

private:

    /**
     * The constructor of the chessboard. Note that it is in private as the
     * class is singleton
     */
    Chessboard();

    /**
     * The singleton attribute
     */
    static Chessboard *chessBoard_;

    /**
     * Number of shots
     */
    int shots;

    /**
     * Number of halfShots
     */
    int halfShots;

    /**
     * This determines which player is allowed to play
     * This is the same thing as a color of a piece
     * This variable cannot be = EMPTY
     */
    PieceColor currentPlayer;

    /**
     * Represents the chess board and contains the pieces
     */
    vector<Piece *> board;

    /**
     * The eaten by black pieces
     */
    vector<Piece *> eatenByBlack;

    /**
     * The eaten by white pieces
     */
    vector<Piece *> eatenByWhite;

    /**
     * The path to save game parts in
     */
    static inline const string SAVING_PATH = "files/backup/";

    /**
     * The file to save game parts in
     */
    static inline const string SAVING_FILE = SAVING_PATH + "save.txt";

    /**
     * Represents actual state of the game
     */
    Status state;
};

#endif //E_CHESS_CHESSBOARD_H
