/** @file */
#pragma once
#ifndef SALA_H
#define SALA_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Asortyment
{
	friend class Sala;
protected:
	string nazwa; /**<nazwa asortymentu, odczytana z pliku*/
	int oryginalna_ilosc; /**<liczba asortymentu odczytana z pliku*/
	int aktualna_ilosc; /**<aktualna ilosc asortymantu*/
public:
	Asortyment(string& _nazwa, int _ile);
	~Asortyment();
	friend ostream& operator<<(ostream& s, Asortyment& asortyment);
	/**
	* @brief Zwraca obliczona wartosc procentowego aktualnego zaopatrzenia w stosunku do oryginalnej ilosci
	* @return procent zapatrzenia
	*/
	double oblicz_poziom_proc();
	/**
	* @brief Podnosi aktualna ilosc asortymentu o przekazany parametr ile
	* @param ile- ilosc o jaka dostawac uzupelnia dany element asortymentu
	*/
	void dostawca_uzupelnij(int& ile);
	/**
	* @brief Podnosi aktualna ilosc asortymentu procentowo o parametr proc w stosunku do oryginalnej ilosci
	* @param proc- liczba rowna procentowi o jaki uzytkownik chce podniesc poziom zaopatrzenia
	*/
	void uzupelnij_hurtowo(int& proc);
	/**
	* @brief Obniza aktualna ilosc asortymentu procentowo o parametr proc w stosunku do oryginalnej ilosci
	* @param proc- liczba rowna procentowi asortymentu jaki zuzywa pacjent
	*/
	void zuzyj(int& o_ile_proc);
};

class Poczekalnia
{
	friend class Sala;
protected:
	int il_miejsc;/**<Liczba miejsc w poczekalni. Wczytywana z pliku "Asortyment.txt". Jest stala przez caly okres trwania programu*/
	int il_wolnych_miejsc;/**Liczba wolnych miejsc w poczekalni. Jest zmieniania wraz z liczba pacjentow przebywajacych w poczekalni<*/
public:
	Poczekalnia();
	~Poczekalnia();
	/**
	* @brief Ustawia "il_miejsc" i "il_wolnych_miejsc" na przekazana ilosc.
	* @param ilosc- przekazana wartosc liczbowa
	* Wywolywana tylko raz- przy odczycie pliku "Asortyment.txt".
	*/
	void ustaw_ile_miejsc(int& ilosc);
	/**
	* Zmniejsza liczbe wolnych miejsc o podana ilosc.
	* @param ilosc- przekazywana liczba rowna ilosci pacjentow dochodzacych do poczekalni
	*/
	void zajmij_miejsce(int& ilosc);
	/**
	* Zwieksza liczbe wolnych miejsc o podana ilosc.
	* @param ilosc- przekazywana liczba rowna ilosci pacjentow przechodzacych do sali
	*/
	void zwolnij_miejsce(int& ilosc);
};

class Sala
{
	friend ostream& operator<<(ostream& s, Sala& sala);
	int il_lozek; /**<Liczba lozek odczytana z pliku*/
	int il_wolnych_lozek; /**<liczba aktualnie wolnych lozek*/
	int il_zajetych_lozek; /**<liczba zajetych lozek*/
	Poczekalnia* wsk_na_poczekalnie; /**<wskaznik na obiekt typu Poczekalnia*/
	vector< shared_ptr<Lekarz>>* wskaznik_na_lekarzy; /**<wskaznik na baze lekarzy*/
	vector< shared_ptr<Pielegniarka>>* wskaznik_na_pielegniarki; /**<wskaznik na baze pielegniarek*/
	vector< shared_ptr<Asortyment>>* wskaznik_na_asortyment; /**<wskaznik na baze asortymentu*/
	vector<shared_ptr<Pacjent>>* wsk_pacjenci_dzis; /**<wskaznik na kontener z pacjentami danego dnia*/
protected:
	string stan; /**<nazwa stanu*/
	double poziom_asort;/**<procentowy poziom ogolnego zaopatrzenia Soru*/ 
	int proc_dost_personelu;/**<procent dostepnych pracownikow*/
	int il_dost_lekarzy;/**<liczba dostepnych lekarzy*/
	int il_dost_piel;/**<liczba dostepnych pielegniarek*/
public:

