#ifndef E_CHESS_BUTTON_H
#define E_CHESS_BUTTON_H

#include "ClickableElement.h"

/**
 * @brief Clickable button
 */
class Button : public ClickableElement {

public:

    /**
     * @brief Public default constructor of Button
     */
    Button();

    /**
     * @brief Public constructor with params of Button
     * @param s Start point
     * @param e End point
     * @param t Type
     */
    Button(Point2I s, Point2I e, int t);

    /**
     * @brief Destructor of Button
     */
    ~Button();

private:

    /**
     * @brief Button type
     */
    int type;

};

#endif //E_CHESS_BUTTON_H
