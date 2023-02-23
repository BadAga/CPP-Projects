/** @file */
#include "Pracownicy.h"
#include "Sala.h"
#include "Funkcje.h"
#include "Pacjent.h"
using namespace std;

ostream& operator<<(ostream& s, Pracownik& pracownik)
{
    s << pracownik.ID << "." << pracownik.imie << " " << pracownik.nazwisko << endl;

    return s;
}

//____________________________________________________________________DZIEN__________________________________________________________________________________________________

dzien::dzien(string& _data, vector<string> _godziny_pracy) : data(_data), godziny_pracy(_godziny_pracy), operacje_na_dzis({}) {}
dzien::dzien(string& _data) : data(_data), godziny_pracy({}), operacje_na_dzis({}) {}
dzien::~dzien() {}

//____________________________________________________________________PRACWONIK_______________________________________________________________________________________________

Pracownik::Pracownik(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien >& _tydzien, bool _dostepnosc) : ID(_ID), imie(_imie), nazwisko(_nazwisko), haslo("")
, tydzien(_tydzien), dostepnosc(_dostepnosc), godz_od_ktorej_dostepny("--:--"), nr_moich_pacjentow({}) {}
Pracownik::Pracownik(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien>& _tydzien) : Pracownik(_ID, _imie, _nazwisko, _tydzien, 0) {}
Pracownik::Pracownik() : ID(0), imie(""), nazwisko(""), haslo(""), tydzien({}), dostepnosc(0), godz_od_ktorej_dostepny("--:--"), nr_moich_pacjentow({}) {}
Pracownik::~Pracownik() {  }

int Pracownik::zwroc_id()
{
    return ID;
}

void Pracownik::ustaw_haslo(string& haslo)
{
    this->haslo = haslo;
}

void Pracownik::zmien_haslo()
{
    cout << "Wprowadz nowe haslo: ";
    string _nowe_haslo;
    cin >> _nowe_haslo;
    ustaw_haslo(_nowe_haslo);
    cout << "  ~haslo zostalo zmienione" << endl;
}

string Pracownik::zwroc_haslo()
{
    return this->haslo;
}

bool Pracownik::zaloguj()
{
    cout << "       HASLO: ";
    string podane;
    cin >> podane;
    if (this->zwroc_haslo() == podane) { cout << "Podane haslo i ID jest poprawne" << endl; return true; }
    else { cout << "Niepoprawne haslo. Sprobuj ponownie" << endl; return 0; }
}

string Pracownik::pierwszy_dzien_tygodnia()
{
    return this->tydzien[0].data;
}

bool Pracownik::czy_godziny_pracy(string& data, string& h)
{
    for (auto& dzien : this->tydzien)
    {
        if (dzien.data == data)
        {
            if (h<dzien.godziny_pracy[1] && h>dzien.godziny_pracy[0])
            {
                return 1;
            }
            else
            {
                return false;
            }
        }
    }
}

bool Pracownik::czy_dalej_bede_zajety(string& h)
{
    if (h >= this->godz_od_ktorej_dostepny) { return 1; }
    return false;
}

void Pracownik::ustaw_godzine_od_ktorej_dostepny(string& h)
{
    this->godz_od_ktorej_dostepny = h;
}



//______________________________________________________________________LEKARZ___________________________________________________________________________________________________


Lekarz::Lekarz() :Pracownik() {}

Lekarz::Lekarz(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien >& _tydzien) : Pracownik(_ID, _imie, _nazwisko, _tydzien)
{
    string auto_haslo = generuj_haslo();
    ustaw_haslo(auto_haslo);
}

Lekarz::~Lekarz() {}

string Lekarz::generuj_haslo()
{
    string haslo = "Lekarz" + to_string(zwroc_id());
    return haslo;
}

void Lekarz::wyswietl_grafik()
{
    for (auto& elem : this->tydzien)
    {
        cout << elem.data << "  " << elem.godziny_pracy[0] << " - " << elem.godziny_pracy[1] << " ";
        if (elem.operacje_na_dzis.size() == 0) { cout << "brak zaplanowanych operacji" << endl; }
        else
        {
            for (auto& operacja : elem.operacje_na_dzis)
            {
                cout << "+ Zaplanowano " << operacja[2] << " na: " << operacja[0] << " do: " << operacja[1] << endl;
            }
        }
    }
}

