//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_SQUAREBUTTON_H
#define E_CHESS_SQUAREBUTTON_H

#include "ClickableElement.h"

class SquareButton : public ClickableElement {
public:
    SquareButton();
    SquareButton(Point2I d, Point2I f);

private:
    void action();


};


#endif //E_CHESS_SQUAREBUTTON_H
