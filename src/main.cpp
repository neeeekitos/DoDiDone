#include <iostream>
#include <unistd.h>
#include "../include/model/Chessboard.h"
#include "../include/view/View.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Chessboard & c = *(Chessboard::GetInstance());
    DestinationsSet dest = c.GetPossibleMoves(make_pair(6,0), false);
    for (Coordinate mv : dest) {
        cout << mv.first << "\t" << mv.second << endl;
    }
    GameController gameControl;
//    v.MenuChoices();


}