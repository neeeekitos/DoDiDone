#include "../../include/view/ClickableElement.h"

ClickableElement::ClickableElement() {}

void ClickableElement::setStartPoint(Point2I p) {
    startPoint = p;
}

void ClickableElement::setEndPoint(Point2I p) {
    endPoint = p;
}

ClickableElement::ClickableElement(Point2I s, Point2I e) {
    endPoint = e;
    startPoint = s;
}

ClickableElement::~ClickableElement() {

}

Point2I ClickableElement::getEndPoint() {
    return endPoint;
}

Point2I ClickableElement::getStartPoint() {
    return startPoint;
}

bool ClickableElement::checkPosition(int x, int y) {
    if (x > startPoint.GetX() && y > startPoint.GetY() && x < endPoint.GetX() && y < endPoint.GetY())
        return true;
    else
        return false;
}


