//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Bishop.h"

// Edited by Rivaldo
#include <algorithm>

Bishop::Bishop(PieceColor aColor): Piece(aColor) {
    this->moveDirections = {-11, -9, 9, 11};
    this->directionIsLimited = false;
}

char Bishop::PieceToFEN() {
    if(this->GetColor()==BLACK)
    {
        return 'B';
    }
    else
    {
        return 'b';
    }
}

/*

char Bishop::PieceToFEN() {
    if(this->getColor()==BLACK)
    {
        return 'B';
    }
    else
    {
        return 'b';
    }
}

bool Bishop::isValidMove(Chessboard board, int pos) {
    vector<int> validMoves = this->movements(board);
    return (find(validMoves.begin(),validMoves.end(),pos) != validMoves.end() );
}

vector<int> Bishop::movements(Chessboard board) {

        vector<int> list;
        int pos;
        int index = board.indexOf(this);

        for (int i = 0; i < this->movelists.size(); i++){
            pos = getCase120(getCase64(index) + this->movelists[i]);
            for (int j = 2; pos != -1 && board.getCase(pos).isEmpty(); j++){
                list.push_back(pos);
                pos = getCase120(getCase64(index) + j * this->movelists[i]);
            }
            if (pos != -1 && board.getCase(pos).getColor() != this->getColor()){
                list.push_back(pos);
            }
        }
        return list;
}

vector<int> Bishop::eatableCase(Chessboard board) {
    vector<int> list;
    int index = board.indexOf(this);
    int pos;
    for (int i = 0; i < this->movelists.size(); i++){
        pos = getCase120(getCase64(index) + this->movelists[i]);
        for (int j = 0; pos != -1 && board.getCase(pos).isEmpty(); j++){
            list.push_back(pos);
            pos = getCase120(getCase64(index) + j * this->movelists[i]);
        }
        if (pos != -1 && board.getCase(pos).getColor() == this->getColor()){
            list.push_back(pos);
        }
    }
    return list;
}*/