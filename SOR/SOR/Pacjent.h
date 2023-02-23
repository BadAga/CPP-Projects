
#pragma once
#ifndef PACJENT_H
#define PACJENT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class Pacjent
{
	friend class Lekarz;
	friend class Pracownik;
	friend class Pielegniarka;
	friend class Sala;
	friend ostream& operator<<(ostream& s, Pacjent& pacjent);
	string friend dodaj_minuty(string& godz, int& minuty);
	int numer; /**<Jest to numer zgloszenia kazdego pacjenta. Generowany przez globalna zmienna 'licznik pacjentow'. Numery sa niepowtarzalne i zaczynaja sie od 1 */
	string  imie;/**<Podawane przy zgloszeniu przez uzytkownika */
	string nazwisko;/**<Podawane przy zgloszeniu przez uzytkownika*/
	int stan_zdrowia;/**<Podawane przy zgloszeniu przez uzytkownika. Przyjmuje wartosc od 1 do 3. Cyfry te symbolizuja rodzaje pomocy potrzebnej pacjentowi:
					 * 1.Pomoc standardowa 2.Pomoc pilna 3. Pomoc natychmiastowa
					 */
	string notatka;/**<Podawana przy zgloszeniu przez uzytkownika*/
	string dokumentacja;/**<Oznacza stan dokumentacji pacjenta. Jezeli nie zostala wygenerowana dokumentacja to atrybut ten jest ustawaiany na "Nie uzupelniono". Zmieniana przez funkcje 'void dodaj_dokumentacje()'.  */
	string godzina_zgloszenia;/**< Podawana przy zgloszeniu przez uzytkownika*/
	string data_zgloszenia;/**<Podawana przy zgloszeniu przez uzytkownika */
	string godzina_rozpoczecia_pomocy;/**<<Ustawiana za pomoca funkcji 'void ustaw_start_pomocy(string& h)'. Symbolizuje godzine zajecia lozka przez pacjenta na SORze */
	string godzina_uzdrowienia;/**<Ustawiana za pomoca funkcji 'void ustaw_koniec_pomocy()'. Symbolizuje godzine opuszczenia pacjenta sali SORu */
	string stan_w_szpitalu; /**<Jest informacja gdzie aktualnie przebywa pacjent*/

public:

	int potrzebni_lekarze;/**<Liczba potrzebnych lekarzy do wyleczenia pacjenta*/
	int potrzebne_pielegniarki;/**<Liczba pielegniarek lekarzy do wyleczenia pacjenta*/
	int czas_zajecia_lozka;/**<Czas (wyrazany w minutach) zajecia lozka na SORze; czas przebywania na SORze*/

	Pacjent(string& _hzgl, string& _data_zgl, int& _nr, string& _imie, string& _nazwisko, int& _stan_zdrowia, string& _notatka);
	~Pacjent();
	/**
	* @brief Na podstawie wpisanych przez uzytkownika danych przy zgloszeniu ustawia wartosci 'potrzebni_lekarze', 'potrzebne_pielegniarki'
	* Gdy 'stan_zdrowia' jest rowny 1 to 'potrzebni_lekarze'=0, 'potrzebne_pielegniarki'=1
	* Gdy 'stan_zdrowia' jest rowny 2 to 'potrzebni_lekarze'=1, 'potrzebne_pielegniarki'=0
	* Gdy 'stan_zdrowia' jest rowny 3 to 'potrzebni_lekarze'=1, 'potrzebne_pielegniarki'=1
	*/
	void oblicz_zapotrzebowanie_na_personel();
	/**
	* @brief Na podstawie wpisanych przez uzytkownika danych przy zgloszeniu ustawia wartosc 'czas_zajecia_lozka'
	* Gdy 'stan_zdrowia' jest rowny 1 to wartosc ustawiana jest rowna 10 (minut).
	* Gdy 'stan_zdrowia' jest rowny 2 to wartosc ustawiana jest rowna 15 (minut).
	* Gdy 'stan_zdrowia' jest rowny 3 to wartosc ustawiana jest rowna 22 (minuty).
	*/
	void oblicz_czas_w_lozku();
	/**
	* @brief Oddelegowuje pacjenta
	* Wywolywana gdy nie ma mozliwosci przyjecia pacjenta na sor ani poczekalni, lub gdy uzytkownik wybierze opcje oddeleguj zamiast poczekalni
	* Ustawia 'stan_w szpitalu' na "Oddelegowany".
	*/
	void oddeleguj();
	/**
	* @brief Automatycznie ustawia 'godzina_uzdrowienia'
	* Wywyolywana w konstruktorze, ustawia 'godzina_uzdrowienia' na --:--,
	* Gdy pacjent nie idzie do poczekalni; poprzez dodanie do 'godzina_uzdrowienia' wartosci atrybutu 'czas_zajecia_lozka';
	*/
	void ustaw_koniec_pomocy();
	/**
	* @brief Przekazana godzine ustawia jako atrybut 'godzina_uzdrowienia'
	* @param h- przekazana godzina
	*/
	void ustaw_koniec_pomocy(string& h);
	/**
	* @brief Zwraca atrybut "stan_zdrowia"
	*@return stan_zdrowia
	*/
	int get_stan_zdrowia();
	/**
	* @brief Przekazana godzine ustawia jako atrybut 'godzina_rozpoczecia_pomocy'
	* @param h- przekazana godzina
	*/
	void ustaw_start_pomocy(string& h);
	/**@brief Przekazana nazwa jest ustawiana jako atrybut "stan_w_szpitalu"
	* przekazywane nazwy to "Oddelegowany", "W poczekalni", "Na sali" oraz "Opuscil szpital"
	* @param nazwa- przekazana nazwa
	*/
	void ustaw_stan_w_szpitalu(string nazwa);
	/**
	* @brief Zwraca numer pacjenta
	* @return numer
	*/
	int jaki_mam_numer();
	/**
	* @brief Funkcja generuje dokumentacje do pliku pacjenta
	* W pierwszej kolejnosci ustawiany jest atrybut "dokumentacja" na "Uzupelniona".
	* Nastepnie uzytkownik jest proszony o odpowiedzenie na kilka pytan; stanowia one dokumentacje.
	* Skonczona dokumentacja jest generowana do pliku wraz z atrybutami pacjenta, takimi jak:
	* numer, imie, nazwisko, stan_zdrowia, notatka, godzina_zgloszenia, data_zgloszenia, godzina_rozpoczecia_pomocy, godzina_uzdrowienia.
	* Nazwa pliku jest generowana automatycznie sklada sie z numeru pacjenta oraz jego nazwiska.
	*/
	void dodaj_dokumentacje();


};

#endif