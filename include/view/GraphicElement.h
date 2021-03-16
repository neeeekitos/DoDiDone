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

/**
 * @brief An interface element on which an image can be added
 */
class GraphicElement {

public:

    /**
     * @brief Public default constructor of GraphicElement
     */
    GraphicElement();

    /**
     * @brief Public default constructor of GraphicElement
     * @param s
     */
    GraphicElement(const string s);

    /**
     * @brief Destructor of GraphicElement
     */
    ~GraphicElement();

    /**
     * @brief Draw this element into the window
     * @param window
     */
    void Draw(sf::RenderWindow &window);

    /**
     * @brief Set image
     * @param fileName
     * @param lvl
     */
    void SetSprite(string fileName, int lvl);

    /**
     * @brief Get image
     * @param state
     * @return
     */
    sf::Sprite &GetSprite(char state);

    /**
     * @brief Set element position
     * @param p Left top corner point
     */
    void SetPosition(Point2I p);

    /**
     * @brief Get element position
     * @return
     */
    Point2I GetPosition();

    /**
     * @brief Set rotation
     * @param angle
     */
    void SetRotation(float angle);

    /**
     * @brief Set scale
     * @param size
     */
    void SetScale(float size);

protected:

    sf::Sprite img;

    sf::Texture t;

    Point2I p;
};

#endif // E_CHESS_GRAPHICELEMENT_H

