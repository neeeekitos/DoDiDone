//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/controller/GameController.h"

GameController::GameController(): view(View::GetInstance()), chessBoard(Chessboard::GetInstance()) {

}

GameController::~GameController() {
}

//int GameController::makeMove(int move) {
    // Making the move
   /* chessBoard.makeMove(coordonnees);
    view.update(chessBoard);

    // If we are in the player mode
    if (/) {
        this->SwitchPlayer();
    } else {    // If we are in the AI mode
        // mv = InstanceOfAI.GenerateMove( chessBoard )
        // chessBoard.makeMove(mv);
        // view.update();
    }
}


/*int GameController::updateView() {
    view.update(chessBoard);
}*/

