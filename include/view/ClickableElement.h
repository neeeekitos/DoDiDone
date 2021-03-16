#ifndef E_CHESS_CLICKABLEELEMENT_H
#define E_CHESS_CLICKABLEELEMENT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "GraphicElement.h"

/**
 * @brief A clickable element
 */
class ClickableElement {

public:

    /**
     * @brief Public default constructor of ClickableElement
     */
    ClickableElement();

    /**
     * @brief Public constructor with params of ClickableElement
     * @param s Start point
     * @param e End point
     */
    ClickableElement(Point2I s, Point2I e);

    /**
     * @brief Destructor of ClickableElement
     */
    ~ClickableElement();

    /**
     * @brief Set start point to p
     * @param p New start point
     */
    void setStartPoint(Point2I p);

    /**
     * @brief Set end point to p
     * @param p New end point
     */
    void setEndPoint(Point2I p);

    /**
     * @brief Get end point
     * @return
     */
    virtual Point2I getEndPoint();

    /**
     * @brief Get start point
     * @return
     */
    virtual Point2I getStartPoint();

    /**
     * @brief Check if a point with {x, y} coordinates
     * is inside this ClickableElement
     * @param x X coordinate
     * @param y Y coordinate
     * @return
     */
    bool checkPosition(int x, int y);

protected:

    /**
     * @brief Start point of this ClickableElement
     */
    Point2I startPoint;

    /**
     * @brief End point of this ClickableElement
     */
    Point2I endPoint;
};

#endif // E_CHESS_CLICKABLEELEMENT_H
