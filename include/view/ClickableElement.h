#ifndef E_CHESS_CLICKABLEELEMENT_H
#define E_CHESS_CLICKABLEELEMENT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "GraphicElement.h"

class ClickableElement {
public:
ClickableElement();

ClickableElement(Point2I d, Point2I f);

~ClickableElement();


void setStartPoint(Point2I p);

void setEndPoint(Point2I p);

virtual Point2I getEndPoint();

virtual Point2I getStartPoint();

bool checkPosition(int x, int y);

protected:
Point2I startPoint;
Point2I endPoint;
};

#endif // E_CHESS_CLICKABLEELEMENT_H
