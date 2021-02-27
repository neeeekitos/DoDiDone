//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_NEWGAMEBUTTON_H
#define E_CHESS_NEWGAMEBUTTON_H

#include "ClickableElement.h"

class NewGameButton : public ClickableElement {
public:
    NewGameButton();
    NewGameButton(Point2I d, Point2I f);
private:

    void action();


};

#endif //E_CHESS_NEWGAMEBUTTON_H
