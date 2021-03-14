//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_GAMECONTROLLER_H
#define E_CHESS_GAMECONTROLLER_H

#include <string.h>
#include "../service/AI.h"
#include "../model/Chessboard.h"
#include "../view/View.h"
#include "../model/GameConstants.h"

/**
 * Represents the controller of the game. This class is charged
 * to change the status of the chessboard
 */
class AI;
class GameController {

public:

    /**
     * Returns the singleton instance of the game
     * @return
     */
    static GameController *GetInstance();

    /**
     * The copy constructor. We must delete it as this class is a singleton
     * @param anotherGameController
     */
    GameController(const GameController &anotherGameController) = delete;

    /**
     * The affectation operator. In normal time, this operator calls the copy
     * constructor. Thus, we must delete it to prevent copying the singleton
     * instance
     * @param aGameController
     */
    void operator=(const GameController &aGameController) = delete;

    /**
     * A destructor of the GameController
     */
    ~GameController();

    /**
     * Starts the game
     */
    void Start();

    /**
     * Sets the game mode into one of the following:
     *      AI
     *      MULTIPLAYER
     * @param gm The game mode
     */
    void SetGameMode(GameMode gm);

    /**
     * Returns the curren game mode
     * @return
     */
    GameMode GetGameMode();

    /**
     * Make a move in the chessboard
     * Contract :
     *      mv is a valid move
     * @param mv A move
     * @return The eventually eaten piece while doing the move. Returns a pointer
     * to the eaten piece if a piece had been eaten, a null pointer otherwise
     */
    Piece * MakeMove(Move mv);

    /**
     * Pushes the IDs of the saved game parts to the result vector and returns it
     * @param result
     * @return The result vector after putting in it the game IDs
     */
    const std::vector<int> &GetSavedGamesIds(vector<int> &result) const;

    /**
     * Saved the game part
     * @return The number of saved game parts
     */
    int SaveGame();

    /**
     * @brief Load game number <gameId> into the chessboard
     * Set game mode
     * @param gameId
    */
    void LoadGame(int gameId);

    /**
     * @brief Get color of current player
     * @return
     */
    PieceColor GetCurrentPlayer() const;

    /**
     * @brief Get number of turns played
     * @return
     */
    int GetShots() const;

    /**
     * Returns the eaten pieces of the given color
     * @param color The color of the requested eaten pieces
     * @return A vector of eaten pieces
     */
    const std::vector<Piece *> & GetEatenPieces(PieceColor color);

    /**
     * This method makes a move in the chessboard
     * Contract :
     *      mv is a valid move
     * @param mv The move to perform
     * @param updateGeneralState Tells if we should update the general state (check,
     * mate, ...etc) by doing the move
     * @param temporaryMove Tells wether this move is a temporary move (It will be undone)
     * @return The eventually eaten piece by the move
     */
    Piece * MakeMove(Move mv, bool updateGeneralState, bool temporaryMove);

private:

    /**
     * The contructor of the game controller. Note that it is a private due to singleton
     * implementation
     */
    GameController();

    /**
     * Represents the game mode
     */
    GameMode gameMode;

    /**
     * The instance of the game controller
     */
    static GameController *gameController_;

};


#endif //E_CHESS_GAMECONTROLLER_H
