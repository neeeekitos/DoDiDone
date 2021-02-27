//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/model/Queen.h"
#include "../../include/model/GameConstants.h"
#include "../../include/model/Piece.h"

#include <vector>

using namespace std;



Queen::Queen(PieceColor aColor): Piece(
        aColor,
        vector <int> {-11, -10, -9, -1, 1, 9, 10, 11},
        false
        ) {}


char Queen::PieceToFEN() {
    return (this->GetColor() == WHITE ? 'q' : 'Q');
}
