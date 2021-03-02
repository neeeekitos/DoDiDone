//
// Created by lpietropao on 27/02/2021.
//

#include "../../include/view/View.h"
#include "../../include/model/GameConstants.h"
#include "../../include/model/Chessboard.h"
#include "../../include/model/Piece.h"
#include "../../include/model/Pawn.h"
#include "../../include/model/Tower.h"
#include "../../include/view/NewGameButton.h"
#include "../../include/view/OnePlayerButton.h"
#include "../../include/view/TwoPlayersButton.h"
#include "../../include/controller/GameController.h"

const string IMG_BASE_PATH = "./../../img/";
const float MARGIN_BETWEEN_PIECE_FACTOR_X = 0.9;
const float MARGIN_BETWEEN_PIECE_FACTOR_Y = 0.85;
const int BOARD_LEFT_TOP_CORNER_X = 294;
const int BOARD_LEFT_TOP_CORNER_Y = 107;
const float SQUARE_OUTLINE_THICKNESS = 10;
const float SQUARE_WIDTH = 69.5;
const float SQUARE_HEIGHT = 66.999;
const sf::Color CLICKED_SQUARE_OUTLINE_COLOR = sf::Color::Yellow;
const sf::Color DESTINATION_SQUARE_OUTLINE_COLOR = sf::Color::Green;

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
    deleteBoardSquares();
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
                int i = getSquareClickedIndex(event.mouseButton.x, event.mouseButton.y);
                cout << "click " << event.mouseButton.x << "-" << event.mouseButton.y << endl;
                if (i != -1 && i < boardSquares.size()) {
                    cleanSquareOutlines();
                    //highlight clicked squares
                    boardSquares.at(i)->setOutlineThickness(SQUARE_OUTLINE_THICKNESS);
                    boardSquares.at(i)->setOutlineColor(CLICKED_SQUARE_OUTLINE_COLOR);
                    //highlight possible moves
                    Chessboard *chessBoard = Chessboard::GetInstance();
                    DestinationsSet possibleMoves = chessBoard->GetPossibleMoves(chessBoard->ConvertOneDimensionPositionToCoordinate(i), false);
                    int size = possibleMoves.size();
                    for(int i = 0;  i < size ; i++)
                    {
                        int index1D = 8 * possibleMoves.at(i).first + possibleMoves.at(i).second;
                        boardSquares.at(index1D)->setOutlineThickness(SQUARE_OUTLINE_THICKNESS);
                        boardSquares.at(index1D)->setOutlineColor(DESTINATION_SQUARE_OUTLINE_COLOR);
                    }
                }
            }
        }
        displayGameIn(*window);
    }
}

void View::update(Chessboard &cb) {
    displayGameIn(*window);
}

void View::initBoardSquares() {
    boardSquares.clear();
    int shiftY = BOARD_LEFT_TOP_CORNER_Y;
    int index1D = 0;
    for (int line = 0; line < 8 ; line++) {
        for (int col = 0; col < 8; col++) {
            index1D = 8 * line + col;
            boardSquares.push_back(new sf::RectangleShape(sf::Vector2f(SQUARE_WIDTH-SQUARE_OUTLINE_THICKNESS*2, SQUARE_HEIGHT-SQUARE_OUTLINE_THICKNESS*2)));
            boardSquares.at(index1D)->setPosition(
                    sf::Vector2f(BOARD_LEFT_TOP_CORNER_X + col * SQUARE_WIDTH + SQUARE_OUTLINE_THICKNESS, shiftY + SQUARE_OUTLINE_THICKNESS));
            boardSquares.at(index1D)->setOutlineThickness(0);
        }
        shiftY += SQUARE_HEIGHT;
    }
}


void View::deleteInterfaceElements() {
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        delete (interface.at(i));
    }
    interface.clear();
}

void View::deleteBoardSquares() {
    int size = boardSquares.size();
    for (int i = 0; i < size; i++) {
        delete (boardSquares.at(i));
    }
    boardSquares.clear();
}

void View::deleteButtonElements() {
    int size = buttons.size();
    for (int i = 0; i < size; i++) {
        delete (buttons.at(i));
    }
    buttons.clear();
}

void View::cleanSquareOutlines() {
    int size = boardSquares.size();

    for (int i = 0; i < size ; i++)
    {
        boardSquares.at(i)->setOutlineThickness(0);
    }
}

void View::displayEatenPieces(sf::RenderWindow &w) {

}

void View::displayPossibleMoves(sf::RenderWindow &w) {

}


void View::displayGameIn(sf::RenderWindow &w) {
    w.clear();
    //interface elements first
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        interface.at(i)->draw(w);
    }
    //board squares with pieces
    size = boardSquares.size();
    for (int i = 0; i < size; i++) {
        sf::Texture texture;
        string pieceName = PIECE_NAME[Chessboard::GetInstance()->GetPiece(i)->GetType()];
        if (pieceName != PIECE_NAME[NONE]){
            string pieceColor = PIECE_COLOR_NAME[Chessboard::GetInstance()->GetPiece(i)->GetColor()];
            if (!texture.loadFromFile(IMG_BASE_PATH + "pieces/" + pieceColor + "/" + pieceName + ".png"))
            {
                cerr << "error" << endl;
            }
            boardSquares.at(i)->setTexture(&texture);
        } else {
            boardSquares.at(i)->setFillColor(sf::Color::Transparent);
        }

        displayEatenPieces(w);

        //display which player should play

        //display turn count


        w.draw(*(boardSquares.at(i)));
    }


    w.display();
}

void View::interfaceInitialisation(int step) {
    deleteButtonElements();
    deleteInterfaceElements();
    Point2I p1;
    Point2I p2;
    sf::Vector2u v;
    GraphicElement img;

    switch (step) {
        case 0:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement(IMG_BASE_PATH + "new-game-button.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 100);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 100);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::NEW_GAME));
            break;

        case 1:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement(IMG_BASE_PATH + "/2-players-button.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 200);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 200);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::TWO_PLAYERS));

            interface.push_back(new GraphicElement(IMG_BASE_PATH + "1-player-button.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 500);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 500);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::ONE_PLAYER));
            break;
        case 2:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "board-with-background2.png"));
            initBoardSquares();
            displayGameIn(*window);
            break;

        default:
            break;
    }
}

int View::getSquareClickedIndex(int x, int y)
{
    int size = boardSquares.size();
    int i = 0;
    while (i < size) {
        if (boardSquares.at(i)->getGlobalBounds().contains(x, y)) {
            const Piece *piece = Chessboard::GetInstance()->GetPiece(i);
            cout << "piece == KING? " << (piece->GetType() == PIECE_TYPE::KING) << endl;
            cout << "piece == TOWER? " << (piece->GetType() == PIECE_TYPE::TOWER) << endl;
            cout << "i= " << i << endl;
            return  i;
        }
        i++;
    }
    return -1;
}






