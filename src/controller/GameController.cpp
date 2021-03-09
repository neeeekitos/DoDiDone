///home/lpietropao/etu/s2/GL/ChessXIV
// Created by lpietropao on 27/02/2021.
//

#include "../../include/controller/GameController.h"

GameController *GameController::gameController_ = nullptr;


GameController *GameController::GetInstance() {
    if (GameController::gameController_ == nullptr) {
        GameController::gameController_ = new GameController;
    }
    return GameController::gameController_;
}

GameController::GameController() : view(View::GetInstance()), chessBoard(Chessboard::GetInstance()) {

}

GameController::~GameController() {
    delete (View::GetInstance());
    delete (Chessboard::GetInstance());
    delete (gameController_);
}

void GameController::Start() {
    view->MenuChoices();
    view->MainLoop();
}

void GameController::SetGameMode(GameMode gm) {
    this->gameMode = gm;
}


GameMode GameController::GetGameMode() {
    return this->gameMode;
}

void GameController::MakeMove(Move mv) {
    Chessboard &c = *Chessboard::GetInstance();
    c.NotifyMove();
    c.nextMoveIsPassingAuthorized = false;
    Piece *temp = c.GetPiece(mv.first);
    c.SetPiece(mv.first, c.GetPiece(mv.second));
    c.SetPiece(mv.second, temp);
    temp->NotifyMove(mv);
    if (!c.nextMoveIsPassingAuthorized) {
        c.inPassingAuthorised = nullptr;
    }
    c.ChangePlayer();       // Change the current player turn
    if (this->gameMode == AI && c.GetCurrentPlayer() == BLACK) {    // If we are in AI mode and it's the AI turn to play
        // Generate a move
        // this->MakeMove(the generated move)
    }
}

const std::vector<int> &GameController::GetSavedGamesIds() const {}

void GameController::SaveGame() {}

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

