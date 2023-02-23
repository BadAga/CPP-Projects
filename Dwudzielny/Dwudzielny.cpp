/** @file */
#include "funkcje.h"

//using namespace std;

int main(int iloscParametrow, char* parametry[])
{
   
    if (iloscParametrow == 1) //kiedy żadne parametry nie są podane(czyli np przy uruchomieniu bez podania parametrow) wyswietla sie instrukcja 
    {
        std::cout << "Uruchom program z parametrem -h aby dowiedziec sie wiecej o poprawnej liscie parametrow" << std::endl;
        return 0;
    }
    int indexParametru = 1;
    std::string nazwaPlikuWejsciowego;
    std::string nazwaPlikuWyjsciowego;

    // odczytuj dopoki istnieja te parametry
    while (indexParametru < iloscParametrow)
    {
               //teraz indexParametru=1
        if (porownaj(parametry[indexParametru], "-h"))//jeśli funkcja wywalila true
        {
            std::cout << "Parametry uruchomienia programu:" << std::endl;
            std::cout << "-h pomoc" << std::endl;
            std::cout << "-i plik wejsciowy" << std::endl;
            std::cout << "-o plik wyjsciowy" << std::endl;
            return 0;
        }
        else if (porownaj(parametry[indexParametru], "-i"))//jesli true
        {
            //teraz indexParametru=2
            indexParametru++; //inkrementujemy bo sprawdzamy kolejny paramtr, który jest na indeksie o 1 dalej
            if (indexParametru < iloscParametrow)
            {
                nazwaPlikuWejsciowego = parametry[indexParametru];
                indexParametru++;
            }
            else
            {
                std::cout << "niewlasciwa lista parametrow" << std::endl;
                std::cout << "Uruchom program z parametrem -h aby dowiedziec sie wiecej o poprawnej liscie parametrow" << std::endl;
                return 0;
            }
        }
        else if (porownaj(parametry[indexParametru], "-o"))//jeśli napisy sa rowne
        {
            indexParametru++;
            //teraz indexParametru=4
            if (indexParametru < iloscParametrow)
            {
                nazwaPlikuWyjsciowego = parametry[indexParametru];
                indexParametru++;
            }
            else
            {
                std::cout << "niewlasciwa lista parametrow" << std::endl;
                std::cout << "Uruchom program z parametrem -h aby dowiedziec sie wiecej o poprawnej liscie parametrow" << std::endl;
                return 0;
            }
        }
        else //jeśli parametr nie pasuje do żadnych wcześniej sprawdzanych
        {
            std::cout << "niewlasciwa lista parametrow" << std::endl;
            std::cout << "Uruchom program z parametrem -h aby dowiedziec sie wiecej o poprawnej liscie parametrow" << std::endl;
            return 0;
        }
    }

    // std::cout << nazwaPlikuWejsciowego << " " << nazwaPlikuWyjsciowego << std::endl;

    std::vector <wierzcholek*> wierzcholki;
    std::vector <wierzcholek*> wierzcholkiPokolorowane;

    int poczatekKrawedzi;
    int koniecKrawedzi;

    //ifstream plikzgrafem(nazwaPlikuWejsciowego);
    //ofstream plikWyjsciowy(nazwaPlikuWyjsciowego);

    std::ifstream plikzgrafem(nazwaPlikuWejsciowego);
    std::ofstream plikWyjsciowy(nazwaPlikuWyjsciowego);
    if (plikzgrafem.good() == false)
    {
        std::cout << "Pilk nie istnieje lub nie do odczytu.";
        return 0;
    }

    while (plikzgrafem >> poczatekKrawedzi >> koniecKrawedzi)
    {
        plikWyjsciowy << poczatekKrawedzi << " " << koniecKrawedzi << std::endl; //od razu sobie zapisujemy do pliku wyjściowego nasz graf by to od razu zrobić
        wierzcholek* w1 = pobierzWierzcholekNaPodstawieID(wierzcholki, poczatekKrawedzi);
        wierzcholek* w2 = pobierzWierzcholekNaPodstawieID(wierzcholki, koniecKrawedzi);
        w1->kolor = 0;
        w2->kolor = 0;

        w1->polaczenia.push_back(w2);
        w2->polaczenia.push_back(w1);

    }
   

    plikzgrafem.close();

    if (wierzcholki.size() > 0)
    {
        wierzcholki[0]->kolor = 1;
        wierzcholkiPokolorowane.push_back(wierzcholki[0]);
        wierzcholki.erase(wierzcholki.begin());
    }


    while (wierzcholki.size() > 0)
    {
        for (auto& w : wierzcholkiPokolorowane)
        {
            pokolorujSasiednieWierzcholki(w);
        }
        for (int i = 0; i < wierzcholki.size(); i++)
        {
            if (wierzcholki[i]->kolor != 0)
            {
                wierzcholkiPokolorowane.push_back(wierzcholki[i]);
                wierzcholki.erase(wierzcholki.begin() + i);//usuwamy ity wierzcholek
            }
        }
    }

    if (czyDwudzielny(wierzcholkiPokolorowane))
    {
        plikWyjsciowy << "graf dwudzielny" << std::endl;

        plikWyjsciowy << "wierzcholki z pierwszej grupy (czerwone) to:" << std::endl;
        for (auto& w : wierzcholkiPokolorowane)
        {
            if (w->kolor == 1)
            {
                plikWyjsciowy << w->id << " ";
            }
        }
        plikWyjsciowy << std::endl;
        plikWyjsciowy << "wierzcholki z drugiej grupy (niebieskie) to:" << std::endl;
        for (auto& w : wierzcholkiPokolorowane)
        {
            if (w->kolor == -1)
            {
                plikWyjsciowy << w->id << " ";
            }
        }
        plikWyjsciowy << std::endl;
    }
    else
    {
        plikWyjsciowy << "graf nie jest dwudzielny" << std::endl;
    }

    plikWyjsciowy.close();
    for (int i = 0; i < wierzcholkiPokolorowane.size(); i++)
    {
        delete wierzcholkiPokolorowane[i];
    }

    return 0;
}