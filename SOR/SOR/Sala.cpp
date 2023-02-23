/** @file */
#include "Pracownicy.h"
#include "Pacjent.h"
#include "Sala.h"
#include "Funkcje.h"

using namespace std;

//---------------------------------------------------------------------ASORTYMENT------------------------------------------------------------------------------


Asortyment::Asortyment(string& _nazwa, int _ile) :nazwa(_nazwa), oryginalna_ilosc(_ile), aktualna_ilosc(_ile) {}

Asortyment::~Asortyment() {}

double Asortyment::oblicz_poziom_proc()
{
	return ((double)aktualna_ilosc / (double)oryginalna_ilosc) * 100.0;
}

void Asortyment::dostawca_uzupelnij(int& ile)
{
	this->aktualna_ilosc += ile;
}

void Asortyment::uzupelnij_hurtowo(int& proc)
{
	int ilosc_dodaj = oryginalna_ilosc * proc * 0.01;
	this->aktualna_ilosc += ilosc_dodaj;
}

void Asortyment::zuzyj(int& o_ile_proc)
{
	int il = this->oryginalna_ilosc * o_ile_proc * 0.01;
	this->aktualna_ilosc -= il;
}



//---------------------------------------------------------------------SALA--------------------------------------------------------------------------------------


Sala::Sala() : il_lozek(0), il_wolnych_lozek(0), il_zajetych_lozek(0), stan(""), poziom_asort(0.0), proc_dost_personelu(0), il_dost_lekarzy(0), il_dost_piel(0)
{
	this->wsk_na_poczekalnie = nullptr;
	this->wskaznik_na_asortyment = nullptr;
	this->wskaznik_na_lekarzy = nullptr;
	this->wskaznik_na_pielegniarki = nullptr;
	this->wsk_pacjenci_dzis = nullptr;
}

Sala::~Sala()
{
	this->wsk_na_poczekalnie = nullptr;
	this->wskaznik_na_asortyment = nullptr;
	this->wskaznik_na_lekarzy = nullptr;
	this->wskaznik_na_pielegniarki = nullptr;
	this->wsk_pacjenci_dzis = nullptr;
}

void Sala::ustaw_il_lozek(int& _il)
{
	this->il_lozek = _il;
	this->il_wolnych_lozek = _il;
	this->il_zajetych_lozek = 0;
}

void Sala::przekaz_wskazniki(Poczekalnia* _na_poczekalnie, vector<shared_ptr<Lekarz>>* _na_lekarzy, vector<shared_ptr<Pielegniarka>>* _na_pielegniarki, vector<shared_ptr<Asortyment>>* _na_asortyment)
{
	this->wsk_na_poczekalnie = _na_poczekalnie;
	this->wskaznik_na_asortyment = _na_asortyment;
	this->wskaznik_na_lekarzy = _na_lekarzy;
	this->wskaznik_na_pielegniarki = _na_pielegniarki;
}

void Sala::przekaz_wskaznik_pacjenci(vector<shared_ptr<Pacjent>>* _wsk_pacjenci_dzis)
{
	this->wsk_pacjenci_dzis = _wsk_pacjenci_dzis;
}

void Sala::oblicz_calosciowy_poziom_asortymentu()
{
	double suma = 0.0;
	int il = 0;
	for (auto& elem : *wskaznik_na_asortyment)
	{
		il++;
		suma += elem->oblicz_poziom_proc();
	}
	this->poziom_asort = (suma / (double)il);
}

void Sala::oblicz_poziom_personelu()
{
	double suma = 0.0, licznik = 0.0;
	int suma_lek = 0, suma_piel = 0;
	for (auto& lekarz : *wskaznik_na_lekarzy)
	{
		licznik += 1.0;
		if (lekarz->dostepnosc == 1)
		{
			suma += 1.0;
			suma_lek++;
		}
	}
	this->il_dost_lekarzy = suma_lek;
	for (auto& pielegniarka : *wskaznik_na_pielegniarki)
	{
		licznik += 1.0;
		if (pielegniarka->dostepnosc == 1)
		{
			suma += 1.0;
			suma_piel++;
		}
	}
	this->il_dost_piel = suma_piel;
	this->proc_dost_personelu = (suma / licznik) * 100.0;

}

