//
// Created by lpietropao on 27/02/2021.
//
#define WINDOW_W 1100
#define WINDOW_H 720

#include "../../include/view/View.h"
#include "../../include/controller/GameController.h"

const string SEPARATION = "--------------------------------\n--------------------------------\n";
const string IMG_BASE_PATH = "./img/";
const string BUTTONS_IMG_BASE_PATH = "./img/buttons/";
const string STATUS_IMG_BASE_PATH = "./img/status/";
const string FONT_BASE_PATH = "./font/";
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
    bool refresh = false;
    vector<int> savedGames;
    int currentSavedGameIndex = 0;
    sf::Event event;

    interfaceInitialisation(0);
    displayGameIn(*window);

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
                        cout << "ok1" << endl;
                        refresh = true;
                        cout << "ok2" << endl;

                        newGamePressed = true;
                        interfaceInitialisation(1);
                    } else if (buttons[3]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //load game
                        newGamePressed = true;
                        playerCount = 1;
                        GameController::GetInstance()->LoadGame(
                                savedGames.size() >= currentSavedGameIndex ? savedGames[currentSavedGameIndex] : -1);
                        interfaceInitialisation(2);
                    }
                    else if (buttons[1]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //next and previous buttons -> circular course of game ids
                        //previous game
                        changeLoadedGame = true;
                        if (savedGamesIterator == savedGames.begin()) {
                            savedGamesIterator = savedGames.end();
                        }
                        savedGamesIterator--;
                        currentSavedGameIndex--;
                        if (currentSavedGameIndex < 0) {
                            currentSavedGameIndex = savedGames.size() - 1;
                        }
                    } else if (buttons[2]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        //next game
                        changeLoadedGame = true;
                        savedGamesIterator++;
                        currentSavedGameIndex++;
                        if (currentSavedGameIndex >= savedGames.size()) { currentSavedGameIndex = 0; }
                        if (savedGamesIterator == savedGames.end()) {
                            savedGamesIterator = savedGames.begin();
                        }
                    }
                    //load new game id button image
                    if (changeLoadedGame) {
                        refresh = true;
                        changeLoadedGame = false;
                        texts[texts.size() - 1]->setString(to_string(*savedGamesIterator + 1));
                    }
                } else {
                    if (buttons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        playerCount = 2;
                        GameController::GetInstance()->SetGameMode(GameMode::MULTIPLAYER);
                        interfaceInitialisation(2);
                    } else if (buttons[1]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                        playerCount = 1;
                        GameController::GetInstance()->SetGameMode(GameMode::AI);
                        interfaceInitialisation(2);
                    }
                }
                if (refresh) {
                    refresh = false;
                    displayGameIn(*window);
                }
            }
        }
    }
}

void View::MainLoop() {
    bool selectNewSquare = false;
    bool refresh = false;

    displayGameIn(*window, true);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                exit(0);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (buttons[0]->checkPosition(event.mouseButton.x, event.mouseButton.y)) {
                    //save game and quit
                    string gameSavedName = "Game " + to_string(GameController::GetInstance()->SaveGame()) + ".";
                    window->close();
                    cout << SEPARATION;
                    cout << "Game saved with name : " << gameSavedName << endl;
                    cout << SEPARATION;
                }
                Chessboard *chessBoard = Chessboard::GetInstance();
                int i = getSquareClickedIndex(event.mouseButton.x, event.mouseButton.y);
                if (i != -1 && i < boardSquares.size()) {
                    refresh = true;
                    pair<int, int> clickedSquare = chessBoard->ConvertOneDimensionPositionToCoordinate(i);
                    //a square is already selected
                    if (selectedSquare != make_pair(-1, -1)) {
                        //get possible moves of selected square (not clicked square)
                        possibleMovesSelectedSquare = chessBoard->GetPossibleMoves(
                                selectedSquare, false);
                        //user clicks on a possible move
                        if (std::find(possibleMovesSelectedSquare.begin(), possibleMovesSelectedSquare.end(),
                                      clickedSquare) != possibleMovesSelectedSquare.end()) {
                            GameController::GetInstance()->MakeMove(make_pair(selectedSquare, clickedSquare));
                            selectedSquare = make_pair(-1, -1);
                        } else {
                            selectNewSquare = true;
                        }
                    } else {
                        selectNewSquare = true;
                    }
                    if (selectNewSquare) {
                        //set selected square
                        selectedSquare = clickedSquare;
                        //get possible moves of selected square
                        possibleMovesSelectedSquare = chessBoard->GetPossibleMoves(
                                selectedSquare, false);
                    }
                }
                if (refresh) {
                    refresh = false;
                    GameStatus s = GameController::GetInstance()->GetGameStatus();
                    if (s == GameStatus::GoesOn) {
                        displayGameIn(*window, true);
                    } else {
                        interfaceInitialisationWithStatus(s);
                        displayGameIn(*window, false);
                    }
                }
            }
        }
    }
}

