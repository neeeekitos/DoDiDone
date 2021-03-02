/*
 * ---------------------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <edouembe@ensea.fr> and <showok@showok.info> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return. Edouard Emberger and Théo Segonds
 * ---------------------------------------------------------------------------------------------------
 */
#include "GraphicElement.h"

#ifndef CLICKABLE
#define CLICKABLE

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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
    Point2I startPoint, endPoint;

    virtual void action();
};

#endif
