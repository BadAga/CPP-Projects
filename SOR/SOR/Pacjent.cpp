#include "Funkcje.h"
#include "Pracownicy.h"
#include "Sala.h"
#include "Pacjent.h"

using namespace std;

Pacjent::Pacjent(string& _hzgl, string& _data_zgl, int& _nr, string& _imie, string& _nazwisko, int& _stan_zdrowia, string& _notatka)
	:numer(_nr), imie(_imie), nazwisko(_nazwisko), stan_zdrowia(_stan_zdrowia), notatka(_notatka), dokumentacja("Nie wprowadzono"),
	godzina_zgloszenia(_hzgl), data_zgloszenia(_data_zgl), godzina_rozpoczecia_pomocy(""), godzina_uzdrowienia(""), stan_w_szpitalu("Zgloszony")

{
	oblicz_zapotrzebowanie_na_personel();
	oblicz_czas_w_lozku();
}

Pacjent::~Pacjent()
{
}

void Pacjent::oblicz_zapotrzebowanie_na_personel()
{
	if (this->stan_zdrowia == 1)
	{
		potrzebne_pielegniarki = 1;
	}
	else if (this->stan_zdrowia == 2)
	{
		potrzebni_lekarze = 1;
	}
	else
	{
		potrzebne_pielegniarki = 1;
		potrzebni_lekarze = 1;
	}
}

void Pacjent::oblicz_czas_w_lozku()
{
	if (this->stan_zdrowia == 1)
	{
		czas_zajecia_lozka = 10;
	}
	else if (this->stan_zdrowia == 2)
	{
		czas_zajecia_lozka = 15;
	}
	else
	{
		czas_zajecia_lozka = 22;
	}
}

void Pacjent::oddeleguj()
{
	this->stan_w_szpitalu = "Oddelegowany";
	this->godzina_rozpoczecia_pomocy = "--:--";
	this->godzina_uzdrowienia = "--:--";
	this->potrzebne_pielegniarki = 0;
	this->potrzebni_lekarze = 0;
	this->czas_zajecia_lozka = 0;

}

void Pacjent::ustaw_koniec_pomocy()
{
	this->godzina_uzdrowienia = dodaj_minuty(this->godzina_rozpoczecia_pomocy, this->czas_zajecia_lozka);
}

void Pacjent::ustaw_koniec_pomocy(string& h)
{
	this->godzina_uzdrowienia = h;
}

int Pacjent::get_stan_zdrowia()
{
	return this->stan_zdrowia;
}

void Pacjent::ustaw_start_pomocy(string& h)
{
	this->godzina_rozpoczecia_pomocy = h;
}

void Pacjent::ustaw_stan_w_szpitalu(string nazwa)
{
	this->stan_w_szpitalu = nazwa;
}

int Pacjent::jaki_mam_numer()
{
	return this->numer;
}

void Pacjent::dodaj_dokumentacje()
{
	this->dokumentacja = "Uzupelniona";
	string nazwa_dokumentacji_pacjenta = to_string(this->numer);
	nazwa_dokumentacji_pacjenta += ('.' + this->nazwisko);
	cout << "Uzupelnij dokumentacje: " << endl;
	cout << " Wpisz dokladne dane pacjenta. By przejsc do kolejnej czesci dokumentacji wcisnij enter" << endl;
	string metryka;
	cin.ignore();
	getline(cin, metryka);
	cout << " Wpisz dokladny opis stanu pacjenta. Wcisnij enter by wygenerowac dokumentacje" << endl;
	string choroba;
	cin.ignore();
	getline(cin, choroba);
	ofstream dokumentacja_zakonczona(nazwa_dokumentacji_pacjenta);
	if (dokumentacja_zakonczona)
	{
		dokumentacja_zakonczona << *this << endl;
		dokumentacja_zakonczona << "data zgloszenia:   " << this->data_zgloszenia << "    godzina zgloszenia: " << this->godzina_zgloszenia << endl;
		dokumentacja_zakonczona << "godzina przyjecia pacjenta na SOR:   " << this->godzina_rozpoczecia_pomocy << "    godzina opuszczenia SORu: " << this->godzina_uzdrowienia << endl << endl;
		dokumentacja_zakonczona << "Szczegolowe dane pacjenta: " << endl << metryka << endl << endl;
		dokumentacja_zakonczona << "Szczegolowy opis stanu pacjenta: " << endl << choroba << endl;

	}
	dokumentacja_zakonczona.close();
	cout << "~Dokumentacje znajdziesz pod nazwa: " << nazwa_dokumentacji_pacjenta << endl;

}

ostream& operator<<(ostream& s, Pacjent& pacjent)
{
	s << pacjent.numer << ".  " << pacjent.imie << " " << pacjent.nazwisko << " " << pacjent.stan_w_szpitalu << " stan poszkodowania: " << pacjent.stan_zdrowia << " notatka: " << pacjent.notatka;
	return s;
}
