#ifndef E_CHESS_POINT2I_H
#define E_CHESS_POINT2I_H

/**
 * @brief Represents a 2D point with integer coordinates
 */
class Point2I {

public:

    /**
     * @brief Constrcutor with params for Point2I
     * @param xCoord X coordinate
     * @param yCoord Y coordinate
     */
    Point2I(int xCoord, int yCoord);

    /**
     * @brief Default constrcutor of Poitn2I
     */
    Point2I();

    /**
     * @brief Destructor of Point2I
     */
    ~Point2I();

    /**
     * @brief Get x coordinate
     * @return x coordinate
     */
    int GetX();

    /**
     * @brief Get y coordinate
     * @return Y coordinate
     */
    int GetY();

    /**
     * @brief Set x coordinate
     * @param xCoord New x coordinate
     */
    void SetX(int xCoord);

    /**
     * @brief Set y coordinate
     * @param yCoord New y coordinate
     */
    void SetY(int yCoord);

    /**
     * @brief Operator==
     * @param p Point to compare with
     * @return True if two points have same coordinates
     */
    bool operator==(Point2I const &p);

private:

    /**
     * @brief X coordinate
     */
    int x;

    /**
     * @brief Y coordinate
     */
    int y;
};

#endif // E_CHESS_POINT2I_H