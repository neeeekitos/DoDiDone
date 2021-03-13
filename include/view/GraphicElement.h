#ifndef E_CHESS_GRAPHICELEMENT_H
#define E_CHESS_GRAPHICELEMENT_H

#define SPRITE_SIZE 80

#include "Point2I.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

class GraphicElement {


public:
    GraphicElement();

    ~GraphicElement();

    GraphicElement(const string s);

    void draw(sf::RenderWindow &window);

    void setSprite(string fileName, int lvl);

    sf::Sprite &getSprite(char state);

    void setPosition(Point2I p);

    Point2I getPosition();

    void setRotation(float angle);

    void setScale(float size);

    void checkPosition();

protected:
sf::Sprite img;
sf::Texture t;
Point2I p;
};

#endif // E_CHESS_GRAPHICELEMENT_H

