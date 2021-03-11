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

GameController::GameController() {
    this->gameMode = UNDEFINED;
}

GameController::~GameController() {
    //delete (View::GetInstance());
    delete (Chessboard::GetInstance());
    //delete (gameController_);
    gameController_ = nullptr;
}

void GameController::Start() {
    View::GetInstance()->MenuChoices();
    Chessboard::GetInstance()->SetStatus(GameStatus::GoesOn);
    View::GetInstance()->MainLoop();
}

void GameController::SetGameMode(GameMode gm) {
    this->gameMode = gm;
}


GameMode GameController::GetGameMode() {
    return this->gameMode;
}

GameStatus GameController::GetGameStatus() {
    return Chessboard::GetInstance()->GetGameStatus();
}

void GameController::MakeMove(Move mv) {
    cout << "MAKE MOVE ";
    cout << mv.first.first << "-" << mv.first.second << " -> " << mv.second.first << "-" << mv.second.second << endl;
    Chessboard &c = *Chessboard::GetInstance();
    c.NotifyMove();
    c.nextMoveIsPassingAuthorized = false;
    if ( !c.GetPiece(mv.second)->isEmpty() ) {
        c.EatPiece(mv.second, c.GetPiece(mv.second)->GetColor());
        c.SetPiece(mv.second, new Piece());
    }
    Piece *temp = c.GetPiece(mv.second);
    c.SetPiece(mv.second, c.GetPiece(mv.first));
    c.SetPiece(mv.first, temp);
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

const std::vector<int> &GameController::GetSavedGamesIds(vector<int> &result) const {
    int number = 0;
    Chessboard * c = Chessboard::GetInstance();
    vector <string> savedGames = c->GetBackupFileInformations();
    result.clear();
    for (int i = 0; i < savedGames.size(); i++) {
        result.push_back(number++);
    }

    return result;
}

unsigned  int GameController::GetTurnCount() const {
    return 2;
}


int GameController::SaveGame() {
    Chessboard * c = Chessboard::GetInstance();
    return c->SaveGame();
}

void GameController::LoadGame(int gameId) {
    Chessboard * c = Chessboard::GetInstance();
    vector <string> vect = c->GetBackupFileInformations();
    if (gameId <= vect.size()) {
        c->Load(vect[gameId]);
    }
}

PieceColor GameController::GetCurrentPlayer() const {
    return Chessboard::GetInstance()->GetCurrentPlayer();
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