void Lekarz::zmien_grafik(string& aktualna_data)
{
    bool znaleziony = 0;
    bool przerwij = 0;
    while (znaleziony == 0 || przerwij == 0)
    {
        cout << "Na ktory dzien chcesz zmienic grafik? Podaj date:";
        string odp;
        string data;
        cin >> data;
        for (auto& elem : this->tydzien)
        {
            if (elem.data == data)
            {
                if (data > aktualna_data)
                {
                    znaleziony = 1;
                    cout << "Podaj godzine wyjscia i wyjscia w formacie GG:MM. wolne wpisz jako --:-- : " << endl;
                    string nowe_wej, nowe_wyj;
                    cin >> nowe_wej >> nowe_wyj;
                    if (sprawdz_format_godziny(nowe_wej) != 1 || sprawdz_format_godziny(nowe_wyj) != 1)
                    {
                        znaleziony = 0;
                        cout << "~Niepoprawny format godziny. Sprobuj ponownie" << endl;
                        break;
                    }
                    else
                    {
                        elem.godziny_pracy[0] = nowe_wej;
                        elem.godziny_pracy[1] = nowe_wyj;
                        cout << "~Godziny zostaly zmienione" << endl;
                        break;
                    }
                }
            }
        }
        if (znaleziony == 0)
        {
            cout << endl << "~Data musi sie zawierac w aktualnym tygodniu; musi byc po " << aktualna_data << endl;
            cout << "Czy chcesz przerwac? Wpisz T jesli tak: " << endl;
            cin >> odp;
            {
                if (odp == "T")
                {
                    przerwij = 1;
                }
            }
        }
        if (przerwij == 1) { break; }
        else { break; }
    }
}

void Lekarz::dodaj_operacje(string& data, string& h)
{
    cout << "Podaj date oraz godzine rozpoczecia i zakonczenia planowanej operacji, pamietajac, ze dodac operacje mozesz od nastepnego dnia: " << endl;
    string op_data, op_rozp_godzina, op_zak_godzina;
    cin >> op_data >> op_rozp_godzina >> op_zak_godzina;
    bool czy_w_zakresie = 0;
    if (sprawdz_format_godziny(op_rozp_godzina) && sprawdz_format_godziny(op_zak_godzina) && sprawdz_format_daty(op_data))
    {
        int indeks_aktualny_czas = 0, indeks_podanej_daty = 0, i = 0;
        for (auto& dzien : tydzien)
        {

            if (dzien.data == op_data)
            {
                indeks_podanej_daty = i;
                czy_w_zakresie = 1;
            }
            else if (dzien.data == data)
            {
                indeks_aktualny_czas = i;
            }
            i++;
        }
        if (czy_w_zakresie == 0) { cout << "Niepoprawne dane. Data musi zawierac sie w aktualnym tygodniu" << endl; }
        if (indeks_aktualny_czas < indeks_podanej_daty)
        {
            if (this->tydzien[indeks_podanej_daty].operacje_na_dzis.size() == 0)
            {
                cout << "Jakie to wydarzenie?" << endl;
                string opis_operacji;
                cin.ignore();
                getline(cin, opis_operacji);
                vector<string> nowa_operacja = { op_rozp_godzina,op_zak_godzina,opis_operacji };
                this->tydzien[indeks_podanej_daty].operacje_na_dzis.push_back(nowa_operacja);
                cout << "~dodano wydarzenie do grafiku" << endl;
            }
            else
            {
                bool nie_nachodzi = 1;
                for (auto& operacja : this->tydzien[indeks_podanej_daty].operacje_na_dzis)
                {
                    if ((op_rozp_godzina >= operacja[0] && op_zak_godzina <= operacja[1]) || (op_rozp_godzina >= operacja[0] && op_rozp_godzina <= operacja[1])
                        || (op_rozp_godzina <= operacja[0] && op_zak_godzina >= operacja[0]))
                    {
                        nie_nachodzi = 0;
                    }
                }
                if (nie_nachodzi)
                {
                    cout << "Jakie to wydarzenie?" << endl;
                    string opis_operacji;
                    cin.ignore();
                    getline(cin, opis_operacji);
                    vector<string> nowa_operacja = { op_rozp_godzina,op_zak_godzina,opis_operacji };
                    this->tydzien[indeks_podanej_daty].operacje_na_dzis.push_back(nowa_operacja);
                    cout << "~dodano wydarzenie do grafiku" << endl;
                }
                else
                {
                    cout << "W tym terminie juz masz zaplanowane wydarzenie. Sprobuj ponownie wprowadzajac poprawne dane" << endl;
                }
            }
        }
        else
        {
            cout << "Wybierz date od: " << data << " do " << this->tydzien[6].data << endl;
        }
    }
    else
    {
        cout << "Nie poprawne dane. Poprawny format godziny: GG:MM .Poprawny format daty: DD.MM" << endl;
    }
}

