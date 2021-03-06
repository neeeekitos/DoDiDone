//
// Created by Nikita TEREKHOV on 06/03/2021.
//

#ifndef E_CHESS_AI_H
#define E_CHESS_AI_H

#include "../model/GameConstants.h"
#include "../model/Chessboard.h"


class AI {
public:
    static AI * GetInstance();
    bool doMove();
    int randomMove();



    ~AI();
    AI(const AI&) = delete;
    void operator= (const AI&) = delete;



private:
    AI();
    vector<Move> AIMoves;
    vector<Move> HumanMoves;
    Chessboard

};

#endif //E_CHESS_AI_H
