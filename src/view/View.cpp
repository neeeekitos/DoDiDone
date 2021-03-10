//
// Created by lpietropao on 27/02/2021.
//
#define WINDOW_W 1100
#define WINDOW_H 720

#include "../../include/view/View.h"
#include "../../include/controller/GameController.h"

const string IMG_BASE_PATH = "./img/";
const string BUTTONS_IMG_BASE_PATH = "./img/buttons/";
const string FONT_BASE_PATH = "./font/";
const int BOARD_LEFT_TOP_CORNER_X = 294;
const int BOARD_LEFT_TOP_CORNER_Y = 107;
const float SQUARE_OUTLINE_THICKNESS = 10;
const float SQUARE_WIDTH = 69.5;
const float SQUARE_HEIGHT = 66.999;
const sf::Color CLICKED_SQUARE_OUTLINE_COLOR = sf::Color::Yellow;
const sf::Color DESTINATION_SQUARE_OUTLINE_COLOR = sf::Color::Green;

std::vector<int> tab = {1, 2, 3, 4, 5};

typedef enum {
    SAVE,
    LOAD,
    NEW_GAME,
    ONE_PLAYER,
    TWO_PLAYERS,
    PREVIOUS,
    NEXT
} ButtonType;

View *View::view_ = nullptr;

View *View::GetInstance() {
    if (View::view_ == nullptr) {
        View::view_ = new View;
    }
    return View::view_;
}

View::View() : window(new sf::RenderWindow(sf::VideoMode(WINDOW_W, WINDOW_H), "GUI chess", sf::Style::Close)),
               selectedSquare(make_pair(-1, -1)) {
}

View::~View() {
    delete window;
    deleteButtonElements();
    deleteInterfaceElements();
    deleteTextElements();
    deleteBoardSquares();
}

void View::MenuChoices() {
    bool newGamePressed = false;
    bool changeLoadedGame = false;
    int playerCount = -1;

    sf::Event event;
    interfaceInitialisation(0);
    vector<int> savedGames;
    GameController::GetInstance()->GetSavedGamesIds(savedGames);
    auto savedGamesIterator = savedGames.begin();

    while (!newGamePressed || playerCount == -1) {
        while (window->pollEvent(event) && (!newGamePressed || playerCount == -1)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (!newGamePressed) {
                    if (buttons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //new game
                        newGamePressed = true;
                        interfaceInitialisation(1);
                    } else if (buttons[3]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //load game
                        newGamePressed = true;
                        playerCount = 1;
                        interfaceInitialisation(2);
                    }
                        //next and previous buttons -> circular course of game ids
                    else if (buttons[1]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //previous game
                        changeLoadedGame = true;
                        if (savedGamesIterator == savedGames.begin()) {
                            savedGamesIterator = savedGames.end();
                        }
                        savedGamesIterator--;
                    } else if (buttons[2]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //next game
                        changeLoadedGame = true;
                        savedGamesIterator++;
                        if (savedGamesIterator == savedGames.end()) {
                            savedGamesIterator = savedGames.begin();
                        }
                    }
                    //load new game id button image
                    if (changeLoadedGame) {
                        interface[2]->setSprite(
                                BUTTONS_IMG_BASE_PATH + "games/game-" + to_string(*savedGamesIterator) + ".png", 0);
                        sf::Vector2<unsigned int> v = interface[interface.size() - 1]->getSprite(
                                0).getTexture()->getSize();
                        Point2I p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 225);
                        interface[2]->setPosition(p1);
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
                Chessboard *chessBoard = Chessboard::GetInstance();
                int i = getSquareClickedIndex(event.mouseButton.x, event.mouseButton.y);
                pair<int, int> clickedSquare = chessBoard->ConvertOneDimensionPositionToCoordinate(i);
                cout << "click " << event.mouseButton.x << "-" << event.mouseButton.y << endl;
                if (i != -1 && i < boardSquares.size()) {
                    cleanSquareOutlines();

                    //a square is already selected
                    if (selectedSquare != make_pair(-1, -1)) {
                        //get possible moves of selected square (not clicked square)
                        DestinationsSet possibleMovesSelectedSquare = chessBoard->GetPossibleMoves(
                                selectedSquare, false);
                        //user clicks on a possible move
                        cout << "clicked=" << clickedSquare.first << "-" << clickedSquare.second << endl;
                        cout << "clicked===== " << (possibleMovesSelectedSquare.size() >= 1 &&
                                                    clickedSquare == possibleMovesSelectedSquare.at(1)) << endl;
                        for (auto it = possibleMovesSelectedSquare.begin();
                             it != possibleMovesSelectedSquare.end(); ++it)
                            cout << "  ||  " << it->first << "-" << it->second;
                        cout << endl;

                        if (std::find(possibleMovesSelectedSquare.begin(), possibleMovesSelectedSquare.end(),
                                      clickedSquare) != possibleMovesSelectedSquare.end()) {
                            cout << "makeMove " << clickedSquare.first << " - " << clickedSquare.second << endl;
                            GameController::GetInstance()->MakeMove(make_pair(selectedSquare, clickedSquare));
                            cout <<*Chessboard::GetInstance() << endl;
                        }
                    } else {
                        //set selected square
                        selectedSquare = clickedSquare;
                        //highlight selected square
                        boardSquares.at(i)->setOutlineThickness(SQUARE_OUTLINE_THICKNESS);
                        boardSquares.at(i)->setOutlineColor(CLICKED_SQUARE_OUTLINE_COLOR);

                        //get possible moves of selected square
                        DestinationsSet possibleMovesSelectedSquare = chessBoard->GetPossibleMoves(
                                selectedSquare, false);
                        int size = possibleMovesSelectedSquare.size();
                        //highlight possible moves
                        for (int i = 0; i < size; i++) {
                            int index1D = 8 * possibleMovesSelectedSquare.at(i).first + possibleMovesSelectedSquare.at(i).second;
                            boardSquares.at(index1D)->setOutlineThickness(SQUARE_OUTLINE_THICKNESS);
                            boardSquares.at(index1D)->setOutlineColor(DESTINATION_SQUARE_OUTLINE_COLOR);
                        }
                    }
                }
            }
        }
        displayGameIn(*window, true);
    }
}

