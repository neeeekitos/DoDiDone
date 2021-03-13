#ifndef E_CHESS_CHESSBOARD_H
#define E_CHESS_CHESSBOARD_H

#include <string>
#include "GameConstants.h"
#include "Piece.h"
#include "Pawn.h"

#define CHESSBOARDSIZE 64

struct Status{
    bool blackCheck;
    bool whiteCheck;
    bool mate;
    bool stalemate;
};

struct Transition {
    Move mv;
    bool eatenPiece;
    int positionOfEatenPiece;
    PieceColor eatenPieceColor;
};

class Chessboard {
public:

    //les spots du plateau où la pièce courante peut aller
    //validSpots;

    //la pièce courante sélectionnée
    //currentPiece;

    static Chessboard *GetInstance();

    Chessboard(const Chessboard &anotherChessBoard) = delete;

    void operator=(const Chessboard &aChessBoard) = delete;

    // string BoardToFen();

    DestinationsSet GetPossibleMoves(Coordinate coor, bool allPlayers);

    //void MakeMove(Move);

    static int GetPositionInBoundariesTable(int position);

    int GetValueInBoundariesTable(int position);

    void UpdateStatus();

    Status GetGameStatus1();

    static Coordinate ConvertOneDimensionPositionToCoordinate(int position);

    int convertCoordinates(const Coordinate &coor) const ;

    bool GameOver(PieceColor pieceColor);

    bool IsValidMove(Move mv);

    GameStatus GetGameStatus() const;

    void SetStatus(GameStatus s);

    Piece *GetPiece(Coordinate cor);

    void SetPiece(Coordinate &cor, Piece *piece);

    friend ostream &operator<<(ostream &out, Chessboard &cb);

    const Piece *const GetPiece(int position) const;

    DestinationsSet GetPossibleMoves( Coordinate coor);

    /**
     * Returns the position of the given piece in the board of pieces
     * @param p : a pointer to a given piece
     * @return : the 1-dimension position of the piece in the chessboard
     */
    int GetPosition(const Piece *p) const;


    Piece *getPiece(int position);

    void EatPiece(Coordinate coordinate, PieceColor pieceColor);

    void ChangePlayer();

    Pawn *inPassingAuthorised;

    bool nextMoveIsPassingAuthorized;

    PieceColor GetCurrentPlayer();

    int GetShots() const;

    DestinationsSet GetMovablePieces(PieceColor);

    DestinationsSet GetAllPieces (PieceColor color);

    string chessboardToFen();

    void NotifyMove();

    int SaveGame();

    bool FenCastlingIsPossible(PieceColor color, CastlingSide castlingSide);

    vector<string> GetBackupFileInformations();

    void Load(string fen);

    Piece *GeneratePiece(char fenChar);

    const std::vector<Piece *> &GetEatenPieces(PieceColor player) const;

    virtual ~Chessboard();

    /**
     * Tells wether the given move allows us to eat a piece
     * @param mv
     * @return
     */
    bool IsEatingMove(Move mv);

    void GetGameState ();

    void undoTransition(Transition& t);

    void UpdateCheckStatus();

    bool IsGameOver();

    WINNER GetWinner();



private:

    Chessboard();

    static Chessboard *chessBoard_;

    int shots;
    int halfShots;
    /**
     * This determines which player is allowed to play
     * This is the same thing as a color of a piece
     * This variable cannot be = EMPTY
     */
    PieceColor currentPlayer;

    //Piece board[CHESSGAMESIZE];
    vector<Piece *> board;

    vector<Piece *> eatenByBlack;
    vector<Piece *> eatenByWhite;

    bool castlingIsPossible(PieceColor color, CastlingSide castlingSide);

    static inline const string SAVING_PATH = "files/backup/";

    static inline const string SAVING_FILE = SAVING_PATH + "save.txt";

    GameStatus status;

    Status state;
};

#endif //E_CHESS_CHESSBOARD_H
