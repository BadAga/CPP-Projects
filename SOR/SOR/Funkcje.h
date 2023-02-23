#pragma once
#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Pracownicy.h"
#include "Sala.h"
#include <iomanip>
#include <algorithm>

using namespace std;

/**
    * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu glownego.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 5).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_glowne();
/**
   * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu lekarza.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 4).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_lek();
/**
    * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu opcji grafik z menu lekarza.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 3).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_grafik();
/**
   * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu grafik dla pielegniarki.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 3).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_grafik_piel();
/**
   * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu dyspozytora.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 6).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_dyspozytor();
/**
    * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje menu dostawcy.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 3).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_dostawca();
/**
    * @brief Wyswietla opcje do wybrania dla uzykownika oraz zwraca wybrana opcje.
    * Wyswietlane sa opcje po wybraniu opcji 1 w menu dyspozytora.
    * Nastepnie uzytkownik proszony jest o wpisanie wybranej opcji (cyfra od 1 do 2).
    * Jezeli wpisana odpowiedz nie jest liczba lub nie jest na liscie opcji to zwracana jest wartosc 0.
    * @return Cyfra wybranej opcji lub 0
    */
int menu_zdarzenie();
/**
    * @brief Funkcja sprawdza czy przekazany lancuch znakow jest liczba
    * Jezeli kazdy znak w parametrze jest cyfra, to lancuch znakow jest liczba
    * @param str- sprawdzany lancuch znakow
    * @return true jezeli paramtetr jest liczba
    */
bool czyint(string& str);
/**
    * @brief Sprawdza czy podana godzina i data jest pozniejsza od ostatnio wprowadzonej godziny i daty do programu
    * Najpierw funkcja sprawdza dlugosc parametrow 'podana_h' i 'podana_dat' powinny miec dlugosc rowna 5.
    * Nastepnie sprawdzany jest format godziny (powinen byc: GG:MM) i daty (powinien byc DD.MM).
    * Kolejnym krokiem jest sprawdzenie ile miesiac z 'poczatek_tygodnia' ma dni, czy nie jest to miesiac luty czy grudzien.
    * Ustalane jest czy w ciagu tygodnia nastepuje inkrementacja miesiaca. Sprawdzane jest czy podana_dat znajduje sie w zakresie tygodnia.
    * N koniec ustalane jest czy ostatnia data jest mniejsza lub rowna podanej dacie i czy ostatnia godzina jest mniejsza od podanej godziny.
    * Jezeli tak jest to zwracana jest wartosc true
    * @param ostatnia_h- ostatnia wprowadzona godzina zmian w programie
    * @param ostatnia_dat- ostatnia wprowadzona data zmian w programie
    * @param podana_h- wprowadzona godzina przez uzytkownika
    * @param podana_dat- wprowadzona data przez uzytkownika
    * @param poczatek_tygodnia- podana w pliku "Grafik.txt" data pierwszego dnia w tygodniu
    * @return true jezeli podana godzina i data jest poprawna
    */ 
bool poprawnosc_godziny(string& ostatnia_h, string& ostatnia_dat, string& podana_h, string& podana_dat, string& poczatek_tygodnia);
/**
    * @brief Na podstawie daty pierwszego dnia w tygodniu inkrementuje dni
    * Wykorzystywana do odczytywania pliku "Grafik.txt".
    * Sprawdza czy wystepuje inkrementacja miesiacy oraz ile dni ma miesiac w dacie. Na tej podstawie poprawnie (zgodnie z kalendarzem) ustala date nastepnego dnia
    * @param dz- dzien wzgledem ktorego funkcja ustala date nastepnego dnia
    * @return data nastepnego dnia
    */
string inkrementuj_dzien(string& dz);
/**
    * @brief Odczytuje plik z grafikem
    * Ustala date pierwszego dnia tygodnia
    * Funkcja odczytuje dane kazdego pracownika. Jego imie, nazwisko oraz godziny pracy w kazdym dniu tygodnia. Na podstawie etykiety z tytulem pracownika (lekarz/ pielegniarka) decyduje jakiego typu ma utworzyc dynamiczny obiekt.
    * Utworzone obiekty dodaje do odpowiednich kontenerow.
    * @param nazwa_plik_personel- nazwa pliku zawierajacego prawidlowy plik z grafikiem
    * @param _lekarze- pusty kontener do przechowywania inteligentnych wskaznikow na obiekty typu Lekarz
    * @param _pielegniarki- pusty kontener do przechowywania inteligentnych wskaznikow na obiekty typu Pielegniarka
    */
