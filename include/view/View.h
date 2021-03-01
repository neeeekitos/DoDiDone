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

    static View * GetInstance();

    View(const View& anotherView) = delete;

    void operator= (const View & aView) = delete;

    ~View();

    void update(Chessboard &cb);

    void MenuChoices();

    void MainLoop();


private:
    View();

    void interfaceInitialisation(int step);

    void gameInitialisation();

    void displayGameIn(sf::RenderWindow &w);

    void displayInterfaceIn(sf::RenderWindow &w);

    void notifyInterface(const sf::Event &event);

    void notifyGame(const sf::Event &event);

    Button *getButtonClicked(const sf::Event &event);

    void initBoardSquares();
    int getSquareClickedIndex(int x, int y);


    void deleteButtonElements();
    void deleteInterfaceElements();
    void deleteBoardSquares();


    sf::RenderWindow *window;
    std::vector<GraphicElement *> interface;
    std::vector<Button *> buttons;
    std::vector<sf::RectangleShape *> boardSquares;

    static View * view_;

};


#endif //E_CHESS_VIEW_H
