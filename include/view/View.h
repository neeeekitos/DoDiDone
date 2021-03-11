//
// Created by lpietropao on 27/02/2021.
//

#ifndef E_CHESS_VIEW_H
#define E_CHESS_VIEW_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../model/Chessboard.h"
#include "GraphicElement.h"
#include "ClickableElement.h"
#include "Button.h"

class View {

public:

    /**
     * @brief
     * @return Singleton of View
     */
    static View *GetInstance();

    /**
     * @brief Copy constructor of View
     * @param anotherView
     */
    View(const View &anotherView) = delete;

    /**
     * @brief operator= for View
     * @param aView
     */
    void operator=(const View &aView) = delete;

    /**
     * @brief Destructor for View
     */
    ~View();

    /**
     * @brief Loop to choose game options
     */
    void MenuChoices();

    /**
     * @brief Main loop for the game
     */
    void MainLoop();


private:

    /**
     * @brief Private constructor
     */
    View();

    /**
     * @brief Init window with all elements depending on step
     * @param step - curent view step : before game begins, after a shot, at the end of game
     */
    void interfaceInitialisation(int step);

    /**
     * @brief Init window with all elements depending on step and game status
     * @param s
     */
    void interfaceInitialisationWithStatus(GameStatus s);

    /**
     * @brief Init chessboard squares to enable click detection on them
     */
    void initBoardSquares();

    /**
     * @brief Draw all graphic element into the window and display it
     * @param w
     * @param gameGoesOn
     */
    void displayGameIn(sf::RenderWindow &w, bool gameGoesOn = false);

    /**
     * @brief Get 1D index of clicked square
     * @param x
     * @param y
     * @return
     */
    int getSquareClickedIndex(int x, int y);

    /**
     * @brief Free memory for button elements
     */
    void deleteButtonElements();

    /**
     * @brief Free memory for interface elements
     */
    void deleteInterfaceElements();

    /**
     * @brief Free memory for text elements
     */
    void deleteTextElements();

    /**
     * @brief Free memory for square elements
     */
    void deleteBoardSquares();


    sf::RenderWindow *window;
    std::vector<GraphicElement *> interface;
    std::vector<Button *> buttons;
    std::vector<sf::RectangleShape *> boardSquares;
    std::vector<sf::Texture *> boardSquareTextures;
    std::vector<sf::Text *> texts;
    sf::Font font;
    std::pair<int, int> selectedSquare;
    DestinationsSet possibleMovesSelectedSquare;

    static View *view_;

};


#endif //E_CHESS_VIEW_H
