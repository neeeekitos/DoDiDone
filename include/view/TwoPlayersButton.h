//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_TWOPLAYERSBUTTON_H
#define E_CHESS_TWOPLAYERSBUTTON_H


#include "ClickableElement.h"

class TwoPlayersButton : public ClickableElement {
public:
    TwoPlayersButton();
    TwoPlayersButton(Point2I d, Point2I f);

private:
    void action();


};

#endif //E_CHESS_TWOPLAYERSBUTTON_H
