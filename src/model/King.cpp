//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/King.h"
#include "../../include/model/GameConstants.h"
#include <algorithm>

King::King(PieceColor aColor): Piece(aColor) {
    this->moveDirections = {-11, -10, -9, -1, 1, 9, 10, 11};
    this->directionIsLimited = true;
    this->type = PIECE_TYPE::KING;
    this->firstMoveDone = false;
}

char King::PieceToFEN() {
    if(this->GetColor()==BLACK)
    {
        return 'K';
    }
    else
    {
        return 'k';
    }

}

void King::NotifyMove(Move mv) {
    this->firstMoveDone = true;
}

bool King::IsFirstMoveDone() {
    return this->firstMoveDone;
}

/*



bool King::isValidMove(Chessboard board, int pos) {
    vector<int> validMoves = this->movements(board);
    return (find(validMoves.begin(),validMoves.end(),pos) != validMoves.end() );
}

vector<int> King::movements(Chessboard board) {

    int pos;
    int index = board.indexOf(this);
    vector<int> list ;
    int opponent =  board.getJoueurAdverse();
    vector<int> moveProhibited = board.eatableBy(opponent);

    for (int i = 0; i < this->movelists.size(); i++){
        pos = getCase120(getCase64(index) + this->movelists[i]);
        if (pos != -1 &&
        (find(moveProhibited.begin(),moveProhibited.end(),pos) == moveProhibited.end()) &&
        board.getCase(pos).getColor() != this->getColor()){
            list.push_back(pos);
        }
    }


    if (board.getGRoque1() || board.getGRoque2()){
        pos = getCase120(getCase64(index) + this->moveroques[0]);
        int pos1 = getCase120(getCase64(index) -3);
        int pos2 = getCase120(getCase64(index) - 1);
        if (pos != -1 && pos1 != -1 && pos2 != -1 && board.getCase(pos).isEmpty() &&
        board.getCase(pos1).isEmpty() && board.getCase(pos2).isEmpty() &&
        (find(moveProhibited.begin(),moveProhibited.end(),pos) == moveProhibited.end()) ){
            list.push_back(pos);
        }
    }
    if (board.getPRoque1() || board.getPRoque2()){
        pos = getCase120(getCase64(index) + this->moveroques[1]);
        int pos1 = getCase120(getCase64(index) + 1);
        if (pos != -1 && pos1 != -1 &&
        board.getCase(pos).isEmpty() &&
        board.getCase(pos1).isEmpty() &&
        (find(moveProhibited.begin(),moveProhibited.end(),pos) == moveProhibited.end()) ){
            list.push_back(pos);
        }
    }

    return list;
}

*/