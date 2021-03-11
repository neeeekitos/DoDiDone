#include <iostream>
#include <unistd.h>
#include "../include/model/Chessboard.h"
#include "../include/view/View.h"
#include "../include/controller/GameController.h"
#include "../include/model/Bishop.h"

using namespace std;

int main() {

    Chessboard & c = *(Chessboard::GetInstance());
    GameController & gm = *(GameController::GetInstance());
    DestinationsSet dest = c.GetPossibleMoves(make_pair(1, 0), false);

    for (Coordinate mv : dest) {
       cout << mv.first << "\t" << mv.second << endl;
    }
   cout << "affichage du plateau" << endl;
    cout << c;

    cout << c.chessboardToFen() << endl;

    Move mv = make_pair(make_pair(6, 7), make_pair(4, 7));
    gm.MakeMove(mv);
    mv = make_pair(make_pair(1, 0), make_pair(3, 0));
    gm.MakeMove(mv);

    //GameController *gameControl = GameController::GetInstance();
    //gameControl->MakeMove(mv);
    gm.Start();

    //delete GameController::GetInstance();
    delete GameController::GetInstance();

    return 0;

}