void View::update(Chessboard &cb) {
    displayGameIn(*window);
}

void View::initBoardSquares() {
    deleteBoardSquares();
    int shiftY = BOARD_LEFT_TOP_CORNER_Y;
    int index1D = 0;
    for (int line = 0; line < 8; line++) {
        for (int col = 0; col < 8; col++) {
            index1D = 8 * line + col;
            boardSquares.push_back(new sf::RectangleShape(sf::Vector2f(SQUARE_WIDTH - SQUARE_OUTLINE_THICKNESS * 2,
                                                                       SQUARE_HEIGHT - SQUARE_OUTLINE_THICKNESS * 2)));
            boardSquares.at(index1D)->setPosition(
                    sf::Vector2f(BOARD_LEFT_TOP_CORNER_X + col * SQUARE_WIDTH + SQUARE_OUTLINE_THICKNESS,
                                 shiftY + SQUARE_OUTLINE_THICKNESS));
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

void View::deleteTextElements() {
    int size = texts.size();
    for (int i = 0; i < size; i++) {
        delete (texts.at(i));
    }
    texts.clear();
}

void View::deleteBoardSquares() {
    int size = boardSquares.size();
    for (int i = 0; i < size; i++) {
        delete (boardSquares.at(i));
    }
    if (boardSquares.size() > 0)
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

    for (int i = 0; i < size; i++) {
        boardSquares.at(i)->setOutlineThickness(0);
    }
}

void View::displayEatenPieces(sf::RenderWindow &w) {

}


void View::displayGameIn(sf::RenderWindow &w, bool gameGoesOn) {
    w.clear();

    //interface elements first
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        interface.at(i)->draw(w);
    }

    //text elements first
    size = texts.size();
    for (int i = 0; i < size; i++) {
        w.draw(*(texts.at(i)));
    }

    if (gameGoesOn) {
        //board squares with pieces
        size = boardSquares.size();
        for (int i = 0; i < size; i++) {
            sf::Texture texture;
            string pieceName = PIECE_NAME[Chessboard::GetInstance()->GetPiece(i)->GetType()];
            if (pieceName != PIECE_NAME[NONE]) {
                string pieceColor = PIECE_COLOR_NAME[Chessboard::GetInstance()->GetPiece(i)->GetColor()];

                if (!texture.loadFromFile(IMG_BASE_PATH + "pieces/" + pieceColor + "/" + pieceName + ".png")) {
                    cerr << "error" << endl;
                } else {
                    boardSquares.at(i)->setTexture(&texture);
                }
            } else {
                boardSquares.at(i)->setFillColor(sf::Color::Transparent);
            }
            w.draw(*(boardSquares.at(i)));
        }
        //display turn count
        texts[0]->setString(to_string(GameController::GetInstance()->GetTurnCount()));
        displayEatenPieces(w);

        if (GameController::GetInstance()->GetCurrentPlayer() == PieceColor::BLACK) {
            interface[4]->setSprite(
                    IMG_BASE_PATH + "current-player-black.png", 0);
        } else {
            interface[4]->setSprite(
                    IMG_BASE_PATH + "current-player-white.png", 0);
        }

        sf::Vector2 v = interface[4]->getSprite(0).getTexture()->getSize();
        Point2I p1 = Point2I(WINDOW_W / 2 - v.x / 2 + 47, 6);
        interface[interface.size() - 1]->setPosition(p1);
    }

    w.display();
}

void View::interfaceInitialisation(int step) {
    deleteButtonElements();
    deleteInterfaceElements();
    deleteTextElements();
    Point2I p1;
    Point2I p2;
    sf::Vector2u v;
    GraphicElement img;
    string gameModeImg;
    font.loadFromFile(FONT_BASE_PATH + "OpenSans-Bold.ttf");


    switch (step) {
        case 0:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "/new-game.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 400);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 400);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::NEW_GAME));


            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "games/game-1.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 225);
            interface[interface.size() - 1]->setPosition(p1);

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "previous.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2 - 173, WINDOW_H - v.y - 225);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2 - 150, WINDOW_H - 225);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::PREVIOUS));

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "next.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2 + 173, WINDOW_H - v.y - 225);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2 + 200, WINDOW_H - 225);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::NEXT));

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "load-game.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 150);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 150);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::LOAD));
            break;

        case 1:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "/2-players.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 200);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 200);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::TWO_PLAYERS));

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "player-vs-bot.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 400);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H - 400);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::ONE_PLAYER));
            break;

        case 2:
            //chessboard background
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "board-with-background2.png"));
            //initBoardSquares();

            //add game mode to interface
            gameModeImg = "2-players.png";
            if (GameController::GetInstance()->GetGameMode() == GameMode::AI) {
                gameModeImg = "players-vs-bot.png";
            }
            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + gameModeImg));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            interface[interface.size() - 1]->setPosition(Point2I(815, 0));

            //add to texts turn count
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "turn-count.png"));
            interface[interface.size() - 1]->setPosition(Point2I(0, 0));

            texts.push_back(new sf::Text("bonjour", font, 30));
            cout << (texts.size()) << "!!!!!!!!!" << endl;
            texts[texts.size() - 1]->setFont(font);
            texts[texts.size() - 1]->setCharacterSize(28);
            texts[texts.size() - 1]->setString(to_string(GameController::GetInstance()->GetTurnCount()));
            texts[texts.size() - 1]->setFillColor(sf::Color::White);
            texts[texts.size() - 1]->setPosition(170, 22);

            //add to interface which player should play
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "/current-player.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, 0);
            interface[interface.size() - 1]->setPosition(p1);

            interface.push_back(new GraphicElement(IMG_BASE_PATH + "/current-player-black.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2 + 47, 6);
            interface[interface.size() - 1]->setPosition(p1);

            deleteBoardSquares();
            initBoardSquares();
            break;

        default:
            break;
    }
}

int View::getSquareClickedIndex(int x, int y) {
    int size = boardSquares.size();
    int i = 0;
    while (i < size) {
        if (boardSquares.at(i)->getGlobalBounds().contains(x, y)) {
            return i;
        }
        i++;
    }
    return -1;
}






