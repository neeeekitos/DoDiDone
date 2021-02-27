//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_LOADGAMEBUTTON_H
#define E_CHESS_LOADGAMEBUTTON_H

#include "ClickableElement.h"

class LoadGameButton : public ClickableElement {
public:
    LoadGameButton();
    LoadGameButton(Point2I d, Point2I f);

private:
    void action();


};


#endif //E_CHESS_LOADGAMEBUTTON_H
