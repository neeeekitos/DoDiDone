/*
 * Inclusion de bibliothèques
 */
#include "TestChessboard.h"
#include "../include/model/Chessboard.h"
using namespace std;

static void test1(void)
{
    cout << "1. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Affichage du board" << endl;
    cout << *bd << endl;
    cout << "Deuxième Appel de GetInstance()" << endl;
    bd = Chessboard::GetInstance();
    cout << *bd << endl;
}

static void test2(void)
{
    cout << "2. Constructeur par défaut de  Chessboard sur le bd2" << endl;
    Chessboard  bd2();
    cout << "code de retour attendu - 1, code reçu : -" << bd2 << endl;
}

static void test3(void)
{
    cout << "3. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Parcours de toutes les pièces du board  de 0 à 63 " << endl;
    for(int i = 0;i < 64; ++i)
    {
        cout << "couleur " << bd->GetPiece(i)->GetColor() << " type " << bd->GetPiece(i)->GetType() << endl;
    }
}

static void test4(void)
{
    cout << "4. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Parcours de toutes les pièces du board on dépasse les extrêmes pour provoquer une erreur" << endl;
    for(int i = 0;i < 65; ++i)
    {
        if(i==64)
        {
            break;
            cout << "Erreur de segmentation"  << endl;
        }
        cout << "couleur " << bd->GetPiece(i)->GetColor() << " type " << bd->GetPiece(i)->GetType() << endl;
    }
}

static void test5(void)
{
    DestinationsSet dest;
    cout << "5. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de l'ensemble des mouvements possibles" << endl;
    for(int i=0;i<8;++i)
    {
        for (int j = 0; j < 8 ; ++j) {
            dest = bd->GetPossibleMoves(make_pair(i, j), false);
            for (Coordinate mv : dest) {
                cout << mv.first << "\t" << mv.second << endl;
            }
        }
    }
}

static void test6(void)
{
    DestinationsSet dest;
    cout << "6. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de l'ensemble des mouvements #gagnants# possibles" << endl;
    for(int i=0;i<8;++i)
    {
        for (int j = 0; j < 8 ; ++j) {
            dest = bd->GetPossibleMoves(make_pair(i, j), true);
            for (Coordinate mv : dest) {
                cout << mv.first << "\t" << mv.second << endl;
            }
        }
    }
}

static void test7(void)
{
    cout << "7. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de l'ensemble des boundaries Table" << endl;
    for(int i=0;i<64;++i)
    {
        cout << i << ":::" << bd->GetValueInBoundariesTable(i) << endl;
    }
}

static void test8(void)
{
    cout << "8. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de l'ensemble des mouvements valides dans les deux sens i vers j puis j vers i" << endl;
    for(int i=0;i<8;++i)
    {
        for(int j=0;j<8;++j) {
            cout << "(" << i << "," << j << ")" << ":::" << bd->IsValidMove(make_pair(make_pair(i, j), make_pair(j, i))) << "\t";
            cout << "(" << j << "," << i << ")" << ":::" << bd->IsValidMove(make_pair(make_pair(j, i), make_pair(i, j))) << endl;
        }
    }
}

static void test9(void)
{
    cout << "9. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de l'ensemble des mouvements valides dans les deux sens i vers j puis j vers i" << endl;
    for(int i=0;i<64;++i)
    {
        Coordinate c = bd->ConvertOneDimensionPositionToCoordinate(i) ;
        cout << "indice :" << i << "::: (" << c.first << "," << c.second << ")" << endl;
    }
}

static void test10(void)
{
    cout << "10. Tests fonctionnels de la classe ChessBoard" << endl;
    cout << "Appel à GetInstance() (Initialisation)" << endl;
    Chessboard * bd =  Chessboard::GetInstance();
    cout << "Récupération de la valeur dans la boundaries table" << endl;
    for(int i=0;i<64;++i)
    {
        cout << "indice :" << i << ":::" << bd->GetValueInBoundariesTable(i) << endl;
    }
}

int main(void)
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    return (EXIT_SUCCESS);
}