string Sala::wylicz_stan()
{
	oblicz_poziom_personelu();
	int suma = 0;
	if (poziom_asort > 80.0) { suma += 10; }
	else if (poziom_asort > 60.0) { suma += 5; }
	else if (poziom_asort > 40.0) { suma += 2; }

	if (this->il_dost_lekarzy > 5) { suma += 10; }
	else if (this->il_dost_lekarzy > 3) { suma += 5; }
	else if (this->il_dost_lekarzy >= 2) { suma += 2; }

	if (this->il_dost_piel > 3) { suma += 10; }
	else if (this->il_dost_piel > 2) { suma += 5; }
	else if (this->il_dost_piel >= 1) { suma += 2; }


	double proc_pocz = ((double)(wsk_na_poczekalnie->il_wolnych_miejsc)) / ((double)(wsk_na_poczekalnie->il_miejsc)) * 100.0;
	double proc_sor = ((double)il_wolnych_lozek / (double)il_lozek) * 100.0;

	if (proc_pocz >= 80.0) { suma += 10; }
	else if (proc_pocz >= 60.0) { suma += 5; }
	else if (proc_pocz >= 40.0) { suma += 2; }

	if (proc_sor >= 80.0) { suma += 10; }
	else if (proc_sor >= 60.0) { suma += 5; }
	else if (proc_sor >= 40.0) { suma += 2; }

	if (suma >= 40) { return "PRAWIDLOWY"; }
	else if (suma >= 25) { return "POPRAWNY"; }
	else if (suma >= 14) { return "NIEPRAWIDLOWY"; }
	else { return "KRYTYCZNY"; }
}

void Sala::ustaw_stan()
{
	this->stan = wylicz_stan();
}

void Sala::uruchom_sor(string& _godz, string& _data)
{
	for (auto& lekarz : *wskaznik_na_lekarzy)
	{
		for (auto& dzien : lekarz->tydzien)
		{
			if (dzien.data == _data)
			{
				if (dzien.operacje_na_dzis.size() == 0)
				{
					if (dzien.godziny_pracy[0] <= _godz && dzien.godziny_pracy[1] > _godz)
					{
						lekarz->godz_od_ktorej_dostepny = dzien.godziny_pracy[0];
						lekarz->dostepnosc = 1;
					}
					else
					{
						lekarz->godz_od_ktorej_dostepny = dzien.godziny_pracy[0];
						lekarz->dostepnosc = 0;
					}
				}
				else
				{
					if (dzien.godziny_pracy[1] != "--:--")
					{
						bool poprawny = 1;
						for (auto& operacja : dzien.operacje_na_dzis)
						{
							if (_godz >= operacja[0] && _godz <= operacja[1]) //gdy jest w trakcie operacji
							{
								lekarz->godz_od_ktorej_dostepny = operacja[1];
								poprawny = 0;
							}
						}
						if (poprawny)
						{
							lekarz->godz_od_ktorej_dostepny = _godz;
							lekarz->dostepnosc = 1;
						}
						else
						{
							lekarz->dostepnosc = 0;
						}
					}
					else
					{
						lekarz->godz_od_ktorej_dostepny = "--:--";
						lekarz->dostepnosc = 0;
					}
				}
			}
		}
	}
	for (auto& pielegniarka : *wskaznik_na_pielegniarki)
	{
		for (auto& dzien : pielegniarka->tydzien)
		{
			if (dzien.data == _data)
			{

				if (dzien.godziny_pracy[0] <= _godz && dzien.godziny_pracy[1] > _godz)
				{
					pielegniarka->dostepnosc = 1;
					pielegniarka->godz_od_ktorej_dostepny = dzien.godziny_pracy[0];
				}
				else
				{
					pielegniarka->dostepnosc = 0;
					pielegniarka->godz_od_ktorej_dostepny = dzien.godziny_pracy[0];

				}
			}
		}
	}
	oblicz_calosciowy_poziom_asortymentu();
	oblicz_poziom_personelu();
	this->ustaw_stan();
}