bool Lekarz::czy_mam_operacje(string& data, string& h)
{
    for (auto& dzien : this->tydzien)
    {
        if (dzien.data == data)
        {
            bool ok = 1;
            for (auto& operacja : dzien.operacje_na_dzis)
            {
                if (h <= operacja[1] && h >= operacja[0])
                {
                    ok = 0;
                }
            }
            if (ok)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}

void Lekarz::aktualizacja(string& data, string& h, string& h_uzdrowienia)
{
    if (this->czy_godziny_pracy(data, h) && this->czy_mam_operacje(data, h) && this->czy_dalej_bede_zajety(h)
        && this->czy_godziny_pracy(data, h_uzdrowienia) && this->czy_mam_operacje(data, h_uzdrowienia) && this->czy_dalej_bede_zajety(h_uzdrowienia))
    {
        this->dostepnosc = 1;
    }
    else
    {
        this->dostepnosc = 0;
    }
}

vector<int> Lekarz::zwroc_moich_pacjentow()
{
    return this->nr_moich_pacjentow;
}


//_____________________________________________________________________PIELEGNIARKA________________________________________________________________________________________________

Pielegniarka::Pielegniarka() :Pracownik() {  }

Pielegniarka::Pielegniarka(int& _ID, const string& _imie, const string& _nazwisko, vector<dzien >& _tydzien) : Pracownik(_ID, _imie, _nazwisko, _tydzien)
{
    string auto_haslo = generuj_haslo();
    ustaw_haslo(auto_haslo);
}

Pielegniarka::~Pielegniarka() { }

string Pielegniarka::generuj_haslo()
{
    string haslo = "Pielegniarka" + to_string(zwroc_id());
    return haslo;
}

void Pielegniarka::wyswietl_grafik()
{
    for (auto& elem : this->tydzien)
    {
        cout << elem.data << "  " << elem.godziny_pracy[0] << " - " << elem.godziny_pracy[1] << endl;
    }
}

void Pielegniarka::zmien_grafik(string& aktualna_data)
{
    {
        bool znaleziony = 0;
        bool przerwij = 0;
        while (znaleziony == 0 || przerwij == 0)
        {
            cout << "Na ktory dzien chcesz zmienic grafik? Podaj date:";
            string odp;
            string data;
            cin >> data;
            for (auto& elem : this->tydzien)
            {
                if (elem.data == data)
                {
                    if (data > aktualna_data)
                    {
                        znaleziony = 1;
                        cout << "Podaj godzine wyjscia i wyjscia w formacie GG:MM. wolne wpisz jako --:-- : " << endl;
                        string nowe_wej, nowe_wyj;
                        cin >> nowe_wej >> nowe_wyj;
                        if (sprawdz_format_godziny(nowe_wej) != 1 || sprawdz_format_godziny(nowe_wyj) != 1)
                        {
                            znaleziony = 0;
                            cout << "~Niepoprawny format godziny. Sprobuj ponownie" << endl;
                            break;
                        }
                        else
                        {
                            elem.godziny_pracy[0] = nowe_wej;
                            elem.godziny_pracy[1] = nowe_wyj;
                            cout << "~Godziny zostaly zmienione" << endl;
                            break;
                        }
                    }
                }
            }
            if (znaleziony == 0)
            {
                cout << endl << "~Data musi sie zawierac w aktualnym tygodniu; musi byc po " << aktualna_data << endl;
                cout << "Czy chcesz przerwac? Wpisz T jesli tak: " << endl;
                cin >> odp;
                {
                    if (odp == "T")
                    {
                        przerwij = 1;
                    }
                }
            }
            if (przerwij == 1) { break; }
            else { break; }
        }
    }
}

void Pielegniarka::aktualizacja(string& data, string& h, string& h_uzdrowienia)
{
    if (this->czy_godziny_pracy(data, h) && this->czy_dalej_bede_zajety(h) && this->czy_godziny_pracy(data, h_uzdrowienia) && this->czy_dalej_bede_zajety(h_uzdrowienia))
    {
        this->dostepnosc = 1;
    }
    else
    {
        this->dostepnosc = 0;
    }
}


