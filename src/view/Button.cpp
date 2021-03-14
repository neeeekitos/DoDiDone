#include "../../include/view/Button.h"

Button::Button() {}

Button::Button(Point2I s, Point2I e, int t) : ClickableElement(s, e), type(t) {}

Button::~Button() {}
