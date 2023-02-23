/** @file */
#include "Funkcje.h"
#include "Pracownicy.h"
#include "Sala.h"
#include "Pacjent.h"

using namespace std;


//==========================================================================INNE===================================================================================================
void odczytaj_plik_grafik(string& nazwa_plik_personel, vector< shared_ptr<Lekarz>>& _lekarze, vector< shared_ptr<Pielegniarka>>& _pielegniarki)
{
    string pierwszy_dzien;
    ifstream plik(nazwa_plik_personel);
    if (plik)
    {
        string line;
        int licznik_lekarzy = 0;
        int licznik_pielegniarek = 0;
        int counterlinii = 0;
        string pdzien, pmies;
        while (getline(plik, line))
        {

            stringstream ss;
            ss << line;
            string cos;

            if (line.size() > 0) { counterlinii++; }
            if (counterlinii == 1)
            {
                while (ss >> cos >> cos >> pierwszy_dzien);
                pdzien = pierwszy_dzien.substr(0, 2);
                pmies = pierwszy_dzien.substr(3, 2);
            }
            vector<dzien> nowy_tydzien = {};
            string do_inkrementacji = pierwszy_dzien;
            for (int i = 0; i < 7; i++)
            {
                dzien nowy_dzien(do_inkrementacji);
                nowy_tydzien.push_back(nowy_dzien);
                string tmp;
                tmp = inkrementuj_dzien(do_inkrementacji);
                do_inkrementacji = tmp;
            }

            string imie;
            string nazwisko;
            string pozycja;
            string wejpon, wejwt, wejsr, wejczw, wejpt, wejsob, wejnd;
            string wyjpon, wyjwt, wyjsr, wyjczw, wyjpt, wyjsob, wyjnd;
            if (counterlinii > 2)
            {
                while (ss >> imie >> nazwisko >> pozycja >> wejpon >> wyjpon >> wejwt >> wyjwt >> wejsr >> wyjsr >> wejczw >> wyjczw >> wejpt >> wyjpt >> wejsob >> wyjsob >> wejnd >> wyjnd)
                {
                    if (pozycja == "lekarz")
                    {

                        licznik_lekarzy++;
                        nowy_tydzien[0].godziny_pracy = { wejpon,wyjpon };
                        nowy_tydzien[1].godziny_pracy = { wejwt,wyjwt };
                        nowy_tydzien[2].godziny_pracy = { wejsr,wyjsr };
                        nowy_tydzien[3].godziny_pracy = { wejczw,wyjczw };
                        nowy_tydzien[4].godziny_pracy = { wejpt,wyjpt };
                        nowy_tydzien[5].godziny_pracy = { wejsob,wyjsob };
                        nowy_tydzien[6].godziny_pracy = { wejnd,wyjnd };


                        shared_ptr<Lekarz> Nowy(new Lekarz(licznik_lekarzy, imie, nazwisko, nowy_tydzien));
                        _lekarze.push_back(move(Nowy));


                    }
                    else
                    {

                        licznik_pielegniarek++;
                        nowy_tydzien[0].godziny_pracy = { wejpon,wyjpon };
                        nowy_tydzien[1].godziny_pracy = { wejwt,wyjwt };
                        nowy_tydzien[2].godziny_pracy = { wejsr,wyjsr };
                        nowy_tydzien[3].godziny_pracy = { wejczw,wyjczw };
                        nowy_tydzien[4].godziny_pracy = { wejpt,wyjpt };
                        nowy_tydzien[5].godziny_pracy = { wejsob,wyjsob };
                        nowy_tydzien[6].godziny_pracy = { wejnd,wyjnd };
                        shared_ptr<Pielegniarka> Nowa(new Pielegniarka(licznik_pielegniarek, imie, nazwisko, nowy_tydzien));
                        _pielegniarki.push_back(move(Nowa));

                    }
                }
            }
        }
    }
}

void odczytaj_plik_asortyment(string& nazwa_pliku_asortyment, vector<shared_ptr<Asortyment>>& _asortyment, Sala*& _sala, Poczekalnia*& _poczekalnia)
{
    ifstream plik(nazwa_pliku_asortyment);
    if (plik)
    {
        string line;
        string nazwa, ilosc;
        int il;
        int licznik_linii = 0;
        while (getline(plik, line))
        {
            if (line.size() != 0)
            {
                licznik_linii++;
                stringstream ss;
                ss << line;
                while (ss >> nazwa >> ilosc)
                {
                    il = stoi(ilosc);
                    if (licznik_linii > 2)
                    {
                        shared_ptr<Asortyment> Rzecz(new Asortyment(nazwa, il));
                        _asortyment.push_back(move(Rzecz));
                    }
                    else if (licznik_linii == 1)
                    {
                        if (nazwa == "Poczekalnia:")
                        {
                            _poczekalnia->ustaw_ile_miejsc(il);
                        }
                    }
                    else if (licznik_linii == 2)
                    {
                        if (nazwa == "Miejsca:")
                        {
                            _sala->ustaw_il_lozek(il);
                        }
                    }
                }
            }

        }

    }
}

