//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/controller/GameController.h"

int GameController::makeMove(int move) {
    chessBoard.makeMove(coordonnees);
    view.update(chessBoard);
}


int GameController::updateView() {
    view.update(chessBoard);
}

