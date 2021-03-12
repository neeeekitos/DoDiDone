//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_GAMECONTROLLER_H
#define E_CHESS_GAMECONTROLLER_H

#include <string.h>
#include "../model/Chessboard.h"
#include "../view/View.h"
#include "../model/GameConstants.h"

class GameController {

public:

    static GameController *GetInstance();

    GameController(const GameController &anotherGameController) = delete;

    void operator=(const GameController &aGameController) = delete;

    ~GameController();

    void Start();

    void SetGameMode(GameMode gm);

    GameMode GetGameMode();

    GameStatus GetGameStatus();

    void MakeMove(Move mv);


    DestinationsSet GetMoveablePieces(PieceColor);

    const std::vector<int> &GetSavedGamesIds(vector<int> &result) const;

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

    const std::vector<Piece *> &GetEatenPieces(PieceColor player);

    //choix 1 ou 2 joueurs, charger partie ou nouvelle partie, initialisation du plateau
    /* void NewGame();

     //toute la durée du jeu
     //lance la vue
     void Play();

     //chargement partie
     void LoadGame();

     //sauvegarde partie
     void SaveGame();





     void MoveValid();
     //retourne les cases où la pièce peut se déplacer
     void GetValidSpots();
     // Les mouvements seront définis par une chaine de caractères qui représente
     // la coordonnée de départ er la coordonnée d'arrivée ex: a1a2
     void MakeMove(string move);
     void SwitchPlayer();


     updateView();*/

private:

    GameController();

    GameMode gameMode;

    static GameController *gameController_;


};


#endif //E_CHESS_GAMECONTROLLER_H
