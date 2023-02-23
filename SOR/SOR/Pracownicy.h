#pragma once
#ifndef PRACOWNICY_H
#define PRACOWNICY_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct dzien
{
    string data; /**<*/
    vector<vector<string >> operacje_na_dzis; /**<Kontener skladajacy sie z nazwy, godziny rozpoczecia operacji i zakonczenia operacji*/
    vector<string> godziny_pracy;/**<Kontener skladajacy sie z godziny rozpoczecia pracy i zakonczenia pracy*/
    dzien(string& _data, vector<string> _godziny_pracy);
    dzien(string& _data);
    ~dzien();
};

class Pracownik
{
    friend class Pacjent;
    friend class Sala;
    int friend roznica_godzin(string& godz_podana, string& godz);
    const int ID; /**<Indywidualny numer kazdego pracownika*/
    const string imie, nazwisko;
protected:
    string haslo;
    vector<dzien> tydzien;
    bool dostepnosc; 
    string godz_od_ktorej_dostepny; 
    vector <int> nr_moich_pacjentow; 

public:

    Pracownik(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien>& _tydzien, bool _dostepnosc);
    Pracownik(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien>& _tydzien);
    Pracownik();
    virtual ~Pracownik();
    /**
    * @return Wartosc atrybutu'ID'
    */
    int zwroc_id();
    /**
    * @brief Metoda wirtualna 
    * W zaleznosci od typu obiektu potomnego, inaczej jest generowane domysle haslo dla pracownika
    */
    string virtual generuj_haslo() = 0;
    /**
    * @brief Ustawia atrybut 'haslo' przekazana wartoscia parametru
    * Wywolywana przy odczycie pliku z haslami oraz przy zmianie hasla przez uzytkownika
    * @param haslo- haslo do ustawienia
    */
    void ustaw_haslo(string& haslo);
    /**
    * @brief Wypisuje imie, nazwisko oraz ID pracownika
    */
    friend ostream& operator<< (ostream& s, Pracownik& pracownik);
    /**
    * @brief Zwraca wartosc atrymutu 'haslo' danego pracownika
    * Wykorzystywana do sprawdzania poprawnosci hasla- przy logowaniu przez uzytkownika
    * @return wartosc atrybutu 'haslo'
    */
    string zwroc_haslo();
    /**
    * @brief Funkcja do zmiany hasla
    * Uzytkownik proszony jest o wpisanie nowego hasla. Wprowadzone haslo jest ustawione jako nowa wartosc atrybutu 'haslo'
    */
    void zmien_haslo();
    /**
    * @brief Weryfikuje wprowadzone haslo
    * Uzytkownik proszony jest o podanie hasla, jezeli haslo jest poprawe zwracana jest wartosc true, w przeciwnym wypadku false.
    * @return powodzenie przy logowaniu
    */
    bool zaloguj();
    /**
    * @brief Metoda wirtualna
    * W zaleznosci od typu obiektu potomnego, w inny sposob jest wyswietlany grafik pracownika
    */
    void virtual wyswietl_grafik() = 0;
    /**
    * @brief Metoda wirtualna
    * W zaleznosci od typu obiektu potomnego, w inny sposob jest zmieniany grafik pracownika
    */
    void virtual zmien_grafik(string& aktualna_data) = 0;
    /**
     * @brief Metoda wirtualna
     * W zaleznosci od typu obiektu potomnego, w inny sposob jest aktualizowany pracownik
     */
    void virtual aktualizacja(string& data, string& h, string& h_uzdrowienia) = 0;
    /**
    * @brief Zwraca date pierwszego dnia tygodnia podanego w pliku "Grafik.txt"
    * @return data
    */
    string pierwszy_dzien_tygodnia();
    /**
    * @brief Funkcja sprawdza czy podana w parametrze godzina znajduje sie w zakresie godzin pracy danego pracownika
    * @param data- dzien, w ktorym sprawdzana jest godzina
    * @return h- sprawdzana godzina
    */
    bool czy_godziny_pracy(string& data, string& h);
    /**
    * @brief Funkcja sprawdza czy podana w parametrze godzina znajduje sie w zakresie godzin pracy danego pracownika
    * @return h- sprawdzana godzina
    */
    bool czy_dalej_bede_zajety(string& h);
    /**
    * @brief Ustawia atrybut Pracownik::godz_od_ktorej_dostepny wartoscia parametru przekazanego
    * @param h-godzina od ktorej bedzie pracownik dostepny
    */
    void ustaw_godzine_od_ktorej_dostepny(string& h);
};