void odczytaj_plik_grafik(string& nazwa_plik_personel, vector<shared_ptr<Lekarz>>& _lekarze, vector<shared_ptr<Pielegniarka>>& _pielegniarki);
/**
    * @brief Odczytuje plik z asortymentem
    * Liczba podana po "Poczekalnia:" jest ustawiana jako liczba liczba miejsc w poczkalni, a liczba po "Miejsca:" jest ustawaiana jako liczba lozek na sali Soru.
    * Kazdy wers w pliku zawiera najpierw nazwe asortymentu oraz oryginalna ilosc. Wartosci oddzielone sa przerwa.
    * Kazdy element asortymentu jest dodawany do kontenera z asortymentem.
    * @param nazwa_pliku_asortyment- nazawa pliku zawierajacego poprawny plik z asortymnetem
    * @param _asortyment- pusty kontener do przechowywania inteligentnych wskaznikow na obiekty typu Asortyment
    * @param _sala- wskaznik na obiekt typu Sala
    * @param _poczekalnia-wskaznik na obiekt typu Poczeklania
    */
void odczytaj_plik_asortyment(string& nazwa_pliku_asortyment, vector<shared_ptr<Asortyment>>& _asortyment, Sala*& _sala, Poczekalnia*& _poczekalnia);
/**
    * @brief Odczytuje plik z haslami do logowania dla pracownikow
    * Kazdy wers zawiera ID pracownika i haslo. Wartosci oddzielone przerwa. 
    * Nastepnie z pomoca wskaznikow na kontener do przechowywania inteligentnych wskaznikow na obiekty typu Lekarz i Pielegniarka zmieniane sa domyslne hasla dla pracownikow, ktorych ID jest w pliku.
    * @param nazwa_pliku_hasla- nazwa pliku zawierajacego hasla pracownikow
    * @param wsk_lekarze-wskaznik na kontener do przechowywania inteligentnych wskaznikow na obiekty typu Lekarz
    * @param wsk_pielegniarki-wskaznik na kontener do przechowywania inteligentnych wskaznikow na obiekty typu Pielegniarka
    */
void odczytaj_hasla(string& nazwa_pliku_hasla, vector<shared_ptr<Lekarz>>*& wsk_lekarze, vector<shared_ptr<Pielegniarka>>*& wsk_pielegniarki);
/**
    * @brief Sprawdza format godziny
    * W pierwszej kolejnosci sprawdzana jest dlugosc przekazanego lancucha znakow. Jezeli jest inna niz 5 zwracana jest wartosc false.
    * Nastpnie sprawdzany jest format godziny, ktory powinien byc GG:MM .
    * Pierwsze dwa miejsca sa dla liczby reprezentujacej godzine, ostatnie dwa dla minut, pomiedzy nimi powinien znajdowac sie dwukropek.
    * @param h- sprawdzany lancuch znakow
    * @return true jezeli podany lancuch spelnia warrunki godziny
    */
bool sprawdz_format_godziny(string& h);
/**
    * @brief Sprawdza format daty
    * W pierwszej kolejnosci sprawdzana jest dlugosc przekazanego lancucha znakow. Jezeli jest inna niz 5 zwracana jest wartosc false.
    * Nastpnie sprawdzany jest format daty, ktory powinien byc DD.MM .
    * Pierwsze dwa miejsca sa dla liczby reprezentujacej dzien, ostatnie dwa dla miesiaca, pomiedzy nimi powinna znajdowac sie kropka.
    * @param data- sprawdzany lancuch znakow
    * @return true jezeli podany lancuch spelnia warrunki daty
    */
bool sprawdz_format_daty(string& data);
/**
    * @brief Dodaje podana liczbe minut do przekazanej godziny
    * @param godz- godzina
    * @param minuty- liczba minut do dodania
    * @return zmieniona godzine
    */
string dodaj_minuty(string& godz, int& minuty);
/**
    * @brief Oblicza roznice (w minutach) miedzy dwiema godzinami.
    * Wykorzystywana do oblczenia najkrotszego czasu oczekiwania w poczekalni. 
    * Jezeli godz_podana jest wieksza badz rowna niz godzif to zwraca jest wartosc 0.
    * W przeciwnym wypadku zwraca jest roznica minut miedzy godzif i godz_podana
    * @param godz_podana- odjemna (godzina przyjecia pacjenta)
    * @param godzif- godzina wzgledem ktorej sprawdzana jest roznica (godzina od ktorej pracownik jest dostepny)
    * @return liczba minut
    */
int roznica_godzin(string& godz_podana, string& godzif);

#endif 
