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

class View {
public:
    View(Chessboard * const chessBoard);
    ~View();
    void update (Chessboard & cb);
    void MainLoop();


private:
    void interfaceInitialisation(int step);
    void gameInitialisation();

    void displayGameIn(sf::RenderWindow &w);
    void displayInterfaceIn(sf::RenderWindow &w);
    void notifyInterface(const sf::Event &event);
    void notifyGame(const sf::Event &event);
    void newGame();

    sf::RenderWindow *window;
    std::vector<GraphicElement*> interface ;
    std::vector<ClickableElement*> boutons ;
    Chessboard *chessboardModel;
};


#endif //E_CHESS_VIEW_H
