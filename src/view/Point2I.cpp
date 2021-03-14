#include "../../include/view/Point2I.h"

Point2I::Point2I(int xCoord, int yCoord) {
    x = xCoord;
    y = yCoord;
}

Point2I::Point2I() {
    x = 0;
    y = 0;
}

Point2I::~Point2I() {}

int Point2I::GetX() {
    return x;
}

int Point2I::GetY() {
    return y;
}

void Point2I::SetX(int xCoord) {
    x = xCoord;
}

void Point2I::SetY(int yCoord) {
    x = yCoord;
}

bool Point2I::operator==(Point2I const &p) {
    if (x == p.x && y == p.y)
        return true;
    else
        return false;
}