class Lekarz :public Pracownik
{
    friend class Sala;

public:
    Lekarz();
    Lekarz(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien >& _tydzien);
    ~Lekarz();
    /**
    * @brief Generuje domyslne haslo dla obiektu typu Lekarz
    * Wywolywana przez konstruktor Lekarz::Lekarz(). Gdy w pliku "Hasla.txt" nie znajduje sie ID danego lekarza haslo wygenerowane przez ta funkcje jest haslem lekarza.
    * Haslo sklada sie ze slowa "Lekarz" i ID lekarza.
    * @return wygenerowane haslo
    */
    string virtual generuj_haslo();
    /**
    * @brief Wyswietla grafik
    * Wyswietla godziny pracy lekarza oraz zaplanowane operacja (nazwe operacji, godzine rozpoczecia i zakonczenia operacji)
    */
    void virtual wyswietl_grafik();
    /**
    * @brief Wprowadza zmiany w godzinach pracy
    * Lekarz proszony jest o wprowadzenie daty dnia, na ktory zmienia godziny pracy, oraz nowe godziny pracy.
    * Sprawdzana jest poprawnoœæ podanej daty i godziny (format, zakres tygodnia)
    */
    void virtual zmien_grafik(string& aktualna_data);
    /**
    * @brief Dodaje do konteneru z operacjami operacje
    * Mozliwe jest dodanie operacji dzien po podanej dacie; nie w ten sam dzien.
    * Nie jest mozliwe nachodzenie sie dwoch operacji na siebie.
    * @param data- data wprowadzzanych zmian
    * @param h- godzina wprowadzanych zmian
    */
    void dodaj_operacje(string& data, string& h);
    /**
    * @brief Funkcja sprawdza czy o podanej godzinie w podany dzien jest zaplanowana operacja.
    * @param data- data sprawdzanego dnia
    * @param h-sprawdzzana godzina
    * @return true jezeli o podanej godzinie w podany dzien jest zaplanowana operacja
    */
    bool czy_mam_operacje(string& data, string& h);
    /**
    * @brief Aktualizuje Lekarz::dostepnosc oraz Lekarz::godz_od_ktorej_dostepny.
    * Jezeli lekarz w podanych godzinach (zarowno godziny wyzdrowienia i przyjecia) pracuje, nie ma zaplanowanej operacji i nie leczy innego pacjenta
    * to jego Lekarz::dostepnosc jest ustawiana na 1.
    * @param data- data przyjecia pacjenta
    * @param h- godzina o ktorej pacjent wchodzi na SOR
    * @param h_uzdrowienia- godzina o ktorej pacjent wyzdrowieje
    */
    void virtual aktualizacja(string& data, string& h, string& h_uzdrowienia);
    /**
    * @return wektor o tych samych wartosciach co Lekarz::nr_moich_pacjentow.
    */
    vector <int> zwroc_moich_pacjentow();
};

class Pielegniarka : public Pracownik
{
    friend class Sala;

public:
    Pielegniarka();
    Pielegniarka(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien>& _tydzien);
    ~Pielegniarka();
    /**
    * @brief Generuje domyslne haslo dla obiektu typu Pielegniarka
    * Wywolywana przez konstruktor Pielegniarka::Pielegniarka(). Gdy w pliku "Hasla.txt" nie znajduje sie ID danego/danej pielegniarki haslo wygenerowane przez ta funkcje jest haslem pielegniarki/rza.
    * Haslo sklada sie ze slowa "Pielegniarka" i ID pielegniarka.
    * @return wygenerowane haslo
    */
    string  generuj_haslo();
    /**
    * @brief  Wyswietla grafik
    * Wyswietla godziny pracy pielegniarki wraz z datami
    */
    void virtual wyswietl_grafik();
    /**
    * @brief Wprowadza zmiany w godzinach pracy
    * Pielegniarka proszona jest o wprowadzenie daty dnia, na ktory zmienia godziny pracy, oraz nowe godziny pracy.
    * Sprawdzana jest poprawnoœæ podanej daty i godziny (format, zakres tygodnia)
    */
    void virtual zmien_grafik(string& aktualna_data);
    /**
    * @brief Aktualizuje Pielegniarka::dostepnosc oraz Pielegniarka::godz_od_ktorej_dostepny.
    * Jezeli pielegniarka w podanych godzinach (zarowno godziny wyzdrowienia i przyjecia) pracuje i nie leczy innego pacjenta
    * to jego Pielegniarka::dostepnosc jest ustawiana na 1.
    * @param data- data przyjecia pacjenta
    * @param h- godzina o ktorej pacjent wchodzi na SOR
    * @param h_uzdrowienia- godzina o ktorej pacjent wyzdrowieje
    */
    void virtual aktualizacja(string& data, string& h, string& h_uzdrowienia);

};



#endif // !PRACOWNICY_H

