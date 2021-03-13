#ifndef E_CHESS_BUTTON_H
#define E_CHESS_BUTTON_H


#include "ClickableElement.h"

class Button : public ClickableElement{
public:
    Button();
    Button(Point2I d, Point2I f, int t);
private:
    int type;

};


#endif //E_CHESS_BUTTON_H