void odczytaj_hasla(string& nazwa_pliku_hasla, vector<shared_ptr<Lekarz>>*& wsk_lekarze, vector<shared_ptr<Pielegniarka>>*& wsk_pielegniarki)
{
    ifstream plik(nazwa_pliku_hasla);
    if (plik)
    {
        string line;
        bool lekarze = 0, pielegniarki = 0;
        while (getline(plik, line))
        {
            string haslo;
            int id;
            if (line == "Lekarze:")
            {
                lekarze = 1;
                pielegniarki = 0;
            }
            else if (line == "Pielegniarki:")
            {
                pielegniarki = 1;
                lekarze = 0;
            }
            else if (lekarze || pielegniarki)
            {
                stringstream ss;
                ss << line;
                if (lekarze)
                {
                    while (ss >> id >> haslo)
                    {
                        if (id < wsk_lekarze->size())
                        {
                            wsk_lekarze->at(id - 1)->ustaw_haslo(haslo);
                        }
                    }
                }
                else if (pielegniarki)
                {
                    while (ss >> id >> haslo)
                    {
                        if (id < wsk_pielegniarki->size())
                        {
                            wsk_pielegniarki->at(id - 1)->ustaw_haslo(haslo);
                        }
                    }
                }
            }

        }

    }

}

bool sprawdz_format_godziny(string& h)
{
    if (h.size() != 5) { return false; }
    string godz = h.substr(0, 2);
    string minuty = h.substr(3, 2);
    if (h[2] != ':') { return 0; }
    if (h == "--:--") { return 1; }
    if (czyint(godz) == 0 || czyint(minuty) == 0) { return 0; }
    if (stoi(godz) > 23 || stoi(minuty) > 59) { return 0; }
    return 1;
}

bool sprawdz_format_daty(string& data)
{
    if (data.size() != 5) { return false; }
    string dzien = data.substr(0, 2);
    string miesiac = data.substr(3, 2);
    if (data[2] != '.') { return 0; }
    if (czyint(dzien) == 0 || czyint(miesiac) == 0) { return 0; }
    if (stoi(dzien) > 31 || stoi(miesiac) > 12) { return 0; }
    return 1;
}

int menu_glowne()
{
    cout << "_________________________________________________________" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Jestem lekarzem" << endl;
    cout << "2 --> Jestem pielegniarka" << endl;
    cout << "3 --> Jestem dyspozytor SORu" << endl;
    cout << "4 --> Jestem dostawca" << endl;
    cout << "5 --> ZAKONCZ" << endl;
    cout << "=========================================================" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }

    return 0;
}

