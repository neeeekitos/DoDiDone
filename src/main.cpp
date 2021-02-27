#include <iostream>
#include <unistd.h>
#include "../include/model/Chessboard.h"
#include "../include/view/View.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Chessboard c;
    View v(&c);
    v.MenuChoices();

}