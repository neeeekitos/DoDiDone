#include <iostream>
#include <sstream>

using namespace std;

class Point2I {
public:
    Point2I(int, int);

    Point2I();

    ~Point2I();

    int getX();

    int getY();

    void setX(int);

    void setY(int);

    bool operator==(Point2I const &p);

private:
    int x;
    int y;
};

#endif
