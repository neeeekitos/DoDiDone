//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_ONEPLAYERBUTTON_H
#define E_CHESS_ONEPLAYERBUTTON_H

#include "ClickableElement.h"

class OnePlayerButton : public ClickableElement {
public:
    OnePlayerButton();
    OnePlayerButton(Point2I d, Point2I f);

private:
    void action();


};


#endif //E_CHESS_ONEPLAYERBUTTON_H
