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

    static View *GetInstance();

    View(const View &anotherView) = delete;

    void operator=(const View &aView) = delete;

    ~View();

    void update(Chessboard &cb);

    void MenuChoices();

    void MainLoop();


private:
    View();

    void interfaceInitialisation(int step);

    void displayGameIn(sf::RenderWindow &w, bool gameGoesOn = false);

    void initBoardSquares();
    void updateBoardSquares();

    void cleanSquareOutlines();

    void displayEatenPieces(sf::RenderWindow &w);

    void displayPossibleMoves(sf::RenderWindow &w);


    int getSquareClickedIndex(int x, int y);

    void deleteButtonElements();

    void deleteInterfaceElements();

    void deleteTextElements();

    void deleteBoardSquares();

    void displayStatus(GameStatus s);


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
