//
// Created by lpietropao on 28/02/2021.
//

#include "../../include/view/Button.h"

Button::Button() {}

Button::Button(Point2I d, Point2I f, int t): ClickableElement(d, f), type(t) {}