void View::interfaceInitialisation(int step) {
    deleteButtonElements();
    deleteInterfaceElements();
    deleteTextElements();
    Point2I p1;
    Point2I p2;
    sf::Vector2u v;
    GraphicElement img;
    string gameModeImg, winner;
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


            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "games/game-empty.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 225);
            interface[interface.size() - 1]->setPosition(p1);

            texts.push_back(new sf::Text("1", font, 26));
            texts[texts.size() - 1]->setFillColor(sf::Color(21, 215, 152));
            texts[texts.size() - 1]->setPosition(585, 439);

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
            cout << "ok3" << endl;
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

            //add game mode to interface
            gameModeImg = "2-players.png";
            if (GameController::GetInstance()->GetGameMode() == GameMode::AI) {
                gameModeImg = "player-vs-bot.png";
            }
            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + gameModeImg));
            interface[interface.size() - 1]->setPosition(Point2I(815, 0));

            //add to texts turn count
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "turn-count.png"));
            interface[interface.size() - 1]->setPosition(Point2I(0, 0));

            texts.push_back(new sf::Text("", font, 30));
            texts[texts.size() - 1]->setFont(font);
            texts[texts.size() - 1]->setCharacterSize(28);
            texts[texts.size() - 1]->setString(to_string(GameController::GetInstance()->GetShots()));
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

            interface.push_back(new GraphicElement(BUTTONS_IMG_BASE_PATH + "save-game.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y);
            p2 = Point2I(WINDOW_W / 2 + v.x / 2, WINDOW_H);
            interface[interface.size() - 1]->setPosition(p1);
            buttons.push_back(new Button(p1, p2, ButtonType::SAVE));
            break;

        case 3:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));
            winner = GameController::GetInstance()->GetGameStatus() == GameStatus::WhiteWin ? "white" : "black";
            interface.push_back(new GraphicElement(STATUS_IMG_BASE_PATH + "/win.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 300);
            interface[interface.size() - 1]->setPosition(p1);

            interface.push_back(new GraphicElement(IMG_BASE_PATH + "/current-player-" + winner + ".png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x - 50 / 2, 345);
            interface[interface.size() - 1]->setPosition(p1);
            break;

        case 4:
            interface.push_back(new GraphicElement(IMG_BASE_PATH + "home.jpeg"));
            interface.push_back(new GraphicElement(STATUS_IMG_BASE_PATH + "/pat.png"));
            v = interface[interface.size() - 1]->getSprite(0).getTexture()->getSize();
            p1 = Point2I(WINDOW_W / 2 - v.x / 2, WINDOW_H - v.y - 300);
            interface[interface.size() - 1]->setPosition(p1);
            break;

        default:
            break;
    }
}

void View::interfaceInitialisationWithStatus(GameStatus s) {
    switch (s) {
        case GameStatus::BlackWin:
        case GameStatus::WhiteWin:
            interfaceInitialisation(3);
            break;
        case GameStatus::Pat:
            interfaceInitialisation(4);
            break;
        default:
            break;
    }
}

void View::initBoardSquares() {
    deleteBoardSquares();
    int shiftY = BOARD_LEFT_TOP_CORNER_Y;
    for (int line = 0; line < 8; line++) {
        for (int col = 0; col < 8; col++) {
            int index1D = 8 * line + col;
            boardSquares.push_back(new sf::RectangleShape(sf::Vector2f(SQUARE_WIDTH - SQUARE_OUTLINE_THICKNESS * 2,
                                                                       SQUARE_HEIGHT - SQUARE_OUTLINE_THICKNESS * 2)));
            boardSquareTextures.push_back(new sf::Texture);
            boardSquares.at(index1D)->setPosition(
                    sf::Vector2f(BOARD_LEFT_TOP_CORNER_X + col * SQUARE_WIDTH + SQUARE_OUTLINE_THICKNESS,
                                 shiftY + SQUARE_OUTLINE_THICKNESS));
            boardSquares.at(index1D)->setOutlineThickness(0);
        }
        shiftY += SQUARE_HEIGHT;
    }
}

void View::displayEatenPieces(PieceColor color, sf::RenderWindow &w) {
    int shiftY = BOARD_LEFT_TOP_CORNER_Y;
    const vector<Piece *> eatenPiecesList = GameController::GetInstance()->GetEatenPieces(color);
    for (int line = 0; line < 4; line++) {
        for (int col = 0; col < 3; col++) {
            int index1D = 3 * line + col;
            if (index1D < eatenPiecesList.size()) {
                string pieceName = PIECE_NAME[eatenPiecesList[index1D]->GetType()];

                int shiftX = (color == PieceColor::WHITE) ? 0 :890;
                eatenPieces.push_back(new sf::RectangleShape(sf::Vector2f(SQUARE_WIDTH - SQUARE_OUTLINE_THICKNESS * 2,
                                                                          SQUARE_HEIGHT -
                                                                          SQUARE_OUTLINE_THICKNESS * 2)));
                eatenPiecesTextures.push_back(new sf::Texture);
                eatenPieces.at(index1D)->setPosition(
                        sf::Vector2f(shiftX + col * SQUARE_WIDTH + SQUARE_OUTLINE_THICKNESS,
                                     shiftY + SQUARE_OUTLINE_THICKNESS));
                eatenPieces.at(index1D)->setOutlineThickness(0);

                if (pieceName != PIECE_NAME[NONE]) {
                    string colorDirectory = (color == PieceColor::BLACK) ? "black" : "white";
                    if (!(eatenPiecesTextures.at(index1D)->loadFromFile(
                            IMG_BASE_PATH + "pieces/" + colorDirectory + "/" + pieceName + ".png"))) {
                        cerr << "Error loading file." << endl;
                    } else {
                        eatenPieces.at(index1D)->setTexture(eatenPiecesTextures.at(index1D));
                    }
                } else {
                    eatenPieces.at(index1D)->setFillColor(sf::Color::Transparent);
                }
                w.draw(*(eatenPieces.at(index1D)));
            }
        }
        shiftY += SQUARE_HEIGHT;
    }
}

void View::displayGameIn(sf::RenderWindow &w, bool gameGoesOn) {
    initBoardSquares();

    w.clear();

    if (gameGoesOn) {
        //display turn count
        texts[0]->setString(to_string(GameController::GetInstance()->GetShots()));

        if (GameController::GetInstance()->GetCurrentPlayer() == PieceColor::BLACK) {
            interface[4]->setSprite(
                    IMG_BASE_PATH + "current-player-black.png", 0);
        } else {
            interface[4]->setSprite(
                    IMG_BASE_PATH + "current-player-white.png", 0);
        }

        sf::Vector2 v = interface[4]->getSprite(0).getTexture()->getSize();
        Point2I p1 = Point2I(WINDOW_W / 2 - v.x / 2 + 47, 6);
        interface[4]->setPosition(p1);
    }

    //interface elements first
    int size = interface.size();
    for (int i = 0; i < size; i++) {
        interface.at(i)->draw(w);
    }

    //text elements
    size = texts.size();
    for (int i = 0; i < size; i++) {
        w.draw(*(texts.at(i)));
    }

    if (gameGoesOn) {
        //selected square and possible move squares
        int size = boardSquares.size();
        if (selectedSquare != make_pair(-1, -1)) {
            sf::RectangleShape selectedRect(sf::Vector2f(SQUARE_WIDTH - SQUARE_OUTLINE_THICKNESS * 2,
                                                         SQUARE_HEIGHT - SQUARE_OUTLINE_THICKNESS * 2));
            int shiftY = BOARD_LEFT_TOP_CORNER_Y + selectedSquare.first * SQUARE_HEIGHT;
            selectedRect.setPosition(
                    sf::Vector2f(
                            BOARD_LEFT_TOP_CORNER_X + selectedSquare.second * SQUARE_WIDTH + SQUARE_OUTLINE_THICKNESS,
                            shiftY + SQUARE_OUTLINE_THICKNESS - 2));
            selectedRect.setOutlineThickness(10);
            selectedRect.setOutlineColor(CLICKED_SQUARE_OUTLINE_COLOR);
            selectedRect.setFillColor(sf::Color::Transparent);
            w.draw(selectedRect);
        }

        for (int i = 0; i < possibleMovesSelectedSquare.size(); i++) {
            sf::RectangleShape selectedRect(sf::Vector2f(SQUARE_WIDTH - SQUARE_OUTLINE_THICKNESS * 2,
                                                         SQUARE_HEIGHT - SQUARE_OUTLINE_THICKNESS * 2));
            int shiftY = BOARD_LEFT_TOP_CORNER_Y + possibleMovesSelectedSquare[i].first * SQUARE_HEIGHT;
            selectedRect.setPosition(
                    sf::Vector2f(BOARD_LEFT_TOP_CORNER_X + possibleMovesSelectedSquare[i].second * SQUARE_WIDTH +
                                 SQUARE_OUTLINE_THICKNESS,
                                 shiftY + SQUARE_OUTLINE_THICKNESS - 2));
            selectedRect.setOutlineThickness(10);
            selectedRect.setOutlineColor(DESTINATION_SQUARE_OUTLINE_COLOR);
            selectedRect.setFillColor(sf::Color::Transparent);
            w.draw(selectedRect);
        }

        //board squares with pieces
        for (int i = 0; i < size; i++) {
            string pieceName = PIECE_NAME[Chessboard::GetInstance()->GetPiece(i)->GetType()];
            if (pieceName != PIECE_NAME[NONE]) {
                string pieceColor = PIECE_COLOR_NAME[Chessboard::GetInstance()->GetPiece(i)->GetColor()];

                if (!(boardSquareTextures.at(i)->loadFromFile(
                        IMG_BASE_PATH + "pieces/" + pieceColor + "/" + pieceName + ".png"))) {
                    cerr << "Error loading file." << endl;
                } else {
                    boardSquares.at(i)->setTexture(boardSquareTextures.at(i));
                }
            } else {
                boardSquares.at(i)->setFillColor(sf::Color::Transparent);
            }
            w.draw(*(boardSquares.at(i)));
        }

        deleteEatenPieces();
        displayEatenPieces(PieceColor::BLACK, w);
        displayEatenPieces(PieceColor::WHITE, w);
    }

    w.display();
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
        delete (boardSquareTextures.at(i));
    }
    boardSquares.clear();
    boardSquareTextures.clear();
}

void View::deleteEatenPieces() {
    int size = eatenPieces.size();
    for (int i = 0; i < size; i++) {
        delete (eatenPieces.at(i));
        delete (eatenPiecesTextures.at(i));
    }
    eatenPieces.clear();
    eatenPiecesTextures.clear();
}

void View::deleteButtonElements() {
    int size = buttons.size();
    for (int i = 0; i < size; i++) {
        delete (buttons.at(i));
    }
    buttons.clear();
}






