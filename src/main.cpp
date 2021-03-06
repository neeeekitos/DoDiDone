#include <iostream>
#include <unistd.h>
#include "../include/model/Chessboard.h"
#include "../include/view/View.h"
#include "../include/controller/GameController.h"
#include "../include/model/Bishop.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Chessboard & c = *(Chessboard::GetInstance());
    DestinationsSet dest = c.GetPossibleMoves(make_pair(1, 0), false);

    for (Coordinate mv : dest) {
        cout << mv.first << "\t" << mv.second << endl;
    }
    cout << "affichage du plateau" << endl;
    cout << c;


    GameController *gameControl = GameController::GetInstance();
    make_pair(make_pair(1,0), dest[0]);
    gameControl->MakeMove(make_pair(make_pair(6,3), make_pair(4, 3)));
    cout << "making another move" << endl;
    gameControl->MakeMove(make_pair(make_pair(4,2), make_pair(5, 3)));
    cout << c;
    gameControl->Start();

}