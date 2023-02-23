/** @file */
#include "struktury.h"
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <vector>
#include <string>

#ifndef FUNKCJE_H
#define FUNKCJE_H

//using namespace std;

/** Funkcja najpierw sprawdza czy w wektorze przechowujacym wskazniki do poszczegolnych wierzcholkow, juz istnieje wierzcholek o podanym identyfikatorze.
* Jesli taki nie istnieje to tworzy nowy wierzcholek o przekaznym identyfikatorze.
* 
*@param wierzcholki wektor przechowujacy wskazniki do wierzcholkow
*@param ID id danego wierzcholka
*@return wskaznik wskazujacy na wierzcholek o przekazanym ID
*/
wierzcholek* pobierzWierzcholekNaPodstawieID(std::vector<wierzcholek*>& wierzcholki, int ID);

/**Funkcja koloruje wierzcholki polaczene ze wskazywanym wierzcholkiem na kolor przeciwny od koloru wierzcholka, na ktory wskazuje przekazny wskaznik.
* 
* Funkcja najpierw sprawdza czy kolor wierzcholka, na ktory wskazuje przekazany wskaznik jest rowny zero czyli szary.
* Kolor musi byc inny niz szary by moc przypisac wierzcholkom, ktore sa polaczone z wierzcholkiem, na ktory wskazuje przekazany wskaznik,
* kolor przeciwny do koloru  wierzcholka, na ktory wskazuje przekazany wskaznik.
* Nastepnie definiujemy kolor, na ktory beda kolorowane wierzcholki znajdujace sie w wektorze polaczenia.
* W kolejnym kroku wszytskie wierzcholki znajdujace sie w owym wektorze sa na ten kolor kolorowane.
* 
* @param w wskaznik wskazujacy na dany wierzcholek
*/
void pokolorujSasiednieWierzcholki(wierzcholek* w);

/**Funkcja sprawdza czy wskazywany wierzcholek jest polaczony z wierzcholkami o przeciwnym kolorze
* 
* W funkcji najpierw jest definiowany kolor jaki powinny miec wierzcholki ktore sa polaczone z wierzcholkiem, 
* na ktory wskazuje przekazany wskaznik. Nastepnie w sprawdzane sa kolory wszystkich tych wierzcholkow. 
* Jesli wszystkie kolory wiercholkow, polaczonych ze wskazywanym wierzcholkiem sa rowne 'kolorDoSasiadow' to zwracana jest wartosc true.
* @param w wskaznik wskazujacy na sprawdzany wiercholek
* @return odpowiedz czy jest dwudzielny dla wierzcholka
*/
bool czyDwudzielnyDlaWierzcholka(wierzcholek* w);

/**Funkcja sprawdza czy wszystkie wierzcholki sa poloczone z wierzcholkami o przeciwnym kolorze.
* 
* Funkcja sprawdza czy wszystkie wierzcholki w wektorze ze wskaznikami do  pokolorowanych wierzcholkow maja wartosc true,
* nadawana przez funkcje 'czyDwudzielnyDlaWierzcholka'.
* @param wierzcholkiPokolorowane wektor przechowujacy wskazniki do pokolorowanych juz wierzcholkow
*/
bool czyDwudzielny(std::vector<wierzcholek*>& wierzcholkiPokolorowane);
/**
*
*Funkcja najpierw tworzy zmienna typu string ze wskazywanej tablicy znakow, a nastepnie porownuje ja z drugim parametrem, ktory tez jest typu string.
*
* @param text wkaznik na tablice znakow bedaca parametrem uruchomienia programu
* @param s2 parametr typu string do ktorego porownujemy text
* @return wartosc true gdy s1 jest rowne s2
*/
bool porownaj(char* text, std::string s2);
#endif 