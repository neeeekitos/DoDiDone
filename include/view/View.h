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
     * @brief Init eaten pieces positions arrays
     * @param color
     * @param w Window where drawing elements
     */
    void displayEatenPieces(PieceColor color, sf::RenderWindow &w);

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

    /**
     * @brief Free momory for eaten pieces elements
     */
    void deleteEatenPieces();


    /**
     * @brief Window where to display game
     */
    sf::RenderWindow *window;

    /**
     * @brief Current 2D coordinates of selected square
     */
    std::pair<int, int> selectedSquare;

    /**
     * @brief List of 2D coordinates of possible move squares for current
     * selected square
     */
    DestinationsSet possibleMovesSelectedSquare;

    /**
     * @brief All images (background and button images)
     */
    std::vector<GraphicElement *> interface;

    /**
     * @brief Clickable buttons
     */
    std::vector<Button *> buttons;

    /**
     * @brief Chessboard square image containers with sometimes a piece image
     * and / or an outiline to highlight it
     */
    std::vector<sf::RectangleShape *> boardSquares;

    /**
     * @brief Eaten piece image containers
     * to display on board sides
     */
    std::vector<sf::RectangleShape *> eatenPieces;

    /**
     * @brief All board pieces images to inject into boardSquares
     */
    std::vector<sf::Texture *> boardSquareTextures;

    /**
     * @brief All etaen pieces images to inject into eatenPieces
     */
    std::vector<sf::Texture *> eatenPiecesTextures;

    /**
     * @brief Game texts
     */
    std::vector<sf::Text *> texts;

    /**
     * @brief Game font
     */
    sf::Font font;

    /**
     * @brief Singleton of View
     */
    static View *view_;

};


#endif //E_CHESS_VIEW_H
