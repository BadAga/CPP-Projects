/** @file */
#include <vector>
#ifndef STRUKTURY_H
#define STRUKTURY_H
//using namespace std;

/**Struktura opisujaca kazdy wczytany wierzcholek
*@param id przechowuje identyfikator wierzcholka
*@param kolor to kolor danego weierzcholka, przyjmuje wartosc 0 dla koloru szarego, 1 dla czerwonego i -1 dla niebieskiego
*@param polaczenia wektor przechowujacy wskazniki do wierzcholkow, z ktorymi dany wierzcholek jest polaczony
*/
struct wierzcholek
{
    int id;
    int kolor; //0 szary 1 czerwony -1 niebieski
    std::vector<wierzcholek*> polaczenia; //wektor przechowywuj¹cy id wierzcholkow z którymi dany wierzcholek jest polaczony
};

#endif