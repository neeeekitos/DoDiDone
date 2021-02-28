//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/view/View.h"
#include "../../include/model/Chessboard.h"
#include "../../include/view/NewGameButton.h"
#include "../../include/view/OnePlayerButton.h"
#include "../../include/view/TwoPlayersButton.h"
#include "../../include/controller/GameController.h"

const string IMG_BASE_PATH = "./../../img/";
const float MARGIN_BETWEEN_PIECE_FACTOR_X = 0.9;
const float MARGIN_BETWEEN_PIECE_FACTOR_Y = 0.85;
const int BOARD_LEFT_TOP_CORNER_X = 323;
const int BOARD_LEFT_TOP_CORNER_Y = 135;

typedef enum {
    SAVE,
    LOAD,
    NEW_GAME,
    ONE_PLAYER,
    TWO_PLAYERS,
    DEFAULT
} ButtonType;

typedef enum {
    BOARD,
    HOME
} InterfaceElements;

View* View::view_ = nullptr;


View * View::GetInstance() {
    if (View::view_ == nullptr) {
        View::view_ = new View;
    }
    return View::view_;
}

View::View() : window(new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H),"GUI chess")) {
}

View::~View() {
    delete window;
    deleteButtonElements();
    deleteInterfaceElements();
}

void View::MenuChoices() {
    bool newGamePressed = false;
    int playerCount = -1;

    sf::Event event;
    interfaceInitialisation(0);

    while (!newGamePressed || playerCount == -1) {
        while (window->pollEvent(event) && (!newGamePressed || playerCount == -1)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (!newGamePressed) {
                    if (buttons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        newGamePressed = true;
                        interfaceInitialisation(1);
                    }
                } else {
                    if (buttons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        playerCount = 2;
                        interfaceInitialisation(2);
                    } else if (buttons[1]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        playerCount = 1;
                        interfaceInitialisation(2);
                    }
                }
            }
        }
        displayGameIn(*window);
    }
}


void View::MainLoop() {

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                //getButtonClicked(event);
            }
        }
        interfaceInitialisation(2);
        displayGameIn(*window);
    }
}

void View::update(Chessboard &cb) {
    window->clear();
    displayInterfaceIn(*window);
    window->display();
}

void View::notifyGame(const sf::Event &event) {}


void View::displayInterfaceIn(sf::RenderWindow &w) {
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        interface.at(i)->draw(w);
    }
}

void View::deleteInterfaceElements() {
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        delete (interface.at(i));
    }
    interface.clear();
}

void View::deleteButtonElements() {
    int size = buttons.size();
    for (int i = 0; i < size; i++) {
        delete (buttons.at(i));
    }
    buttons.clear();
}

void View::displayGameIn(sf::RenderWindow &w) {
    w.clear();
    displayInterfaceIn(w);
    w.display();
}

void View::interfaceInitialisation(int step) {
    deleteButtonElements();
    deleteInterfaceElements();
    Point2I p1;
    Point2I p2;
    sf::Vector2u v;
    int shiftY = 0;
    GraphicElement img;

    switch (step) {
        case 0:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement("./../../data/bouton-newGame.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 100);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 100);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::NEW_GAME));
            break;

        case 1:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement("./../../data/bouton-2Players.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 200);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 200);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::TWO_PLAYERS));

            interface.push_back(new GraphicElement("./../../data/bouton-1Players.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 500);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 500);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::ONE_PLAYER));
            break;
        case 2:
            //gameInitialisation();
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "board-with-background2.png"));
            img = GraphicElement(IMG_BASE_PATH + "noir-pion.png");
            img.setScale(0.7);

            v = img.getSprite(0).getTexture()->getSize();
            for (int i = 0; i < 3 ; i++)
            {
                for (int j = 0 ; j<6 ; j++) {
                    interface.push_back(new GraphicElement(IMG_BASE_PATH + "noir-pion.png"));
                    interface[interface.size() - 1]->setPosition(Point2I(BOARD_LEFT_TOP_CORNER_X+MARGIN_BETWEEN_PIECE_FACTOR_X*j*v.x, BOARD_LEFT_TOP_CORNER_Y+MARGIN_BETWEEN_PIECE_FACTOR_Y*shiftY));
                    interface[interface.size() - 1]->setScale(0.7);
                }
                shiftY += v.y;
            }


            break;

        default:
            break;
    }
}


