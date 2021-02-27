//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Tower.h"
#include <vector>

Tower::Tower(PieceColor aColor):
    Piece(
            aColor,
            vector<int> {-10, -1, 1, 10},
            false
            ){}



char Tower::PieceToFEN() {
    return (this->GetColor() == WHITE ? 't' : 'T');
}
