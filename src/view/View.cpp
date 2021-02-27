//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/view/View.h"
#include "../../include/model/Chessboard.h"
#include "../../include/view/NewGameButton.h"
#include "../../include/view/OnePlayerButton.h"
#include "../../include/view/TwoPlayersButton.h"

View::View(Chessboard *const chessBoard) : chessboardModel(chessBoard),
                                           window(new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H),
                                                                       "GUI chess")) {
}

View::~View() {
    delete window;
}

void View::update(Chessboard &cb) {}

void View::MenuChoices() {
    bool newGamePressed = false;
    int playerCount = -1;

    sf::Event event;
    interfaceInitialisation(0);
    window->clear();
    sf::Texture texture;
    sf::Sprite sprite;
    try {
        texture.loadFromFile("./../../data/accueil.png");
        sprite.setTexture(texture);
        window->draw(sprite);
    } catch (exception) {
    }
    while (!newGamePressed || playerCount == -1) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {

                if (!newGamePressed) {
                    if (!boutons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        newGamePressed = true;
                        interfaceInitialisation(1);
                    }
                } else {
                    if (boutons[0]->isInside(event)) {
                        playerCount = 2;
                        interfaceInitialisation(2);
                    } else if (boutons[1]->isInside(event)) {
                        playerCount = 1;
                        interfaceInitialisation(2);
                    }
                }
            }
        }
        window->clear();

        //displayInterfaceIn(*window);

//        displayGameIn(*window);
        displayInterfaceIn(*window);
        window->display();


    }
}


void View::MainLoop() {
    interfaceInitialisation(0);
    window->clear();
    sf::Texture texture;
    sf::Sprite sprite;
    try {
        texture.loadFromFile("./../../data/accueil.png");
        sprite.setTexture(texture);
        window->draw(sprite);
    } catch (exception) {
    }

    //displayInterfaceIn(*window);

//        displayGameIn(*window);
    //      displayInterfaceIn(*window);
    window->display();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                notifyInterface(event);
                notifyGame(event);
            }
        }
        window->clear();

        //displayInterfaceIn(*window);

//        displayGameIn(*window);
        displayInterfaceIn(*window);
        window->display();
    }
}

void View::notifyInterface(const sf::Event &event) {
    int l = boutons.size();
    for (int i = 0; i < l; i++) {
        boutons[i]->isInside(event);
    }
}

void View::notifyGame(const sf::Event &event) {}


void View::newGame() {
    interfaceInitialisation(1);
}

void View::displayInterfaceIn(sf::RenderWindow &w) {
    int nb2 = interface.size();
    // Dans cette boucle, on affiche l'ensemble des objets graphiques du jeu (hors pieces)
    for (int i = 0; i < nb2; i++)
        interface.at(i)->draw(w);
}

void View::interfaceInitialisation(int step) {
    interface.clear();
    boutons.clear();
    Point2I p1;
    Point2I p2;
    sf::Vector2u v;

    switch (step) {
        case 0:
            interface.push_back(new GraphicElement("./../../data/accueil.png"));
            interface.push_back(new GraphicElement("./../../data/bouton-newGame.png"));

            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 100);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 100);

            interface[interface.size() - 1]->setPosition(p1);
            boutons.push_back(new NewGameButton(p1, p2));
            break;

        case 1:
            interface.push_back(new GraphicElement("./../../data/accueil.png"));
            interface.push_back(new GraphicElement("./../../data/bouton-2Players.png"));

            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 200);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 200);

            interface[interface.size() - 1]->setPosition(p1);
            boutons.push_back(new OnePlayerButton(p1, p2));

            interface.push_back(new GraphicElement("./../../data/bouton-1Players.png"));

            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 500);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 500);

            interface[interface.size() - 1]->setPosition(p1);
            boutons.push_back(new TwoPlayersButton(p1, p2));
            break;
        case 2:
            //gameInitialisation();
            interface.push_back(new GraphicElement("./../../data/plateau.png"));
            break;
    }
}