int menu_lek()
{
    cout << endl << "=======================MENU WYBORU=======================" << endl << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> zmien haslo" << endl;
    cout << "2 --> grafik" << endl;
    cout << "3 --> pacjenci" << endl;
    cout << "4 --> WYLOGUJ" << endl;
    cout << "=========================================================" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

int menu_grafik()
{
    cout << "_________________________________________________________" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Wprowadz zmiany w grafiku" << endl;
    cout << "2 --> Zaplanuj wydarzenie" << endl;
    cout << "3 --> Wroc do menu wyboru" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

int menu_grafik_piel()
{
    cout << "_________________________________________________________" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Zmien haslo" << endl;
    cout << "2 --> Wprowadz zmiany w grafiku" << endl;
    cout << "3 --> WROC DO MENU GLOWNEGO" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

int menu_dyspozytor()
{

    cout << endl << "=====================MENU DYSPOZYTORA====================" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Dodaj zdarzenie" << endl;
    cout << "2 --> Wyswietl aktualny stan SORu" << endl;
    cout << "3 --> Dodaj lekarza/pielegniarke" << endl;
    cout << "4 --> Uzupelnij asortyment" << endl;
    cout << "5 --> Wygeneruj raport" << endl;
    cout << "6 --> WROC DO MENU GLOWNEGO--konczy to dzien!" << endl;
    cout << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

int menu_dostawca()
{
    cout << endl << "======================MENU DOSTAWCY======================" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Uzupelnij asortyment" << endl;
    cout << "2 --> Sprawdz aktualny poziom asortymentu" << endl;
    cout << "3 --> WROC DO MENU GLOWNEGO" << endl;
    cout << "=========================================================" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

int menu_zdarzenie()
{
    cout << "_________________________________________________________" << endl;
    cout << "Wybierz jedna z opcji:" << endl;
    cout << "1 --> Wprowadzam dane pacjenta" << endl;
    cout << "2 --> WROC DO MENU DYSPOZYTORA" << endl;
    cout << "=========================================================" << endl;
    cout << "Wybieram: ";
    string odp;
    cin >> odp;
    if (czyint(odp))
    {
        return stoi(odp);
    }
    return 0;
}

bool czyint(string& str)
{
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

bool poprawnosc_godziny(string& ostatnia_h, string& ostatnia_dat, string& podana_h, string& podana_dat, string& poczatek_tygodnia)
{
    if (podana_h.size() != 5 || podana_dat.size() != 5) { return false; }
    string h = podana_h.substr(0, 2);
    string m = podana_h.substr(3, 2);
    string dz = podana_dat.substr(0, 2);
    string mies = podana_dat.substr(3, 2);

    string sh = ostatnia_h.substr(0, 2);
    string sm = ostatnia_h.substr(3, 2);
    string sdz = ostatnia_dat.substr(0, 2);
    string smies = ostatnia_dat.substr(3, 2);

    string ph = poczatek_tygodnia.substr(0, 2);
    string pm = poczatek_tygodnia.substr(3, 2);
    string pdz = poczatek_tygodnia.substr(0, 2);
    string pmies = poczatek_tygodnia.substr(3, 2);



    if (czyint(h) == 0 || czyint(m) == 0 || czyint(dz) == 0 || czyint(mies) == 0 || podana_dat[2] != '.' || podana_h[2] != ':') { return false; }
    else if (stoi(h) > 23 || stoi(m) > 59 || stoi(dz) > 31 || stoi(mies) > 12) { return 0; }
    //jest w poprawnym formacie 
    bool luty = 0, dni_31 = 0, dni_30 = 0, grudzien = 0, koncowka = 0, srodek_miesiaca = 0;
    if (stoi(pmies) == 2) { luty = 1; }
    else if (stoi(pmies) == 12) { grudzien = 1; }
    else if (stoi(pmies) == 1 || stoi(pmies) == 3 || stoi(pmies) == 5 || stoi(pmies) == 7 || stoi(pmies) == 8 || stoi(pmies) == 10) { dni_31 = 1; }
    else { dni_30 = 1; }
    // sprawdzanie ile dni w miesiacu
    if (luty == 1) //zakladam ze luty ma 29 dni zawsze
    {
        if (stoi(pdz) < 24) { srodek_miesiaca = 1; }
        else { koncowka = 1; }
    }
    else if (dni_31 == 1 || grudzien == 1)
    {
        if (stoi(pdz) < 26) { srodek_miesiaca = 1; }
        else { koncowka = 1; }
    }
    else if (dni_30 == 1)
    {
        if (stoi(pdz) < 25) { srodek_miesiaca = 1; }
        else { koncowka = 1; }
    }
    int ostatnia_dzien, ostatni_miesiac;
    string ostatnia_godzina = "23:59";
    //wiemy czy wystapi inkrementacja miesiaca
    if (srodek_miesiaca == 1)
    {
        ostatnia_dzien = stoi(pdz) + 6;
        ostatni_miesiac = stoi(pmies);
    }
    else if (koncowka == 1)
    {
        if (grudzien)
        {
            ostatnia_dzien = stoi(pdz) + 6 - 31;
            ostatni_miesiac = 1;
        }
        else if (luty)
        {
            ostatnia_dzien = stoi(pdz) + 6 - 29;
            ostatni_miesiac = 3;
        }
        else if (dni_31)
        {
            ostatnia_dzien = stoi(pdz) + 6 - 31;
            ostatni_miesiac = stoi(pmies) + 1;
        }
        else if (dni_30)
        {
            ostatnia_dzien = stoi(pdz) + 6 - 30;
            ostatni_miesiac = stoi(pmies) + 1;
        }
    }

    if (srodek_miesiaca)
    {
        if (stoi(mies) != ostatni_miesiac) { return 0; }
    }
    else if (koncowka)
    {
        if (stoi(mies) != ostatni_miesiac && stoi(mies) != stoi(pmies))
        {
            return 0;
        }
    }
    // miesiace sie zgadzaja
    if (srodek_miesiaca)
    {
        if (stoi(dz) < stoi(pdz) || stoi(dz) > ostatnia_dzien)
        {
            return 0;
        }

    }
    else if (koncowka)
    {
        if (stoi(dz) > ostatnia_dzien && stoi(dz) < stoi(pdz))
        {
            return 0;
        }
    }
    if (ostatnia_h == "--:--")
    {
        ostatnia_dat = podana_dat;
        ostatnia_h = podana_h;
        return 1;
    }

    if (srodek_miesiaca)
    {
        if (podana_dat < ostatnia_dat) { return 0; }
        else if (podana_dat > ostatnia_dat)
        {
            ostatnia_dat = podana_dat;
            ostatnia_h = podana_h;
            return 1;
        }
        else if (podana_dat == ostatnia_dat)
        {
            if (podana_h > ostatnia_h)
            {
                ostatnia_dat = podana_dat;
                ostatnia_h = podana_h;
                return 1;
            }
            else { return 0; }
        }
    }
    if (koncowka)
    {
        if (podana_dat == ostatnia_dat)
        {
            if (podana_h > ostatnia_h)
            {
                ostatnia_dat = podana_dat;
                ostatnia_h = podana_h;
                return 1;
            }
            else { return 0; }
        }
        else if (mies == smies)
        {
            if (dz > sdz)
            {
                ostatnia_dat = podana_dat;
                ostatnia_h = podana_h;
                return 1;
            }
            else { return 0; }
        }
        else if (stoi(mies) - 1 == stoi(smies))
        {
            ostatnia_dat = podana_dat;
            ostatnia_h = podana_h;
            return 1;
        }
        else if (grudzien)
        {
            if (stoi(mies) == 1 && stoi(smies) == 12)
            {
                ostatnia_dat = podana_dat;
                ostatnia_h = podana_h;
                return 1;
            }
            else { return 0; }
        }
    }
}

string inkrementuj_dzien(string& dz)
{
    if (dz.size() == 5)
    {
        string _dzien = dz.substr(0, 2);
        int _wart_dnia = stoi(_dzien);
        string _miesiac = dz.substr(3, 2);
        int _wart_mies = stoi(_miesiac);
        _wart_dnia++;

        if ((_wart_dnia == 32) && (_wart_mies == 1 || _wart_mies == 3 || _wart_mies == 5 || _wart_mies == 7 || _wart_mies == 8 || _wart_mies == 10))
        {
            _wart_dnia = 1;
            _wart_mies++;
        }
        else if (_wart_dnia == 32 && _wart_mies == 12)
        {
            _wart_dnia = 1;
            _wart_mies = 1;
        }
        else if (_wart_dnia == 29 && _wart_mies == 2)
        {
            _wart_dnia = 1;
            _wart_mies++;
        }
        else if (_wart_dnia == 31 && (_wart_mies == 4 || _wart_mies == 6 || _wart_mies == 9 || _wart_mies == 11))
        {
            _wart_dnia = 1;
            _wart_mies++;
        }
        if (_wart_dnia < 10)
        {
            _dzien = '0' + to_string(_wart_dnia);
        }
        else { _dzien = to_string(_wart_dnia); }
        if (_wart_mies < 10)
        {
            _miesiac = '0' + to_string(_wart_mies);
        }
        else { _miesiac = to_string(_wart_mies); }
        return _dzien + '.' + _miesiac;
    }
    else
    {
        return "";
    }
}

string dodaj_minuty(string& _godz, int& _minuty)
{
    string h = _godz.substr(0, 2);
    string m = _godz.substr(3, 2);
    int godz = stoi(h);
    int min = stoi(m);
    string koniec;

    if (min + _minuty > 59)
    {
        godz += 1;
        min = _minuty + min - 60;
    }
    else
    {
        min = _minuty + min;
    }
    if (godz < 10)
    {
        koniec += '0' + to_string(godz);
    }
    else
    {
        koniec += to_string(godz);
    }
    koniec += ':';
    if (min < 10)
    {
        koniec += '0' + to_string(min);
    }
    else
    {
        koniec += to_string(min);
    }
    return koniec;
}

int roznica_godzin(string& godz_podana, string& godz)
{
    int wynik;
    if (godz_podana >= godz)
    {
        return 0;
    }
    else
    {
        string h_pod = godz_podana.substr(0, 2);
        string m_pod = godz_podana.substr(3, 2);
        string h = godz.substr(0, 2);
        string m = godz.substr(3, 2);
        if (h_pod == h)
        {
            wynik = (stoi(m) - stoi(m_pod));
        }
        else if (stoi(h_pod) + 1 == stoi(h))
        {
            wynik = 60 - stoi(m_pod) + stoi(m);
        }
        else
        {
            if (stoi(m_pod) > stoi(m))
            {
                wynik = (stoi(h) - stoi(h_pod) - 1) * 60 + 60 - stoi(m_pod) + stoi(m);
            }
            else
            {
                wynik = (stoi(h) - stoi(h_pod)) * 60 + stoi(m) - stoi(m_pod);
            }
        }
    }
    return wynik;
}


