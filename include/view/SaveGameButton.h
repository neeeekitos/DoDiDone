//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_SAVEGAMEBUTTON_H
#define E_CHESS_SAVEGAMEBUTTON_H

#include "ClickableElement.h"

class SaveGameButton : public ClickableElement {
public:
    SaveGameButton();
    SaveGameButton(Point2I d, Point2I f);

private:
    void action();


};


#endif //E_CHESS_SAVEGAMEBUTTON_H