	Sala();
	~Sala();
	/**
	* @brief Ustawia wartosc atrybutu 'il_lozek'. 
	* Jest wywolywana przy odczycie pliku "Asortyment.txt".
	* @param _il- liczba lozek 
	*/
	void ustaw_il_lozek(int& _il);
	/**
	* @brief Ustawia wskazniki klasy Sala na obiekty na ktore wskazuja przekazane wskazniki
	* @param _na_poczekalnie- wskaznik na obiekt typu poczekalnia
	* @param _na_lekarzy- wskaznik na wektor inteligentnych wskaznikow na obiekty typu Lekarz
	* @param _na_pielegniarki- wskaznik na wektor inteligentnych wskaznikow na obiekty typu Pielegniarka
	* @param _na_asortyment- wskaznik na wektor inteligentnych wskaznikow na obiekty typu Asortyment
	*/
	void przekaz_wskazniki(Poczekalnia* _na_poczekalnie, vector< shared_ptr<Lekarz>>* _na_lekarzy,
		vector< shared_ptr<Pielegniarka>>* _na_pielegniarki, vector< shared_ptr<Asortyment>>* _na_asortyment);
	/**
	* @brief Ustawia wskaznik klasy Sala 'wsk_pacjenci_dzis' na obiekt na ktory wskazuje przekazany wskaznik
	* Na kazdy dzien tygodnia jest tworzony jeden taki wskaznik, jest on przekazywany tylko raz.
	* @param _wsk_pacjenci_dzis- wskaznik na wektor inteligentnych wskaznikow na obiekty typu Pacjent
	*/
	void przekaz_wskaznik_pacjenci(vector<shared_ptr<Pacjent>>* _wsk_pacjenci_dzis);
	/**
	* @brief Oblicza srednia wartosc procentowa zaopatrzenia sali
	* Wartosc wyliczona moze byc wieksza od 100.
	*/
	void oblicz_calosciowy_poziom_asortymentu();
	/**
	* @brief Oblicza procent dostepnych pracownikow ze wszystkich pracownikow.  
	*/
	void oblicz_poziom_personelu();
	/**
	* @brief Wylicza aktualny stan SORu.
	* Mozliwe stany to: 'PRAWIDLOWY','POPRAWNY','NIEPRAWIDLOWY','KRYTYCZNY'.
	* Do obliczenia stanu brane sa pod uwage poziom zaopatrzenia, liczbe dostepnych lekarzy i pielegniarek oraz liczbe wolnych miejsc w poczekalni i lozek na sali.
	* @return Nazwa stanu
	*/
	string wylicz_stan();
	/**
	* @brief Ustawia atrybut 'stan' jako wartosc zwracana przez wywyolana wewnatrz funkcji funkcje 'wylicz_stan()'.
	*/
	void ustaw_stan();
	/**
	* @brief Funkcja ustawia dostepnosc personelu w podanej dacie i godzinie.
	* Sprawdzane sa godziny pracy pracownika, czy nie ma zaplanowanych juz na ta godzine w grafiku wydarzen (jezeli Pracownik jest obiektem typu Lekarz)
	* Jezeli podana godzina jest w obrebach godzin pracy pracownika, a lekarz nie ma zaplanowanych operacji na ta godzine, to dostepnosc tego pracownika jest ustawiana na 1.
	* Ustawiany jest tez stan SORu poprzez wywolanie funkcji 'ustaw_stan()'.
	* Funkcja ta zostaje wywolana gdy uzytkownik w menu glownym wybierze opcje 'Jestem dyspozytorem SORu' i wpisze prawidlowa date i godzine.
	* @param _data- podana przez uzytkownika data  
	* @param _godz- podana przez uzytkownika godzina 
	*/
	void uruchom_sor(string& _godz, string& _data);
	/**
	* @brief Funkcja sprawdza za pomoca 'wsk_na_poczekalnie' czy jest miejsce w poczekalni
	* @return true jezeli jest miejsce w poczekalni
	*/
	bool czy_trzeba_oddelegowac();
	/**
	* @brief Aktualizuje dane pracownikow dla danego pacjenta.
	* Dla kazdego pracownika wskazywanego w obiekcie wskazywanym przez 'wskaznik_na_lekarzy' oraz 'wskaznik_na_pielegniarki' jest wywolywana ich metoda wirtualna 'aktualizacja(string& data, string& h, string& h_uzdrowienia)'
	* @param data- data podana przez uzytkownika po wybraniu 3 opcji w menu glownym
	* @param h- jest to godzina zgloszenia pacjenta.
	* @param h_uzdrowienia- jest to godzina o ktorej pacjent by opuscil sor gdyby mogl odrazu wejsc na SOR po zgloszeniu
	*/
	void aktualizuj(string& data, string& h, string& h_uzdrowienia);
	/**
	* @brief Sprawdza czy jest wystarczajaca liczba personelu dla pacjenta by go przyjac na sale SORu.
	* Dla kazdego pracownika wskazywanego w obiekcie wskazywanym przez 'wskaznik_na_lekarzy' oraz 'wskaznik_na_pielegniarki' sa sprawdzane godziny pracy godziny zgloszenia i godziny uzdrowienia pacjenta.
	* Dla lekarzy dodatkowo sprawdzane sa godziny operacji w grafiku. 
	* Funkcja zapobiega sytuacji, by jakikolwiek z pracownikow musial pracowac poza godzinami pracy.
	* @param data- data podana przez uzytkownika po wybraniu 3 opcji w menu glownym
	* @param h- jest to godzina zgloszenia pacjenta.
	* @param h_uzdrowienia- jest to godzina o ktorej pacjent by opuscil sor gdyby mogl odrazu wejsc na SOR po zgloszeniu
	* @param il_lek- liczba potrzebnych lekarzy
	* @param il_piel- liczba potrzebnych pielegniarek
	* @return true jezeli jest wystarczajaca liczba personelu
	*/
	bool czy_jest_wystarczajaco_personelu(string& data, string& h_zgloszenia, string& h_uzdrownienia, int& il_lek, int& il_piel);
	/**
	* @brief Umozliwia wybranie konkretnego pracownika.
	* Uzytkownikowi wyswietla sie lista dostepnych pracownikow prowadzacych wraz z ich numerami ID.
	* Dla pacjentow potrzebujacych 'pomoc standardowa' sa wyswietlane aktualnie dostepne pielegniarki, w innym przypadku sa wyswietlani lekarze.
	* Uzytkownik wprowadza ID wybranego pracownika. Nastepnie pracownikowi przypisuje sie danego pacjenta przez dodanie jego numeru do 'vector <int> nr_moich_pacjentow', 
	* oraz odpowiednie zmienienie godziny od ktorej dany pracownik bedzie znow dostepny (rownej godzinie o ktorej pacjent opusci SOR). 
	* Jezeli 'stan_pacjenta' byl rowny 3, to pielegniarka jest wybierana losowo.
	* Zmieniana jest tez dostepnosc pracownika na 0.
	* @param stan_pacjenta- stan pacjenta
	* @param h_zgloszenia- godzina zgloszenia pacjenta
	* @param godzina_wyzdrowienia- godzina o ktorej pacjent opusci sale SORu
	* @param nr_pacjenta- numer pacjenta
	*/
	void wybierz_konkretnego_prowadzacego(int stan_pacjenta, string& h_zgloszenia, string& godzina_wyzdrowienia, int nr_pacjenta);
	/**
	* @brief Losowo wybiera komplet pracownikow dla pacjenta
	* Pracownikowi przypisuje sie danego pacjenta poprzez dodanie jego numeru do 'vector <int> nr_moich_pacjentow',
	* oraz odpowiednie zmienienie godziny od ktorej dany pracownik bedzie znow dostepny (rownej godzinie o ktorej pacjent opusci SOR).
	* Zmieniana jest tez dostepnosc pracownika na 0.
	* @param stan_pacjenta- stan pacjenta
	* @param h_zgloszenia- godzina zgloszenia pacjenta
	* @param godzina_wyzdrowienia- godzina o ktorej pacjent opusci sale SORu
	* @param nr_pacjenta- numer pacjenta
	*/
	void wybierz_dowolny_komplet_pracownikow(int stan_pacjenta, string& h_zgloszenia, string& godzina_wyzdrowienia, int nr_pacjenta);
	/**
	* @brief Funkcja zmiejsza parametr wolnych lozek i zwieksza parametr zajetych lozek o ta sama ilosc
	* @param il_lozek- liczba zajmowanych lozek
	*/
	void zajmij_lozko(int il_lozek);
	/**
	* @brief Funkcja zmiejsza parametr zajetych lozek i zwieksza parametr wolnych lozek
	* @param il_lozek- liczba zwalnianych lozek
	*/
	void zwolnij_lozko(int il_lozek);
	/**
	* @brief Zmiejsza o liczbe procent atrybut 'poziom_asort'
	* Jezeli stan pacjenta jest rowny 1, to 'poziom_asort" jest zmniejszany o 2 procent
	* Jezeli stan pacjenta jest rowny 2, to 'poziom_asort" jest zmniejszany o 3 procent
	* Jezeli stan pacjenta jest rowny 3, to 'poziom_asort" jest zmniejszany o 5 procent
	* Kazdy element w wektorze wskazywanym przez 'wskaznik_na_asortyment' jest rowniez zminiejszany o ten sam procent.
	* Jezeli il_lozek jest rozna od 1 to procent o ktory zmniejszone sa dane jest mnozony przez il_lozek.
	* @param il_lozek- liczba pacjentow
	* @param stan_pacjenta- stan pacjenta
	*/
	void zuzyj_asortyment(int il_lozek, int stan_pacjenta);
	/**
	* @brief Funkcja szuka najkrotszy czas oczekiwania w poczekalni.
	* Za pomoca wskaznikow 'wskaznik_na_lekarzy' oraz 'wskaznik_na_pielegniarki' wyszukiwana jest najmniejsza roznica miedzy godzina zgloszenia pacjenta (h_zgloszenia), a godzina od ktorej pracownik jest dostepny.
	* Funkcja wyswietla informacje o dlugosci oczekiwania w poczekalni.
	* Jezeli stan poszkodowanego jest rowny 3 to wybierany jest dluzszy czas oczekiwania miedzy czasem oczekiwania na lekarza i pielegniarke.
	* Nastepnie pyta uzytkownika czy woli oddelegowac pacjenta czy poslac go do poczekalni.
	* Jezeli uzytkownik wybierze oddelegowanie, zostaje wywolana funkcja Pacjent::oddeleguj()
	* W przeciwnym razie pacjent zostaje przypisany do pracownika/-ow o najkrotszym czasie oczekiwania.
	* Pracownikowi przypisuje sie danego pacjenta poprzez dodanie jego numeru do 'vector <int> nr_moich_pacjentow',
	* oraz odpowiednie zmienienie godziny od ktorej dany pracownik bedzie znow dostepny (rownej godzinie o ktorej pacjent opusci SOR; ktora jest rowna sumie godzinie zgloszenia, czasu oczekiwania oraz czasu potrzebnego do wyleczenia).
	* Zmieniana jest tez dostepnosc pracownika na 0. 
	* @param data- data podana przez uzytkownika po wybraniu 3 opcji w menu glownym
	* @param h_zgloszenia- godzina zgloszenia pacjenta
	* @param stan_pacjenta- stan pacjenta
	* @param nr_pacjenta- numer pacjenta
	* @return wektor z dwoma stringami reprezentujacymi godziny, jeden z godzina o ktorej pacjent wejdzie na SOR, druga, z godzina o ktorej z niego wyjdzie
	*/
	vector<string> znajdz_najkrotszy_czas_oczekiwnania(string& data, string& h_zgloszenia, int stan_pacjenta, int nr_pacjenta);
	/**
	* @brief Przez 'wsk_na_poczekalnie' wywolywana jest funkcja Poczeklania::zajmij_miejsce(il)
	* @param il- liczba zajmowanych miejsc
	*/
	void zajmij_miejsce_w_poczekalni(int il);
	/**
	*  @brief Przez 'wsk_na_poczekalnie' wywolywana jest funkcja Poczeklania::zwolnij_miejsce(il)
	* @param il- liczba zwalnianych miejsc
	*/
	void zwolnij_miejsce_w_poczekalni(int il);
	/**
	* @brief Przez 'wsk_pacjenci_dzis' sprawdzany i aktualizowany jest stan pacjentow przebywajacych na sali i poczekalni
	* Wywolywana przed kazdym zgloszeniem czy wyswietlaniem stanu SORu.
	* Dla pacjentow ktorych 'stan_w_szpitalu' to "Na sali", sprawdzane jest czy parametr h, jest wiekszy od godziny o ktorej powinen opuscic SOR, jezeli tak, to jego 'stan_w_szpitalu' ustawiany jest na 'Opuscil szpital'.
	* Dla pacjentow ktorych 'stan_w_szpitalu' to "W poczekalni", sprawdzane jest czy parametr h, jest wiekszy od godziny o ktorej powinen opuscic SOR, jezeli tak, to jego 'stan_w_szpitalu' ustawiany jest na 'Opuscil szpital'.
	* Jezeli jego godzina wejscia na SOR jest mniejsza od parametru h i godzina opuszczenia Soru jest wieksza od h, to 'stan_w_szpitalu' ustawiany jest na 'Na sali'. 
	* @param h- godzina zgloszenia, przed ktorym sprawdzane sa sala i poczekalnia
	*/
	void sprawdz_pacj_na_sali_i_w_poczekalni(string& h);
	/**
	* @brief Przez 'wsk_na_poczekalnie' sprawdzany jest atrybut 'il_wolnych_miejsc'
	* @return wartosc rowna ilosci wolnych miwjsc w poczekalni
	*/
	int odczytaj_ile_miejsc_wolnych_w_poczekalni();
	/**
	* @brief Funkcja sprawdza czy ktorys z pracownikow nie skonczyl pracy
	* Wywolywana przed kazdym zgloszeniem czy wyswietlaniem stanu SORu.
	* Za pomoca wskaznikow 'wskaznik_na_lekarzy' oraz 'wskaznik_na_pielegniarki' porownywane sa godziny pracy pracownikow w danym dniu z parametrem h.
	* Jezeli pracownik skonczyl juz prace jego dostepnosc ustawiana jest na 0, a godzina od ktorej jest dostepny na --:--
	* @param data-data podana przez uzytkownika po wybraniu 3 opcji w menu glownym
	* @param h- godzina nastepnego zgloszenia wprowadzenego przez uzytkownika
	*/
	void czy_ktos_nie_skonczyl_pracy(string& data, string& h);
	/**
	* @brief Wyswietla rade dla dyspozytora, ktora poprawi stan SORu
	*/
	void rada();
	/**
	* @brief Funkcja wywolywana po wybraniu przez uzytkownika 6 opcji w menu dyspozytora.
	* Wszystkim pacjenci przebywajacy w szpitalu opuszczaj szpital; zuzywajac przy tym asortyment.
	* Zwalniane sa lozka na sali oraz miejsca w poczekalni
	*/
	void koniec_dnia();
	/**
	* @brief Podnosi procentowy poziom ogolnego zaopatrzenia Soru
	* Za pomoca wskaznika 'wskaznik_na_asortyment' dla kazdego elementu wywolywana jest funkcja Asortyment::uzupelnij_hurtowo(proc);
	* @param proc- liczba rowna procentowej mianie w zaopatrzeniu
	*/
	void uzupelnienie_hurtowe_asortymentu(int& proc);
	/**
	* @brief szykuje i zwraca szablon grafiku dla nowego pracownika
	* @return szablon grafiku
	*/
	vector<dzien> przygotuj_grafik();
	/**
	* @brief Generuje raport SORu do pliku tekstowego
	* W raporcie jest wyswietlany stan Soru, lista pacjentow przebywajacych na sorze oraz szczegolowa lista zawierajaca kazdy element zaopatrzenia
	* @param nazwa_raportu- nazwa pliku, do ktorego zostanie wygenerowany raport
	*/
	void generuj_raport(const string& nazwa_raportu);


};

#endif // !1
