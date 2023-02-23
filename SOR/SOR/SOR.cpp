/** @file */
#include "Pacjent.h"
#include "Pracownicy.h"
#include "Funkcje.h"
#include "Sala.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
//#include <vld.h>
using namespace std;


int main()
{

    Sala sor;
    Poczekalnia poczekalnia;

    Sala* wsk_na_sale = &sor;
    Poczekalnia* wsk_na_poczekalnie = &poczekalnia;

    vector< shared_ptr<Lekarz>> baza_lekarze;
    vector< shared_ptr<Pielegniarka>> baza_pielegniarki;
    vector< shared_ptr<Asortyment>> baza_asortyment;

    string nazwapliku_grafik = "Grafik.txt";
    string nazwapliku_asortyment = "Asortyment.txt";
    string nazwapliku_hasla = "Hasla.txt";

    odczytaj_plik_grafik(nazwapliku_grafik, baza_lekarze, baza_pielegniarki);
    odczytaj_plik_asortyment(nazwapliku_asortyment, baza_asortyment, wsk_na_sale, wsk_na_poczekalnie);

    vector< shared_ptr<Lekarz>>* wskaznik_na_lekarze = &baza_lekarze;
    vector< shared_ptr<Pielegniarka>>* wskaznik_na_pielegniarki = &baza_pielegniarki;
    vector< shared_ptr<Asortyment>>* wskaznik_na_asortyment = &baza_asortyment;

    odczytaj_hasla(nazwapliku_hasla, wskaznik_na_lekarze, wskaznik_na_pielegniarki);

    sor.przekaz_wskazniki(wsk_na_poczekalnie, wskaznik_na_lekarze, wskaznik_na_pielegniarki, wskaznik_na_asortyment);

    //pacjenci;
    int licznik_pacjentow = 0;
    vector<pair<string, vector<shared_ptr<Pacjent>>>> zgloszeni_pacjenci;

    int odp_menu_g = 0;
    int odp_menu_lek = 0;
    int odp_menu_dyspozytor = 0;
    int odp_menu_dostawca = 0;
    bool zgoda = 0;
    string _id;
    string wprhaslo;

    string pierwszy_dzien_tygodnia = baza_lekarze[0]->pierwszy_dzien_tygodnia();
    string ostatnio_wprowadzona_data = pierwszy_dzien_tygodnia;
    string ostatnio_wproawdzona_godzina = "--:--";
    string aktualna_data, aktualna_godzina, podanah, podanydz;

    bool pozwolenie = 0;

    while (odp_menu_g != 5)
    {
        odp_menu_g = menu_glowne();
        switch (odp_menu_g)
        {
        case 1://lekarz    

            while (zgoda == 0)
            {
                cout << ">>>>>>>>>>>>>>>>>>>>>>>WERYFIKACJA>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                cout << "       ID:";
                cin >> _id;
                int id = -80;
                if (czyint(_id))
                {
                    id = stoi(_id);
                }

                if ((czyint(_id) == 0) || id<0 || id>baza_lekarze.size())
                {
                    zgoda = 0;
                    cout << "Niepoprawne ID. Sprobuj ponownie" << endl;
                    cout << "Czy chcesz wrocic do menu glownego? wpisz 'T' jesli tak" << endl;
                    string czy_przerwij;
                    cin >> czy_przerwij;
                    if (czy_przerwij == "T") { break; }
                    cout << "__________________________________________________________" << endl;
                }
                else
                {
                    if (baza_lekarze[id - 1]->zaloguj() == 1)
                    {
                        zgoda = 1;
                        vector<int> numery;
                        while (odp_menu_lek != 4)
                        {
                            odp_menu_lek = menu_lek();
                            int odp_menu_lek_grafik = 0;
                            string odp_dokumentacja;
                            switch (odp_menu_lek)
                            {
                            case 1: //zmiana hasla
                                baza_lekarze[id - 1]->zmien_haslo();
                                break;
                            case 2:// grafik
                                cout << endl << ">>>>>>>>>>>>>>>>>>>>>>>>>>GRAFIK>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                                baza_lekarze[id - 1]->wyswietl_grafik();
                                cout << endl;
                                while (odp_menu_lek_grafik != 3)
                                {
                                    odp_menu_lek_grafik = menu_grafik();
                                    if (odp_menu_lek_grafik == 1)// zmien grafik
                                    {
                                        bool pozwolenie = 0;
                                        string podanah, podanydz;
                                        cout << "->Podaj aktualna date (format: DD.MM): " << endl;
                                        cin >> podanydz;
                                        cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
                                        cin >> podanah;
                                        pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, podanydz, pierwszy_dzien_tygodnia);
                                        if (pozwolenie == 1)
                                        {
                                            baza_lekarze[id - 1]->zmien_grafik(ostatnio_wprowadzona_data);
                                        }
                                        else
                                        {
                                            cout << "~Podano nieporawne dane. Ostatnia data i godzina wprowadzania zmian: " << ostatnio_wprowadzona_data << " o " << ostatnio_wproawdzona_godzina << endl;
                                            cout << "__________________________________________________________" << endl;
                                        }
                                    }
                                    else if (odp_menu_lek_grafik == 2) //dodaj operacje
                                    {
                                        bool pozwolenie = 0;
                                        string podanah, podanydz;
                                        cout << "->Podaj aktualna date (format: DD.MM): " << endl;
                                        cin >> podanydz;
                                        cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
                                        cin >> podanah;
                                        pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, podanydz, pierwszy_dzien_tygodnia);
                                        if (pozwolenie == 1)
                                        {
                                            baza_lekarze[id - 1]->dodaj_operacje(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina);
                                        }
                                        else
                                        {
                                            cout << "~Podano nieporawne dane. Ostatnia data i godzina wprowadzania zmian: " << ostatnio_wprowadzona_data << " o " << ostatnio_wproawdzona_godzina << endl;
                                            cout << "__________________________________________________________" << endl;
                                        }
                                    }
                                    else if (odp_menu_lek_grafik != 3)
                                    {
                                        cout << "~Niepoprawne dane. Sprobuj ponownie (wpisz cyfre od 1 do 4)." << endl << endl;
                                        cout << "__________________________________________________________" << endl;
                                    }
                                }
                                odp_menu_lek_grafik = 0;
                                break;
                            case 3: //moi pacjenci
                                numery = baza_lekarze[id - 1]->zwroc_moich_pacjentow();
                                if (numery.size() != 0)
                                {
                                    for (auto& dzien : zgloszeni_pacjenci)
                                    {
                                        for (auto& pacjent : dzien.second)
                                        {
                                            for (auto& nr : numery)
                                            {
                                                if (pacjent->jaki_mam_numer() == nr)
                                                {
                                                    cout << *pacjent << endl;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    cout << "Wpisz numer pacjenta, ktoremu chcesz uzupelnic dokumentacje, wpisz 'N' jesli chcesz wrocic do menu lekarza: " << endl;
                                    cin >> odp_dokumentacja;
                                    if (odp_dokumentacja == "N") { break; }
                                    else if (czyint(odp_dokumentacja))
                                    {
                                        bool czy_jest_taki_pacjent = 0;
                                        for (auto& nr : numery)
                                        {
                                            if (nr == stoi(odp_dokumentacja))
                                            {
                                                czy_jest_taki_pacjent = 1;
                                                for (auto& dzien : zgloszeni_pacjenci)
                                                {
                                                    for (auto& pacjent : dzien.second)
                                                    {

                                                        if (pacjent->jaki_mam_numer() == nr)
                                                        {
                                                            pacjent->dodaj_dokumentacje();
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        if (czy_jest_taki_pacjent == 0)
                                        {
                                            cout << "~Wybierz jedno z wyswietlonych wyzej numerow" << endl;
                                        }
                                    }
                                    else
                                    {
                                        cout << "~Niepoprawne dane. Wpisz wartosc liczbowa lub 'N'. Sprobuj ponownie" << endl;
                                        cout << "__________________________________________________________" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "~Brak pacjentow do wyswietlenia." << endl;
                                    cout << "__________________________________________________________" << endl;
                                }
                                break;
                            case 4://
                                break;
                            default:
                                cout << "~Niepoprawne dane. Sprobuj ponownie (wpisz cyfre od 1 do 4)." << endl;
                                cout << "__________________________________________________________" << endl;
                                break;
                            }
                        }
                        odp_menu_lek = 0;
                    }
                    else
                    {
                        cout << "Jak chcesz wrocic do menu glownego wpisz 'T'" << endl;
                        string odp;
                        cin >> odp;
                        if (odp == "T")
                        {
                            odp_menu_lek = 0;
                            zgoda = 0;
                            break;
                        }

                    }

                }
            }
            zgoda = 0;

            break;
        case 2://pielegniarka
            while (zgoda == 0)
            {
                cout << "=======================WERYFIKACJA=======================" << endl;

                cout << "       ID:";
                cin >> _id;
                int id = -80;
                if (czyint(_id))
                {
                    id = stoi(_id);
                }
                if ((czyint(_id) == 0) || id<0 || id>baza_pielegniarki.size())
                {
                    zgoda = 0;
                    cout << "Niepoprawne ID. Sprobuj ponownie" << endl;
                    cout << "Czy chcesz wrocic do menu glownego? wpisz 'T' jesli tak" << endl;
                    string czy_przerwij;
                    cin >> czy_przerwij;
                    if (czy_przerwij == "T") { break; }
                    cout << "__________________________________________________________" << endl;
                }
                else
                {
                    if (baza_pielegniarki[id - 1]->zaloguj() == 1)
                    {
                        zgoda = 1;
                        int odp_piel_graf = 0;
                        cout << endl << ">>>>>>>>>>>>>>>>>>>>>>>>>>GRAFIK>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
                        baza_pielegniarki[id - 1]->wyswietl_grafik();
                        cout << endl;
                        while (odp_piel_graf != 3)
                        {
                            odp_piel_graf = menu_grafik_piel();
                            if (odp_piel_graf == 2)
                            {
                                bool pozwolenie = 0;
                                string podanah, podanydz;
                                cout << "->Podaj aktualna date (format: DD.MM): " << endl;
                                cin >> podanydz;
                                cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
                                cin >> podanah;
                                pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, podanydz, pierwszy_dzien_tygodnia);
                                if (pozwolenie == 1)
                                {
                                    baza_pielegniarki[id - 1]->zmien_grafik(ostatnio_wprowadzona_data);
                                }
                                else
                                {
                                    cout << "~Podano nieporawne dane. Ostatnia data i godzina wprowadzania zmian: " << ostatnio_wprowadzona_data << " o " << ostatnio_wproawdzona_godzina << endl;
                                    cout << "__________________________________________________________" << endl;
                                }
                            }
                            else if (odp_piel_graf == 1)
                            {
                                baza_pielegniarki[id - 1]->zmien_haslo();

                            }
                            else if (odp_piel_graf != 3)
                            {
                                cout << "~Niepoprawne dane. Sprobuj ponownie (wpisz cyfre od 1 do 3)." << endl;
                                cout << "_________________________________________________________" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Jak chcesz wrocic do menu glownego wpisz 'T'" << endl;
                        string odp;
                        cin >> odp;
                        if (odp == "T")
                        {
                            zgoda = 0;
                            break;
                        }
                    }
                }
            }
            zgoda = 0;
            break;
        case 3://dyspozytor


            cout << "->Podaj aktualna date (format: DD.MM): " << endl;
            cin >> podanydz;
            cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
            cin >> podanah;
            pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, podanydz, pierwszy_dzien_tygodnia);
            if (pozwolenie == 1)
            {
                sor.uruchom_sor(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data);
                pair<string, vector<shared_ptr<Pacjent>>> pacjenci_dzis;
                vector<shared_ptr<Pacjent>>* wsk_pacjenci_dzis = &pacjenci_dzis.second;
                pacjenci_dzis.first = ostatnio_wprowadzona_data;
                sor.przekaz_wskaznik_pacjenci(wsk_pacjenci_dzis);

                int licznik_pacjentow_dzis = 0;
                bool czy_poprawna_godzina_uzupelnienia = 0;
                string godzina_uzupelnienia;
                string imie_dodawanego, nazwisko_dodawanego, stanowisko_dodawanego;
                bool godziny_dodawanego = 0;

                while (odp_menu_dyspozytor != 6)
                {
                    odp_menu_dyspozytor = menu_dyspozytor();
                    int odp_menu_zdarzenie = 0;
                    switch (odp_menu_dyspozytor)
                    {
                    case 1://dodaj zdarzenie
                        while (odp_menu_zdarzenie != 2)
                        {
                            odp_menu_zdarzenie = menu_zdarzenie();
                            string imie_pacjenta, nazwisko_pacjenta, notatka, stan_poszkodowania, godzina_zgloszenia;
                            if (odp_menu_zdarzenie == 1)
                            {
                                bool czy_poprawna_godzina_zgloszenia = 0;
                                cout << "Podaj godzine zgloszenia: ";
                                cin >> godzina_zgloszenia;
                                czy_poprawna_godzina_zgloszenia = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, godzina_zgloszenia, ostatnio_wprowadzona_data, pierwszy_dzien_tygodnia);
                                if (czy_poprawna_godzina_zgloszenia == 1)
                                {
                                    ostatnio_wproawdzona_godzina = godzina_zgloszenia;
                                    sor.sprawdz_pacj_na_sali_i_w_poczekalni(ostatnio_wproawdzona_godzina);
                                    sor.czy_ktos_nie_skonczyl_pracy(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina);
                                    cout << "Podaj imie pacjenta:";
                                    cin >> imie_pacjenta;
                                    cout << "Podaj nazwisko pacjenta: ";
                                    cin >> nazwisko_pacjenta;
                                    cout << "Jakiej pomocy potrzebuje pacjent: 1.Pomoc standardowa 2.Pomoc pilna 3. Pomoc natychmiastowa  : ";
                                    cin >> stan_poszkodowania;
                                    while (czyint(stan_poszkodowania) != 1)
                                    {
                                        cout << "~Wybierz cyfre od 1 do 3" << endl;
                                        cin >> stan_poszkodowania;
                                    }
                                    while (stoi(stan_poszkodowania) > 3)
                                    {
                                        cout << "~Wybierz cyfre od 1 do 3" << endl;
                                        cin >> stan_poszkodowania;
                                    }
                                    licznik_pacjentow++;
                                    licznik_pacjentow_dzis++;
                                    cout << "Krotka notatka dotyczaca pacjenta:" << endl;
                                    cin.ignore();
                                    getline(cin, notatka);
                                }
                                else
                                {
                                    cout << "Godzina zgloszenia musi byc wieksza od ostatniego logowania i byc w formacie GG:MM" << endl;
                                    break;
                                }
                                int stan_pacjenta = stoi(stan_poszkodowania);
                                shared_ptr<Pacjent> zgloszenie(new Pacjent(godzina_zgloszenia, ostatnio_wprowadzona_data, licznik_pacjentow, imie_pacjenta, nazwisko_pacjenta, stan_pacjenta, notatka));
                                pacjenci_dzis.second.push_back(move(zgloszenie));
                                if (sor.czy_trzeba_oddelegowac())
                                {
                                    cout << "_____________________________________________________________" << endl;
                                    cout << "Nie ma wystarczajacych miejsc na SORze i poczekalni" << endl;
                                    cout << "Pacjent zostaje oddelegowany do Szpitala w Lesnej Gorze" << endl;
                                    pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->oddeleguj(); /// to moze byc przyczyna wielu bledow      

                                }
                                else //nie trzeba oddelegowywac
                                {
                                    string godzina_uzdrowienia = dodaj_minuty(ostatnio_wproawdzona_godzina, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->czas_zajecia_lozka);
                                    if (sor.czy_jest_wystarczajaco_personelu(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina, godzina_uzdrowienia, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->potrzebni_lekarze, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->potrzebne_pielegniarki))
                                    {
                                        sor.aktualizuj(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina, godzina_uzdrowienia);
                                        cout << "Czy chcesz wybrac konkretnego pracownika prowadzacego? Wpisz T jesli tak. Jesli Ci to obojetne to wpisz cokolwiek" << endl;
                                        string odp;
                                        cin >> odp;
                                        if (odp == "T") //przypisz konkretnie jakiegos
                                        {
                                            cout << endl << "Wpisz id wybranego pracownika" << endl;
                                            sor.wybierz_konkretnego_prowadzacego(pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->get_stan_zdrowia(), ostatnio_wproawdzona_godzina, godzina_uzdrowienia, licznik_pacjentow);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_start_pomocy(ostatnio_wproawdzona_godzina);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_koniec_pomocy(godzina_uzdrowienia);
                                            sor.zajmij_lozko(1);
                                            sor.zuzyj_asortyment(1, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->get_stan_zdrowia());
                                            sor.oblicz_calosciowy_poziom_asortymentu();
                                            sor.ustaw_stan();
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_stan_w_szpitalu("Na sali");

                                            cout << "Pacjent przebywa na SORze" << endl;
                                            cout << "_____________________________________________________________" << endl;
                                            cout << endl;

                                        }
                                        else//randomowy lekarz
                                        {
                                            sor.wybierz_dowolny_komplet_pracownikow(pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->get_stan_zdrowia(), ostatnio_wproawdzona_godzina, godzina_uzdrowienia, licznik_pacjentow);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_start_pomocy(ostatnio_wproawdzona_godzina);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_koniec_pomocy(godzina_uzdrowienia);

                                            sor.zajmij_lozko(1);
                                            sor.zuzyj_asortyment(1, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->get_stan_zdrowia());
                                            sor.oblicz_calosciowy_poziom_asortymentu();
                                            sor.ustaw_stan();
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_stan_w_szpitalu("Na sali");
                                            cout << "Pracownicy dla tego pacjenta zostali wybrani" << endl;
                                            cout << "Pacjent przebywa na SORze" << endl;
                                            cout << "_____________________________________________________________" << endl;
                                        }
                                    }
                                    else
                                    {
                                        //poczekalnia
                                        cout << "Nie ma wystarczajacej ilosci dostepnego personelu" << endl;
                                        vector<string> godziny = sor.znajdz_najkrotszy_czas_oczekiwnania(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina, pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->get_stan_zdrowia(), licznik_pacjentow);
                                        if (godziny.size() != 0)
                                        {

                                            sor.zajmij_miejsce_w_poczekalni(1);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_start_pomocy(godziny[0]);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_koniec_pomocy(godziny[1]);
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->ustaw_stan_w_szpitalu("W poczekalni");
                                            sor.oblicz_calosciowy_poziom_asortymentu();
                                            sor.ustaw_stan();
                                            cout << "Pacjent przebywa w poczekalni" << endl;
                                            cout << "_____________________________________________________________" << endl;
                                            cout << endl;

                                        }
                                        else
                                        {
                                            pacjenci_dzis.second[licznik_pacjentow_dzis - 1]->oddeleguj();
                                            cout << "Pacjent zostaje oddelegowany do Szpitala w Lesnej Gorze" << endl;
                                            cout << "_____________________________________________________________" << endl;
                                        }
                                    }
                                }

                            }
                            else if (odp_menu_zdarzenie != 2)
                            {
                                cout << "Niepoprawne dane. Sprobuj ponownie. Wprowadz cyfre od 1 do 2." << endl;
                                cout << "_____________________________________________________________" << endl;
                            }
                        }
                        odp_menu_zdarzenie = 0;
                        break;
                    case 2://sprawdz stan
                        cout << endl;
                        cout << "_____________________________________________________________" << endl;
                        cout << "Stan SORu na: " << ostatnio_wprowadzona_data << "  " << ostatnio_wproawdzona_godzina << endl;
                        sor.aktualizuj(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina, ostatnio_wproawdzona_godzina); //
                        sor.oblicz_calosciowy_poziom_asortymentu();
                        sor.ustaw_stan();
                        sor.rada();
                        cout << sor;

                        break;
                    case 3://dodaj pracownik

                        cout << "Podaj imie pracownika: " << endl;
                        cin >> imie_dodawanego;
                        cout << "Podaj nazwisko pracownika: " << endl;
                        cin >> nazwisko_dodawanego;
                        cout << "Podaj stanowisko. Wpisz 'lekarz' lub 'pielegniarka'" << endl;
                        cin >> stanowisko_dodawanego;
                        while (godziny_dodawanego != 1)
                        {
                            cout << "Podaj godzine rozpoczecia i zakonczenia pracy DZISIAJ" << endl;
                            string start_dodawanego, stop_dodawanego;
                            cin >> start_dodawanego;
                            cin >> stop_dodawanego;
                            if (sprawdz_format_godziny(start_dodawanego) && sprawdz_format_godziny(stop_dodawanego))
                            {
                                if (start_dodawanego < stop_dodawanego)
                                {
                                    godziny_dodawanego = 1;
                                    if (stanowisko_dodawanego == "lekarz")
                                    {
                                        int nr = baza_lekarze.size() + 1;
                                        vector<dzien> nowy_tydzien;
                                        nowy_tydzien = sor.przygotuj_grafik();
                                        for (auto& dzien : nowy_tydzien)
                                        {
                                            if (dzien.data == ostatnio_wprowadzona_data)
                                            {
                                                dzien.godziny_pracy[0] = start_dodawanego;
                                                dzien.godziny_pracy[1] = stop_dodawanego;
                                                break;
                                            }
                                        }
                                        shared_ptr<Lekarz> Nowy(new Lekarz(nr, imie_dodawanego, nazwisko_dodawanego, nowy_tydzien));
                                        baza_lekarze.push_back(move(Nowy));
                                        cout << "~Dodano lekarza" << endl;
                                    }
                                    else if (stanowisko_dodawanego == "pielegniarka")
                                    {
                                        int nr = baza_pielegniarki.size() + 1;
                                        vector<dzien> nowy_tydzien;
                                        nowy_tydzien = sor.przygotuj_grafik();
                                        for (auto& dzien : nowy_tydzien)
                                        {
                                            if (dzien.data == ostatnio_wprowadzona_data)
                                            {
                                                dzien.godziny_pracy[0] = start_dodawanego;
                                                dzien.godziny_pracy[1] = stop_dodawanego;
                                                break;
                                            }
                                        }
                                        shared_ptr<Pielegniarka> Nowy(new Pielegniarka(nr, imie_dodawanego, nazwisko_dodawanego, nowy_tydzien));
                                        baza_pielegniarki.push_back(move(Nowy));
                                        cout << "~Dodano pielegniarke" << endl;
                                    }
                                    else
                                    {
                                        cout << "~Wprowadzono nieprawidlowe dane. W stanowisku wpisz 'lekarz' lub 'pielegniarka'" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "~Godzina zakonczenia pracy musi byc wieksza od godziny rozpoczecia" << endl;
                                }
                            }
                            else
                            {
                                cout << "~Poprawny format godziny to GG:MM. Sprobuj ponownie. " << endl;
                            }
                        }
                        godziny_dodawanego = 0;

                        break;
                    case 4://uzupelnij asortyment

                        cout << "Podaj godzine uzupelnienia: ";
                        cin >> godzina_uzupelnienia;
                        czy_poprawna_godzina_uzupelnienia = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, godzina_uzupelnienia, ostatnio_wprowadzona_data, pierwszy_dzien_tygodnia);
                        if (czy_poprawna_godzina_uzupelnienia == 1)
                        {
                            ostatnio_wproawdzona_godzina = godzina_uzupelnienia;
                            cout << "O ile procent chcesz podniesc poziom zaopatrzenia? MAX 50%" << endl;
                            string odp;
                            cin >> odp;
                            if (czyint(odp))
                            {
                                if (stoi(odp) <= 50)
                                {
                                    int il = stoi(odp);
                                    sor.uzupelnienie_hurtowe_asortymentu(il);

                                    cout << "~Asortyment zostal uzupelniony";
                                }
                                else
                                {
                                    cout << "~Mozesz maksymalnie podniesc poziom zaopatrzenia o 50%." << endl;
                                }

                            }
                            else
                            {
                                cout << "~Podaj wartosc liczbowa. Sprobuj ponownie" << endl;
                            }

                        }
                        else
                        {
                            cout << "~Nastepnym razem podaj odpowiednie dane. Ostatnio wprowadzane dane byly o: " << ostatnio_wproawdzona_godzina << endl;
                        }
                        czy_poprawna_godzina_uzupelnienia = 0;
                        break;
                    case 5://wygeneruj raport

                        cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
                        cin >> podanah;
                        pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, ostatnio_wprowadzona_data, pierwszy_dzien_tygodnia);
                        if (pozwolenie == 1)
                        {
                            sor.sprawdz_pacj_na_sali_i_w_poczekalni(ostatnio_wproawdzona_godzina);
                            sor.czy_ktos_nie_skonczyl_pracy(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina);
                            sor.aktualizuj(ostatnio_wprowadzona_data, ostatnio_wproawdzona_godzina, ostatnio_wproawdzona_godzina); //
                            sor.oblicz_calosciowy_poziom_asortymentu();
                            sor.ustaw_stan();
                            string godzina_do_nazwy = ostatnio_wproawdzona_godzina;
                            godzina_do_nazwy[2] = '.';
                            const string nazwa_raportu = "RAPORT" + ostatnio_wprowadzona_data + godzina_do_nazwy;

                            sor.generuj_raport(nazwa_raportu);
                            cout << "~wygenerowano raport pod nazwa: " << nazwa_raportu << endl;
                        }
                        else
                        {
                            cout << "~Poprawny format godziny to GG:MM. Sprobuj ponownie. Ostatnie logowanie bylo o: " << ostatnio_wproawdzona_godzina << endl;
                        }
                        break;

                    case 6://wyjscie
                        ostatnio_wproawdzona_godzina = "23:59";
                        sor.koniec_dnia();
                        break;
                    default:
                        cout << "Niepoprawne dane. Sprobuj ponownie. Wprowadz cyfre od 1 do 6." << endl;
                        cout << "_____________________________________________________________" << endl;
                        break;
                    }

                }
                zgloszeni_pacjenci.push_back(pacjenci_dzis);
                pozwolenie = 0;
                odp_menu_dyspozytor = 0;
            }
            else
            {
                cout << "~Podano nieporawne dane. Ostatnia data i godzina wprowadzania zmian: " << ostatnio_wprowadzona_data << " o " << ostatnio_wproawdzona_godzina << endl;
                cout << "__________________________________________________________" << endl;

            }

            break;
        case 4://dostawca

            while (odp_menu_dostawca != 3)
            {
                odp_menu_dostawca = menu_dostawca();
                switch (odp_menu_dostawca)
                {
                case 1://uzupelnij
                    cout << "->Podaj aktualna date (format: DD.MM): " << endl;
                    cin >> podanydz;
                    cout << "->Podaj aktualna godzine (format: GG:MM): " << endl;
                    cin >> podanah;
                    pozwolenie = poprawnosc_godziny(ostatnio_wproawdzona_godzina, ostatnio_wprowadzona_data, podanah, podanydz, pierwszy_dzien_tygodnia);
                    if (pozwolenie == 1)
                    {
                        cout << "Podaj numer asortymentu, ktory chcesz uzupelnic : " << endl;
                        string ktory;
                        for (int i = 0; i < baza_asortyment.size(); i++)
                        {
                            if (i + 1 < 10)
                            {
                                cout << i + 1 << ". " << *baza_asortyment[i] << ", procent normy:" << baza_asortyment[i]->oblicz_poziom_proc() << endl;
                            }
                            else
                            {
                                cout << i + 1 << "." << *baza_asortyment[i] << ", procent normy:" << baza_asortyment[i]->oblicz_poziom_proc() << endl;
                            }

                        }

                        bool dobrze_wybrany_asort = 0;
                        while (dobrze_wybrany_asort != 1)
                        {
                            cout << "Wybieram:";
                            cin >> ktory;
                            cout << endl;

                            if (czyint(ktory))
                            {
                                dobrze_wybrany_asort = 0;
                                if (stoi(ktory) < baza_asortyment.size() + 1)
                                {
                                    dobrze_wybrany_asort = 1;
                                    bool dobrze_wybrana_il = 0;
                                    while (dobrze_wybrana_il != 1)
                                    {
                                        cout << "Ile dodajesz?";
                                        string ile;
                                        cin >> ile;
                                        if (czyint(ile))
                                        {

                                            dobrze_wybrana_il = 1;
                                            int il = stoi(ile);
                                            baza_asortyment[stoi(ktory) - 1]->dostawca_uzupelnij(il);
                                            cout << "Chcesz dalej uzupelniac? wpisz 'T' jesli tak" << endl;
                                            {
                                                string dalej;
                                                cin >> dalej;
                                                if (dalej == "T") { dobrze_wybrany_asort = 0; dobrze_wybrana_il = 0; break; }
                                                else { break; break; }

                                            }

                                        }
                                        else if (czyint(ile) == 0 || dobrze_wybrana_il == 0)
                                        {
                                            cout << "~Podaj wartosc liczbowa" << endl;
                                            cout << "Czy chcesz wrocic? wpisz 'T' jesli tak" << endl;
                                            string czy_przerwij;
                                            cin >> czy_przerwij;
                                            if (czy_przerwij == "T") { break; break; }//
                                            cout << "_____________________________________________________________" << endl;
                                        }
                                    }
                                    dobrze_wybrana_il = 0;
                                }
                                else
                                {
                                    cout << "~Podaj wartosc liczbowa od 1 do " << baza_asortyment.size() << endl;
                                    cout << "Czy chcesz wrocic do menu dostawcy? wpisz 'T' jesli tak" << endl;
                                    string czy_przerwij;
                                    cin >> czy_przerwij;
                                    if (czy_przerwij == "T") { break; }
                                    cout << "_____________________________________________________________" << endl;
                                }
                            }
                            else if (czyint(ktory) == 0)
                            {

                                cout << "~Podaj wartosc liczbowa od 1 do " << baza_asortyment.size() << endl;
                                cout << "Czy chcesz wrocic do menu dostawcy? wpisz 'T' jesli tak" << endl;
                                string czy_przerwij;
                                cin >> czy_przerwij;
                                if (czy_przerwij == "T") { break; }
                                cout << "_____________________________________________________________" << endl;
                            }
                        }
                        dobrze_wybrany_asort = 0;
                    }
                    else
                    {
                        cout << "~Podano nieporawne dane. Ostatnia data i godzina wprowadzania zmian: " << ostatnio_wprowadzona_data << " o " << ostatnio_wproawdzona_godzina << endl;
                        cout << "__________________________________________________________" << endl;
                    }
                    pozwolenie = 0;
                    break;
                case 2://wyswietl
                    cout << "_____________________________________________________________" << endl;

                    cout << "Stan asortymentu : " << endl;

                    for (int i = 0; i < baza_asortyment.size(); i++)
                    {

                        if (i + 1 < 10)
                        {
                            cout << i + 1 << ". " << *baza_asortyment[i] << ", procent normy:" << baza_asortyment[i]->oblicz_poziom_proc() << endl;
                        }
                        else
                        {
                            cout << i + 1 << "." << *baza_asortyment[i] << ", procent normy:" << baza_asortyment[i]->oblicz_poziom_proc() << endl;
                        }

                    }
                    break;
                case 3://powrot
                    break;
                default:
                    cout << "~Niepoprawne dane. Sprobuj ponownie. Wprowadz cyfre od 1 do 3." << endl;
                    cout << "_____________________________________________________________" << endl;
                    break;
                }
            }
            cout << sor;
            odp_menu_dostawca = 0;

            break;

        case 5:
            cout << "_________________________________________________________" << endl;

            cout << "                         KONIEC                          " << endl;
            cout << "_________________________________________________________" << endl;
            break;
        default:
            cout << "Niepoprawne dane. Wpisz cyfre od 1 do 5" << endl;
            cout << "_________________________________________________________" << endl;
            break;
        }
    }

    wskaznik_na_lekarze = nullptr;
    wskaznik_na_asortyment = nullptr;
    wskaznik_na_pielegniarki = nullptr;
    wsk_na_sale = nullptr;

}

