
#include <iostream>
#include <string>
#include "LinkedList.h";
#include <vld.h> //do wyciekow pamieci
using namespace std;

//to do:
//zwracanie aktualnej liczby elementów ---zrobione
//dodawanie elementu na końcu --->zrobione
//dodawanie w dowolnym miejscu listy --->zrobione
//usuwanie wskazanego elementu--->działa

//to do:
//wyszukiwanie elementu---> zrobione jeszcze tylko find_all
//dostęp do elementów listy przy pomocy operatora [] ---> nie działa poza zakresem
//sortowanie


int main()
{
   
    int typ=4; //1=int 2==float 3==double 4==string
    switch (typ)
    {
        case 1:
        {
            cout << "========================== typ int ==========================" << endl;
            LinkedList<int> inty1;
            cout << "Wyswietlanie pustej listy" << endl;
            inty1.display_list();
            cout << "========================== wstawianie" << endl;
            cout << "Wstawianie od tylu wartosci, kolejno 1,2,3,4,5" << endl;
            inty1.push_back(1);
            inty1.push_back(2);
            inty1.push_back(3);
            inty1.push_back(4);
            inty1.push_back(5);
            inty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu. (W wezel o indeksie 2 wstawie wartosc 100)" << endl;
            inty1.insert_after(100, 1); //o indeksie 2 czyli za wezlem o indeksie 1
            inty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie 20 sprobuje wstawic wartosc 200)" << endl;
            inty1.insert_after(200, 19);
            inty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie -4 sprobuje wstawic wartosc 300)" << endl;
            inty1.insert_after(300, -3);
            inty1.display_list();
            cout << "=========================================== zwracanie aktualnej liczby elementow i usuwanie wszytskich elementow" << endl;
            cout << "aktualna liczba elementow to: " << inty1.size() << endl;
            cout << "teraz lista zostanie wyczyszczona" << endl;
            inty1.clear();
            cout << "aktualna liczba elementow po wyczyszczeniu to: " << inty1.size() << endl;
            cout << "=========================================== kopiowanie" << endl;
            cout << "utworze nowa inna liste (lista2) i wstawie do niej wartosci 10,11,12,13,14,15" << endl;
            LinkedList<int> inty2;
            inty2.push_back(10);
            inty2.push_back(11);
            inty2.push_back(12);
            inty2.push_back(13);
            inty2.push_back(14);
            inty2.push_back(15);
            cout << "lista2 wyglada tak: " << endl;
            inty2.display_list();
            cout<<"teraz skopiuje do pierwszej listy (lista1) liste2)"<<endl;
            inty1.copy(inty2);
            cout << "lista1 wyglada tak:" << endl;
            inty1.display_list();
            cout << "============================================ usuwanie wybranego elementu. (usune element na pozycji 3 czyli o indeksie 2)" << endl;
            inty1.delete_at(2);
            cout << "lista1 po usunieciu 3 elementu wyglada tak:" << endl;
            inty1.display_list();
            cout << "teraz z listy1 sprobuje usunac element 17:" << endl;
            inty1.delete_at(16);
            cout << "============================================ dostep do elementu przez []" << endl;
            cout << "chce wyswietlic 3 element listy 1" << endl;
            cout << inty1[2] << endl;
            cout << "============================================ wyszukiwanie elementu" << endl;
            cout << "w liscie1 sprobujemy znalezc element ktora wartosc jest rowna 10" << endl;
            inty1.search(10);
            cout << "czy taki element istnieje w liście?:" << inty1.search(10) << endl;
            cout << "czy istnieje elementy ktorego wartosc jest rowna 36:  "  << endl;
            inty1.search(36);

        }break;
        case 2:
        {
            cout << "========================== typ float ==========================" << endl;
            LinkedList<float> floaty1;
            cout << "Wyswietlanie pustej listy" << endl;
            floaty1.display_list();
            cout << "========================== wstawianie" << endl;
            cout << "Wstawianie od tylu wartosci, kolejno 1.11,2.11,3.11,4.11,5.11" << endl;
            floaty1.push_back(1.11);
            floaty1.push_back(2.11);
            floaty1.push_back(3.11);
            floaty1.push_back(4.11);
            floaty1.push_back(5.11);
            floaty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu. (W wezel o indeksie 2 wstawie wartosc 100.11)" << endl;
            floaty1.insert_after(100.11, 1); //o indeksie 2 czyli za wezlem o indeksie 1
            floaty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie 20 sprobuje wstawic wartosc 200.11)" << endl;
            floaty1.insert_after(200.11, 19);
            floaty1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie -4 sprobuje wstawic wartosc 300.11)" << endl;
            floaty1.insert_after(300.11, -3);
            floaty1.display_list();
            cout << "=========================================== zwracanie aktualnej liczby elementow i usuwanie wszytskich elementow" << endl;
            cout << "aktualna liczba elementow to: " << floaty1.size() << endl;
            cout << "teraz lista zostanie wyczyszczona" << endl;
            floaty1.clear();
            cout << "aktualna liczba elementow po wyczyszczeniu to: " << floaty1.size() << endl;
            cout << "=========================================== kopiowanie" << endl;
            cout << "utworze nowa inna liste (lista2) i wstawie do niej wartosci 10.22, 11.22, 12.22, 13.22, 14.22, 15.22" << endl;
            LinkedList<float> floaty2;
            floaty2.push_back(10.22);
            floaty2.push_back(11.22);
            floaty2.push_back(12.22);
            floaty2.push_back(13.22);
            floaty2.push_back(14.22);
            floaty2.push_back(15.22);
            cout << "lista2 wyglada tak: " << endl;
            floaty2.display_list();
            cout << "teraz skopiuje do pierwszej listy (lista1) liste2)" << endl;
            floaty1.copy(floaty2);
            cout << "lista1 wyglada tak:" << endl;
            floaty1.display_list();
            cout << "============================================ usuwanie wybranego elementu. (usune element na pozycji 3 czyli o indeksie 2)" << endl;
            floaty1.delete_at(2);
            cout << "lista1 po usunieciu 3 elementu wyglada tak:" << endl;
            floaty1.display_list();
            cout << "teraz z listy1 sprobuje usunac element 17:" << endl;
            floaty1.delete_at(16);
            cout << "============================================ dostep do elementu przez []" << endl;
            cout << "chce wyswietlic 3 element listy 1" << endl;
            cout << floaty1[2] << endl;
            cout << "============================================ wyszukiwanie elementu" << endl;
            cout << "w liscie1 sprobujemy znalezc element ktora wartosc jest rowna 10.22" << endl;
            floaty1.search(10.22);
            cout << "czy taki element istnieje w liscie?: " << floaty1.search(10.22) << endl;
            cout << "czy istnieje elementy ktorego wartosc jest rowna 36:  " << endl;
            floaty1.search(101.1);
        }break;
        case 3:
        {
            cout << "========================== typ double ==========================" << endl;
            LinkedList<double> double1;
            cout << "Wyswietlanie pustej listy" << endl;
            double1.display_list();
            cout << "========================== wstawianie" << endl;
            cout << "Wstawianie od tylu wartosci, kolejno 1.11,2.11,3.11,4.11,5.11" << endl;
            double1.push_back(1.11);
            double1.push_back(2.11);
            double1.push_back(3.11);
            double1.push_back(4.11);
            double1.push_back(5.11);
            double1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu. (W wezel o indeksie 2 wstawie wartosc 100.11)" << endl;
            double1.insert_after(100.11, 1); //o indeksie 2 czyli za wezlem o indeksie 1
            double1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie 20 sprobuje wstawic wartosc 200.11)" << endl;
            double1.insert_after(200.11, 19);
            double1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie -4 sprobuje wstawic wartosc 300.11)" << endl;
            double1.insert_after(300.11, -3);
            double1.display_list();
            cout << "=========================================== zwracanie aktualnej liczby elementow i usuwanie wszytskich elementow" << endl;
            cout << "aktualna liczba elementow to: " << double1.size() << endl;
            cout << "teraz lista zostanie wyczyszczona" << endl;
            double1.clear();
            cout << "aktualna liczba elementow po wyczyszczeniu to: " << double1.size() << endl;
            cout << "=========================================== kopiowanie" << endl;
            cout << "utworze nowa inna liste (lista2) i wstawie do niej wartosci 10.22, 11.22, 12.22, 13.22, 14.22, 15.22" << endl;
            LinkedList<double> double2;
            double2.push_back(10.22);
            double2.push_back(11.22);
            double2.push_back(12.22);
            double2.push_back(13.22);
            double2.push_back(14.22);
            double2.push_back(15.22);
            cout << "lista2 wyglada tak: " << endl;
            double2.display_list();
            cout << "teraz skopiuje do pierwszej listy (lista1) liste2)" << endl;
            double1.copy(double2);
            cout << "lista1 wyglada tak:" << endl;
            double1.display_list();
            cout << "============================================ usuwanie wybranego elementu. (usune element na pozycji 3 czyli o indeksie 2)" << endl;
            double1.delete_at(2);
            cout << "lista1 po usunieciu 3 elementu wyglada tak:" << endl;
            double1.display_list();
            cout << "teraz z listy1 sprobuje usunac element 17:" << endl;
            double1.delete_at(16);
            cout << "============================================ dostep do elementu przez []" << endl;
            cout << "chce wyswietlic 3 element listy 1" << endl;
            cout << double1[2] << endl;
            cout << "============================================ wyszukiwanie elementu" << endl;
            cout << "w liscie1 sprobujemy znalezc element ktora wartosc jest rowna 10.22" << endl;
            double1.search(10.22);
            cout << "czy taki element istnieje w liscie?: " << double1.search(10.22) << endl;
            cout << "czy istnieje elementy ktorego wartosc jest rowna 36:  " << endl;
            double1.search(101.1);
        }break;
        case 4:
        {
            cout << "========================== typ string ==========================" << endl;
            LinkedList<string> stringi1;
            cout << "Wyswietlanie pustej listy" << endl;
            stringi1.display_list();
            cout << "========================== wstawianie" << endl;
            cout << "Wstawianie od tylu wartosci, kolejno raz, dwa, trzy, cztery, piec" << endl;
            stringi1.push_back("raz");
            stringi1.push_back("dwa");
            stringi1.push_back("trzy");
            stringi1.push_back("cztery");
            stringi1.push_back("piec");
            stringi1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu. (W wezel o indeksie 2 wstawie wartosc 'agnieszka')" << endl;
            stringi1.insert_after("agnieszka", 1); //o indeksie 2 czyli za wezlem o indeksie 1
            stringi1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie 20 sprobuje wstawic wartosc 'dawid')" << endl;
            stringi1.insert_after("dawid", 19);
            stringi1.display_list();
            cout << "Wstawianie wartosci w dowolnym miejscu cd. (W wezel o indeksie -4 sprobuje wstawic wartosc 'dawid')" << endl;
            stringi1.insert_after("dawid", -3);
            stringi1.display_list();
            cout << "=========================================== zwracanie aktualnej liczby elementow i usuwanie wszytskich elementow" << endl;
            cout << "aktualna liczba elementow to: " << stringi1.size() << endl;
            cout << "teraz lista zostanie wyczyszczona" << endl;
            stringi1.clear();
            cout << "aktualna liczba elementow po wyczyszczeniu to: " << stringi1.size() << endl;
            cout << "=========================================== kopiowanie" << endl;
            cout << "utworze nowa inna liste (lista2) i wstawie do niej wartosci 'ala', 'ma', 'kota', 'i', 'malego', 'psa'" << endl;
            LinkedList<string> stringi2;
            stringi2.push_back("ala");
            stringi2.push_back("ma");
            stringi2.push_back("kota");
            stringi2.push_back("i");
            stringi2.push_back("malego");
            stringi2.push_back("psa");
            cout << "lista2 wyglada tak: " << endl;
            stringi2.display_list();
            cout << "teraz skopiuje do pierwszej listy (lista1) liste2)" << endl;
            stringi1.copy(stringi2);
            cout << "lista1 wyglada tak:" << endl;
            stringi1.display_list();
            cout << "============================================ usuwanie wybranego elementu. (usune element na pozycji 3 czyli o indeksie 2)" << endl;
            stringi1.delete_at(2);
            cout << "lista1 po usunieciu 3 elementu wyglada tak:" << endl;
            stringi1.display_list();
            cout << "teraz z listy1 sprobuje usunac element 17:" << endl;
            stringi1.delete_at(16);
            cout << "============================================ dostep do elementu przez []" << endl;
            cout << "chce wyswietlic 3 element listy 1" << endl;
            cout << stringi1[2] << endl;
            cout << "============================================ wyszukiwanie elementu" << endl;
            cout << "w liscie1 sprobujemy znalezc element ktora wartosc jest rowna 'psa'" << endl;
            stringi1.search("psa");
            cout << "czy taki element istnieje w liscie?: " << stringi1.search("psa") << endl;
            cout << "czy istnieje elementy ktorego wartosc jest rowna 'papuge':  " << endl;
            stringi1.search("papuge");
        }break;
        default:
        {
        cout << "Zaincjiuj zmienna typ 1,2,3 lub4. 1=int 2==float 3==double 4==string" << endl;
        }break;
    }
    
};