bool Sala::czy_trzeba_oddelegowac()
{
	if (wsk_na_poczekalnie->il_wolnych_miejsc == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Sala::aktualizuj(string& data, string& h, string& h_uzdrowienia)
{
	for (auto& lekarz : *wskaznik_na_lekarzy)
	{
		lekarz->aktualizacja(data, h, h_uzdrowienia);
	}
	for (auto& pielegniarka : *wskaznik_na_pielegniarki)
	{
		pielegniarka->aktualizacja(data, h, h_uzdrowienia);
	}
	oblicz_poziom_personelu();
	ustaw_stan();
}

bool Sala::czy_jest_wystarczajaco_personelu(string& data, string& h_zgloszenia, string& h_uzdrownienia, int& il_lek, int& il_piel)
{
	int licznik_lek = 0, licznik_piel = 0;
	for (auto& lekarz : *wskaznik_na_lekarzy)
	{
		if (lekarz->czy_godziny_pracy(data, h_zgloszenia) && lekarz->czy_mam_operacje(data, h_zgloszenia) && lekarz->czy_dalej_bede_zajety(h_zgloszenia)
			&& lekarz->czy_godziny_pracy(data, h_uzdrownienia) && lekarz->czy_mam_operacje(data, h_uzdrownienia) && lekarz->czy_dalej_bede_zajety(h_uzdrownienia))
		{
			licznik_lek++;
		}
	}
	for (auto& pielegniarka : *wskaznik_na_pielegniarki)
	{
		if (pielegniarka->czy_godziny_pracy(data, h_zgloszenia) && pielegniarka->czy_dalej_bede_zajety(h_zgloszenia)
			&& pielegniarka->czy_godziny_pracy(data, h_uzdrownienia) && pielegniarka->czy_dalej_bede_zajety(h_uzdrownienia))
		{
			licznik_piel++;
		}
	}
	if (licznik_lek < il_lek || licznik_piel < il_piel)
	{
		return false;
	}
	else
	{
		return 1;
	}

}

void Sala::wybierz_konkretnego_prowadzacego(int stan_pacjenta, string& h_zgloszenia, string& godzina_wyzdrowienia, int nr_pacjenta)
{
	int id_lek = 0, id_piel = 0;
	vector<int> pasujacy_lek;
	vector<int> pasujace_piel;
	if (stan_pacjenta == 1 || stan_pacjenta == 3) //moze wybrac pielegniarke
	{
		for (auto& pielegniarka : *wskaznik_na_pielegniarki)
		{

			if (pielegniarka->dostepnosc == 1)
			{
				if (stan_pacjenta == 1)
				{
					cout << *pielegniarka;
				}
				pasujace_piel.push_back(id_piel);
			}
			id_piel++;
		}
		if (stan_pacjenta == 3)
		{
			for (auto& lekarz : *wskaznik_na_lekarzy)
			{
				if (lekarz->dostepnosc == 1)
				{
					cout << *lekarz;
					pasujacy_lek.push_back(id_lek);
				}
				id_lek++;
			}
		}
	}
	else //moze wybrac lekarza // bo lekarz jest wyzej w hierarchii
	{
		for (auto& lekarz : *wskaznik_na_lekarzy)
		{
			if (lekarz->dostepnosc == 1)
			{
				cout << *lekarz;
				pasujacy_lek.push_back(id_lek);
			}
			id_lek++;
		}
	}
	string wybor_pracownika;
	cin >> wybor_pracownika;
	bool jest_taki_pracownik = 0;
	while (jest_taki_pracownik == 0)
	{
		if (czyint(wybor_pracownika))
		{
			if (stan_pacjenta == 1)
			{
				for (auto& indeks : pasujace_piel)
				{
					if (indeks == stoi(wybor_pracownika) - 1)
					{
						jest_taki_pracownik = 1;
					}
				}
			}
			else
			{
				for (auto& indeks : pasujacy_lek)
				{
					if (indeks == stoi(wybor_pracownika) - 1)
					{
						jest_taki_pracownik = 1;
					}
				}
			}
		}
		else
		{
			cout << "~Wybierz poprawne ID pracownika: ";
			cin >> wybor_pracownika;
			cout << endl;
		}
		if (jest_taki_pracownik == 0)
		{
			cout << "~Wybierz poprawne ID pracownika: ";
			cin >> wybor_pracownika;
			cout << endl;
		}
	}
	int i = 0;
	if (stan_pacjenta == 1)
	{
		for (auto& piel : *wskaznik_na_pielegniarki)
		{
			i++;
			if (i == stoi(wybor_pracownika))
			{
				piel->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				piel->dostepnosc = 0;
				piel->nr_moich_pacjentow.push_back(nr_pacjenta);
			}
		}
	}
	else if (stan_pacjenta == 2)
	{
		for (auto& lek : *wskaznik_na_lekarzy)
		{
			i++;
			if (i == stoi(wybor_pracownika))
			{
				lek->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				lek->dostepnosc = 0;
				lek->nr_moich_pacjentow.push_back(nr_pacjenta);
			}
		}
	}
	else
	{
		for (auto& lek : *wskaznik_na_lekarzy)
		{
			i++;
			if (i == stoi(wybor_pracownika))
			{
				lek->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				lek->dostepnosc = 0;
				lek->nr_moich_pacjentow.push_back(nr_pacjenta);
			}
		}
		i = 0;
		for (auto& piel : *wskaznik_na_pielegniarki)
		{

			if (i == pasujace_piel[0])
			{
				piel->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				piel->dostepnosc = 0;
				piel->nr_moich_pacjentow.push_back(nr_pacjenta);
			}
			i++;
		}
	}
}

void Sala::wybierz_dowolny_komplet_pracownikow(int stan_pacjenta, string& h_zgloszenia, string& godzina_wyzdrowienia, int nr_pacjenta)
{
	bool stop = 0;
	if (stan_pacjenta == 1 || stan_pacjenta == 3)
	{
		for (auto& pielegniarka : *wskaznik_na_pielegniarki)
		{

			if (pielegniarka->dostepnosc == 1)
			{
				pielegniarka->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				pielegniarka->dostepnosc = 0;
				pielegniarka->nr_moich_pacjentow.push_back(nr_pacjenta);
				break;
			}
		}
	}
	if (stan_pacjenta == 2 || stan_pacjenta == 3)
	{
		for (auto& lekarz : *wskaznik_na_lekarzy)
		{
			if (lekarz->dostepnosc == 1)
			{
				lekarz->ustaw_godzine_od_ktorej_dostepny(godzina_wyzdrowienia);
				lekarz->dostepnosc = 0;
				lekarz->nr_moich_pacjentow.push_back(nr_pacjenta);
				break;
			}
		}
	}
}

void Sala::zajmij_lozko(int il_lozek)
{
	this->il_wolnych_lozek -= il_lozek;
	this->il_zajetych_lozek += il_lozek;
}

void Sala::zwolnij_lozko(int il_lozek)
{
	this->il_wolnych_lozek += il_lozek;
	this->il_zajetych_lozek -= il_lozek;
}

void Sala::zuzyj_asortyment(int il_lozek, int stan_pacjenta)
{
	int proc = 0;
	if (stan_pacjenta == 1)
	{
		proc = 2;
	}
	else if (stan_pacjenta == 2)
	{
		proc = 3;
	}
	else
	{
		proc = 5;
	}
	int przekaz = il_lozek * proc;
	for (auto& asortyment : *wskaznik_na_asortyment)
	{
		asortyment->zuzyj(przekaz);
	}
}

vector<string> Sala::znajdz_najkrotszy_czas_oczekiwnania(string& data, string& h_zgloszenia, int stan_pacjenta, int nr_pacjenta)
{
	vector<string> godziny;
	int czas_oczekiwania_piel = INT_MAX, czas_oczekiwania_lek = INT_MAX;
	int czas_w_lozku, indeks_piel = 0, indeks_lek = 0, i = 0;
	if (stan_pacjenta == 1) { czas_w_lozku = 10; }
	else if (stan_pacjenta == 2)
	{
		czas_w_lozku = 15;
	}
	else
	{
		czas_w_lozku = 22;
	}
	if (stan_pacjenta == 1 || stan_pacjenta == 3)
	{
		for (auto& pielegniarka : *wskaznik_na_pielegniarki)
		{
			if (pielegniarka->godz_od_ktorej_dostepny != "--:--")
			{

				string h_zak = dodaj_minuty(pielegniarka->godz_od_ktorej_dostepny, czas_w_lozku);
				string h_rozp = pielegniarka->godz_od_ktorej_dostepny;
				if (pielegniarka->czy_godziny_pracy(data, h_zak) && pielegniarka->czy_dalej_bede_zajety(h_zak))
				{
					if (czas_oczekiwania_piel >= roznica_godzin(h_zgloszenia, pielegniarka->godz_od_ktorej_dostepny))
					{
						indeks_piel = i;
						czas_oczekiwania_piel = roznica_godzin(h_zgloszenia, pielegniarka->godz_od_ktorej_dostepny);
					}
				}
			}
			i++;
		}
		i = 0;
	}
	if (stan_pacjenta == 3 || stan_pacjenta == 2)
	{
		for (auto& lekarz : *wskaznik_na_lekarzy)
		{
			if (lekarz->godz_od_ktorej_dostepny != "--:--")
			{
				string  h_zak = dodaj_minuty(lekarz->godz_od_ktorej_dostepny, czas_w_lozku);
				string h_rozp = lekarz->godz_od_ktorej_dostepny;

				if (lekarz->czy_mam_operacje(data, h_rozp) && lekarz->czy_godziny_pracy(data, h_zak) && lekarz->czy_mam_operacje(data, h_zak) && lekarz->czy_dalej_bede_zajety(h_zak))
				{
					if (czas_oczekiwania_lek >= roznica_godzin(h_zgloszenia, lekarz->godz_od_ktorej_dostepny))
					{
						indeks_lek = i;
						czas_oczekiwania_lek = roznica_godzin(h_zgloszenia, lekarz->godz_od_ktorej_dostepny);
					}
				}
			}
			i++;
		}
		i = 0;
	}
	if (stan_pacjenta == 3)
	{
		if (czas_oczekiwania_piel == czas_oczekiwania_lek)
		{
			cout << "Czas oczekiwania wynosi: " << czas_oczekiwania_piel << " minut." << endl;
		}
		else
		{
			cout << "Czas oczekiwania wynosi: " << max(czas_oczekiwania_piel, czas_oczekiwania_lek) << " minut." << endl;
		}
	}
	else if (stan_pacjenta == 1)
	{
		cout << "Czas oczekiwania wynosi: " << czas_oczekiwania_piel << " minut." << endl;
	}
	else
	{
		cout << "Czas oczekiwania wynosi: " << czas_oczekiwania_lek << " minut." << endl;
	}
	cout << "Wpisz T jesli chcesz oddelegowac pacjenta do innego szpitala, by nie musial tyle czekac: ";
	string odp;
	cin >> odp;
	if (odp == "T")
	{
		return godziny;
	}
	else
	{
		// pozajmuj personel;
		i = 0;
		if (stan_pacjenta == 1)
		{
			for (auto& pielegniarka : *wskaznik_na_pielegniarki)
			{
				if (i == indeks_piel)
				{
					string h_zak = dodaj_minuty(pielegniarka->godz_od_ktorej_dostepny, czas_w_lozku);
					string h_rozp = pielegniarka->godz_od_ktorej_dostepny;
					pielegniarka->godz_od_ktorej_dostepny = h_zak;
					pielegniarka->dostepnosc = 0;
					pielegniarka->nr_moich_pacjentow.push_back(nr_pacjenta);
					godziny.push_back(h_rozp);
					godziny.push_back(h_zak);
					return godziny;
				}
				i++;
			}
		}
		else if (stan_pacjenta == 2)
		{
			for (auto& lekarz : *wskaznik_na_lekarzy)
			{
				if (i == indeks_lek)
				{
					string h_zak = dodaj_minuty(lekarz->godz_od_ktorej_dostepny, czas_w_lozku);
					string h_rozp = lekarz->godz_od_ktorej_dostepny;
					lekarz->godz_od_ktorej_dostepny = h_zak;
					lekarz->dostepnosc = 0;
					lekarz->nr_moich_pacjentow.push_back(nr_pacjenta);
					godziny.push_back(h_rozp);
					godziny.push_back(h_zak);
					return godziny;
				}
				i++;
			}
		}
		else
		{
			string h_zak, h_rozp;
			if (max(czas_oczekiwania_piel, czas_oczekiwania_lek) == czas_oczekiwania_lek || czas_oczekiwania_lek == czas_oczekiwania_piel)
			{
				for (auto& lekarz : *wskaznik_na_lekarzy)
				{
					if (i == indeks_lek)
					{
						h_zak = dodaj_minuty(lekarz->godz_od_ktorej_dostepny, czas_w_lozku);
						h_rozp = lekarz->godz_od_ktorej_dostepny;
						lekarz->godz_od_ktorej_dostepny = h_zak;
						lekarz->dostepnosc = 0;
						lekarz->nr_moich_pacjentow.push_back(nr_pacjenta);
						godziny.push_back(h_rozp);
						godziny.push_back(h_zak);
						break;
					}
					i++;
				}
				i = 0;
				for (auto& pielegniarka : *wskaznik_na_pielegniarki)
				{
					if (i == indeks_piel)
					{
						pielegniarka->godz_od_ktorej_dostepny = h_zak;
						pielegniarka->dostepnosc = 0;
						pielegniarka->nr_moich_pacjentow.push_back(nr_pacjenta);

						return godziny;
					}
					i++;
				}
			}
			else
			{
				for (auto& pielegniarka : *wskaznik_na_pielegniarki)
				{
					if (i == indeks_piel)
					{
						h_zak = dodaj_minuty(pielegniarka->godz_od_ktorej_dostepny, czas_w_lozku);
						h_rozp = pielegniarka->godz_od_ktorej_dostepny;
						pielegniarka->godz_od_ktorej_dostepny = h_zak;
						pielegniarka->dostepnosc = 0;
						pielegniarka->nr_moich_pacjentow.push_back(nr_pacjenta);
						godziny.push_back(h_rozp);
						godziny.push_back(h_zak);
						break;
					}
					i++;
				}
				i = 0;
				for (auto& lekarz : *wskaznik_na_lekarzy)
				{
					if (i == indeks_lek)
					{
						lekarz->godz_od_ktorej_dostepny = h_zak;
						lekarz->dostepnosc = 0;
						lekarz->nr_moich_pacjentow.push_back(nr_pacjenta);

						return godziny;
					}
					i++;
				}
			}
		}
	}

}

void Sala::zajmij_miejsce_w_poczekalni(int il)
{
	this->wsk_na_poczekalnie->zajmij_miejsce(il);
}

void Sala::zwolnij_miejsce_w_poczekalni(int il)
{
	this->wsk_na_poczekalnie->zwolnij_miejsce(il);
}

void Sala::sprawdz_pacj_na_sali_i_w_poczekalni(string& h)
{
	for (auto& pacjent : *wsk_pacjenci_dzis)
	{
		if (pacjent->stan_w_szpitalu == "Na sali")
		{
			if (h >= pacjent->godzina_uzdrowienia)
			{
				pacjent->stan_w_szpitalu = "Opuscil szpital";
				this->zwolnij_lozko(1);
			}
		}
		else if (pacjent->stan_w_szpitalu == "W poczekalni")
		{
			if (h >= pacjent->godzina_rozpoczecia_pomocy && h < pacjent->godzina_uzdrowienia)
			{
				pacjent->stan_w_szpitalu = "Na sali";
				this->zwolnij_miejsce_w_poczekalni(1);
				this->zajmij_lozko(1);
				this->zuzyj_asortyment(1, pacjent->stan_zdrowia);

			}
			else if (h >= pacjent->godzina_uzdrowienia)
			{
				this->zwolnij_miejsce_w_poczekalni(1);
				this->zuzyj_asortyment(1, pacjent->stan_zdrowia);
				pacjent->stan_w_szpitalu = "Opuscil szpital";
			}
		}
	}
}

int Sala::odczytaj_ile_miejsc_wolnych_w_poczekalni()
{
	return this->wsk_na_poczekalnie->il_wolnych_miejsc;
}

void Sala::czy_ktos_nie_skonczyl_pracy(string& data, string& h)
{
	for (auto& lek : *wskaznik_na_lekarzy)
	{
		for (auto& dzien : lek->tydzien)
		{
			if (dzien.data == data)
			{
				if (dzien.godziny_pracy[0] < h && dzien.godziny_pracy[1] <= h)
				{
					lek->godz_od_ktorej_dostepny = "--:--";
					lek->dostepnosc = 0;
					break;
				}
			}

		}
	}
	for (auto& piel : *wskaznik_na_pielegniarki)
	{
		for (auto& dzien : piel->tydzien)
		{
			if (dzien.data == data)
			{
				if (dzien.godziny_pracy[0] < h && dzien.godziny_pracy[1] <= h)
				{
					piel->godz_od_ktorej_dostepny = "--:--";
					piel->dostepnosc = 0;
					break;
				}
			}

		}
	}

}

void Sala::rada()
{
	if (this->il_dost_piel <= 1)
	{
		cout << "~Koniecznie dodaj pielegniarke" << endl;
	}
	else if (this->il_dost_piel == 2)
	{
		cout << "~Dodanie pielegniarki byloby optymalne" << endl;
	}
	if (this->il_dost_lekarzy <= 1)
	{
		cout << "~Koniecznie dodaj lekarza" << endl;
	}
	else if (this->il_dost_lekarzy == 2)
	{
		cout << "~Dodanie lekarza byloby optymalne" << endl;
	}
	if (this->poziom_asort <= 60)
	{
		cout << "~Zrob dostawe asortymentu" << endl;
	}
}

void Sala::koniec_dnia()
{
	for (auto& pacjent : *wsk_pacjenci_dzis)
	{
		if (pacjent->stan_w_szpitalu == "Na sali")
		{

			pacjent->stan_w_szpitalu = "Opuscil szpital";
			this->zwolnij_lozko(1);
		}
		else if (pacjent->stan_w_szpitalu == "W poczekalni")
		{

			this->zwolnij_miejsce_w_poczekalni(1);
			this->zuzyj_asortyment(1, pacjent->stan_zdrowia);
			pacjent->stan_w_szpitalu = "Opuscil szpital";

		}
	}
}

void Sala::uzupelnienie_hurtowe_asortymentu(int& proc)
{
	for (auto& asort : *wskaznik_na_asortyment)
	{
		asort->uzupelnij_hurtowo(proc);
	}
}

vector<dzien> Sala::przygotuj_grafik()
{
	vector<dzien> szablon;
	for (auto& lek : *wskaznik_na_lekarzy)
	{
		szablon = lek->tydzien;
		break;
	}
	for (auto& dzien : szablon)
	{
		dzien.godziny_pracy[0] = "--:--";
		dzien.godziny_pracy[1] = "--:--";
		vector<vector<string >> operacje;
		dzien.operacje_na_dzis = operacje;
	}
	return szablon;
}

void Sala::generuj_raport(const string& nazwa_raportu)
{
	ofstream raport(nazwa_raportu);
	if (raport)
	{
		raport << *this;
		raport << endl;
		raport << "Pacjenci z dzisiaj:" << endl;
		for (auto& pacjent : *wsk_pacjenci_dzis)
		{
			raport << *pacjent << endl;
		}
		raport << "Poziom asortymentu: " << endl;
		for (auto& elem : *wskaznik_na_asortyment)
		{
			raport << *elem << " procent normy: " << elem->oblicz_poziom_proc() << endl;
		}
	}
	raport.close();
}



//-------------------------------------------------------------------POCZEKALNIA-----------------------------------------------------------------------------------------

Poczekalnia::Poczekalnia() :il_miejsc(0), il_wolnych_miejsc(0) {}

Poczekalnia::~Poczekalnia() {}

void Poczekalnia::ustaw_ile_miejsc(int& ilosc)
{
	this->il_miejsc = ilosc;
	this->il_wolnych_miejsc = ilosc;
}

void Poczekalnia::zajmij_miejsce(int& ilosc)
{
	il_wolnych_miejsc -= ilosc;
}

void Poczekalnia::zwolnij_miejsce(int& ilosc)
{
	this->il_wolnych_miejsc += ilosc;
}

ostream& operator<<(ostream& s, Asortyment& asortyment)
{
	s << setw(13);
	s << asortyment.nazwa;
	s << setw(10);
	s << " ilosc: " << asortyment.aktualna_ilosc;
	return s;
}

ostream& operator<<(ostream& s, Sala& sala)
{
	s << "STAN: " << sala.stan << endl << endl;
	s << "LICZBA WOLNYCH LOZEK: " << sala.il_wolnych_lozek << "   LICZBA ZAJETYCH MIEJSC: " << sala.il_zajetych_lozek << endl;
	s << "LICZBA WOLNYCH MIEJSC W POCZEKALNI: " << sala.odczytaj_ile_miejsc_wolnych_w_poczekalni() << endl;
	s << "PROCENT WSZYSTKICH DOSTEPNYCH PRACOWNIKOW: " << sala.proc_dost_personelu << "%" << endl;
	s << "LICZBA DOSTEPNYCH LEKARZY: " << sala.il_dost_lekarzy << "   LICZBA DOSTEPNYCH PIELEGNIAREK: " << sala.il_dost_piel << endl;
	s << "PROCENT ZAOPATRZENIA: " << sala.poziom_asort << endl;

	return s;
}
