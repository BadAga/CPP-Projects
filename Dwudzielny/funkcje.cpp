/** @file */
#include "funkcje.h"


//using namespace std;

wierzcholek* pobierzWierzcholekNaPodstawieID(std::vector<wierzcholek*>& wierzcholki, int ID)
{
    for (auto element : wierzcholki)
    {
        if (element->id == ID) //jesli jest równy to modyfikujemy
        {
            return element;
        }
    }

    // wierzcholek u;

    wierzcholek* wsk = new wierzcholek();
    wsk->id = ID;
    wierzcholki.push_back(wsk);
    return wsk;
}



void pokolorujSasiednieWierzcholki(wierzcholek* w)
{
    if (w->kolor == 0)
    {
        return;//wychodzimy z funkcji bo nie wiemy na jaki kolor kolorowac
    }

    int kolor = -w->kolor;

    for (auto& element : w->polaczenia)
    {
        element->kolor = kolor;
    }
}

bool czyDwudzielnyDlaWierzcholka(wierzcholek* w)
{
    int kolorDoSasiadow = -w->kolor;
    for (auto& element : w->polaczenia)
    {
        if (element->kolor != kolorDoSasiadow)
        {
            return false;
        }
    }
    return true;
}

bool czyDwudzielny(std::vector<wierzcholek*>& wierzcholkiPokolorowane)
{
    for (auto& w : wierzcholkiPokolorowane)
    {
        if (!czyDwudzielnyDlaWierzcholka(w))
        {
            return false;
        }
    }
    return true;
}

bool porownaj(char* text, std::string s2)
{
    std::string s1 = text;//stworzymy stringa z tekstem z parametru
    return (s1.compare(s2) == 0);//int <0 s1 jest mniejsze, 0 s1 i s2 sa rowne, int>0 s1 jest wieksze
}
