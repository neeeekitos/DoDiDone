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

    static GameController * GetInstance();

    GameController(const GameController& anotherGameController) = delete;

    void operator= (const GameController & aGameController) = delete;

    ~GameController();

    void Start();

    void  SetGameMode (GameMode gm);

    GameMode GetGameMode ();

    void MakeMove(Move mv);
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
    View *view;
    Chessboard *chessBoard;
    GameMode gameMode;

    static GameController * gameController_;


};


#endif //E_CHESS_GAMECONTROLLER_H
