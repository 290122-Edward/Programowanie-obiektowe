#include <iostream>
#include <string>

using namespace std;

const int rozmiar = 10;

class Osoba {
private:
    string imie;
    string nazwisko;
    string nr_indeksu;

public:
    Osoba() {
        imie = "";
        nazwisko = "";
        nr_indeksu = "";
    }

    void setImie(string noweImie) { imie = noweImie; }
    string getImie() { return imie; }

    void setNazwisko(string noweNazwisko) { nazwisko = noweNazwisko; }
    string getNazwisko() { return nazwisko; }

    void setIndeks(string nowyIndeks) { nr_indeksu = nowyIndeks; }
    string getIndeks() { return nr_indeksu; }
};


void dodajStudenta(Osoba listaStudentow[], string indeks, string imie, string nazwisko) {
    bool wolne_miejsce = false;
    for (int i = 0; i < rozmiar; i++) {
        if (listaStudentow[i].getIndeks() == "") {
            listaStudentow[i].setIndeks(indeks);
            listaStudentow[i].setImie(imie);
            listaStudentow[i].setNazwisko(nazwisko);
            wolne_miejsce = true;
            break;
        }
    }
    if (!wolne_miejsce) {
        cout << "Baza studentow jest pelna!" << endl;
    }
    cout << "\n";
}


void drukujBazeStudentow(Osoba listaStudentow[]) {
    cout << "--- BAZA GLOWNA STUDENTOW ---" << endl;
    cout << "Indeks ---- Imie ---- Nazwisko" << endl;
    bool ktokolwiek = false;
    for (int i = 0; i < rozmiar; i++) {
        if (listaStudentow[i].getIndeks() != "") {
            ktokolwiek = true;
            cout << listaStudentow[i].getIndeks() << " ---- " 
                 << listaStudentow[i].getImie() << " ---- " 
                 << listaStudentow[i].getNazwisko() << endl;
        }
    }
    if (!ktokolwiek) cout << "Baza jest pusta." << endl;
    cout << "\n";
}


void dodajDoGrupy(Osoba listaStudentow[], Osoba* grupa[], string indeks) {
    Osoba* wskaznikNaStudenta = nullptr;
    
    
    for (int i = 0; i < rozmiar; i++) {
        if (listaStudentow[i].getIndeks() == indeks) {
            wskaznikNaStudenta = &listaStudentow[i];
            break;
        }
    }

    if (wskaznikNaStudenta != nullptr) {
        bool wolne_miejsce = false;
        for (int i = 0; i < rozmiar; i++) {
            if (grupa[i] == nullptr) {
                grupa[i] = wskaznikNaStudenta;
                wolne_miejsce = true;
                cout << "Pomyslnie dodano studenta do grupy." << endl;
                break;
            }
        }
        if (!wolne_miejsce) cout << "Wybrana grupa jest pelna." << endl;
    } else {
        cout << "Blad: Nie znaleziono studenta o takim indeksie w bazie glownej." << endl;
    }
    cout << "\n";
}

void ustawObecnosc(Osoba* grupa[], bool tabObecnosc[], string indeks, bool obecnosc) {
    bool czy_jest_taki_indeks = false;
    for (int i = 0; i < rozmiar; i++) {
        
        if (grupa[i] != nullptr && grupa[i]->getIndeks() == indeks) {
            czy_jest_taki_indeks = true;
            tabObecnosc[i] = obecnosc;
            break;
        }
    }

    if (!czy_jest_taki_indeks) {
        cout << "Nie znaleziono studenta w tej grupie." << endl;
    }
    cout << "\n";
}


void zmienInformacje(Osoba listaStudentow[], string indeks) {
    bool czy_jest_taki_indeks = false;
    int indexBazy = -1;

    for (int i = 0; i < rozmiar; i++) {
        if (listaStudentow[i].getIndeks() == indeks) {
            czy_jest_taki_indeks = true;
            indexBazy = i;
            break;
        }
    }

    if (czy_jest_taki_indeks) {
        int wyborZmiany;
        string nowaWartosc;
        do {
            cout << "1.Zmien imie\n2.Zmien nazwisko\n0.Anuluj\nWybierz: ";
            cin >> wyborZmiany;
            switch (wyborZmiany) {
                case 1:
                    cout << "Wpisz nowe imie: ";
                    cin >> nowaWartosc;
                    listaStudentow[indexBazy].setImie(nowaWartosc);
                    cout << "\n";
                    break;
                case 2:
                    cout << "Wpisz nowe nazwisko: ";
                    cin >> nowaWartosc;
                    listaStudentow[indexBazy].setNazwisko(nowaWartosc);
                    cout << "\n";
                    break;
                case 0:
                    break;
                default:
                    cout << "Niepoprawny wybor" << endl;
            }
        } while (wyborZmiany != 0);
    } else {
        cout << "Nie znalezionio takiej osoby w bazie." << endl;
    }
    cout << "\n";
}

void usunOsobe(Osoba listaStudentow[], Osoba* grupaPPO[], Osoba* grupaAM[], string indeks) {
    bool czy_jest_taki_indeks = false;
    int pozycja = -1;

    for (int i = 0; i < rozmiar; i++) {
        if (listaStudentow[i].getIndeks() == indeks) {
            czy_jest_taki_indeks = true;
            pozycja = i;
            break;
        }
    }

    if (czy_jest_taki_indeks) {
        for (int i = 0; i < rozmiar; i++) {
            if (grupaPPO[i] != nullptr && grupaPPO[i]->getIndeks() == indeks) {
                grupaPPO[i] = nullptr;
            }
            if (grupaAM[i] != nullptr && grupaAM[i]->getIndeks() == indeks) {
                grupaAM[i] = nullptr;
            }
        }

        listaStudentow[pozycja].setIndeks("");
        listaStudentow[pozycja].setImie("");
        listaStudentow[pozycja].setNazwisko("");

        cout << "Usunieto studenta z bazy oraz ze wszystkich grup." << endl;
    } else {
        cout << "Nie znalezionio takiego indeksu." << endl;
    }
    cout << "\n";
}

void drukujListe(Osoba* grupa[], bool tabObecnosc[], string nazwaGrupy) {
    cout << "--- Lista dla grupy: " << nazwaGrupy << " ---" << endl;
    cout << "Indeks ---- Imie ---- Nazwisko ---- Obecnosc" << endl;
    
    bool ktokolwiek = false;
    for (int i = 0; i < rozmiar; i++) {
        if (grupa[i] != nullptr) {
            ktokolwiek = true;
            cout << grupa[i]->getIndeks() << " ---- " 
                 << grupa[i]->getImie() << " ---- " 
                 << grupa[i]->getNazwisko() << " ---- " 
                 << tabObecnosc[i] << endl;
        }
    }
    if(!ktokolwiek) cout << "Grupa jest pusta." << endl;
    cout << "\n";
}

int main() {
    
    Osoba listaStudentow[rozmiar]; 
    
    Osoba* grupaPPO[rozmiar] = {nullptr};
    bool tabObPPO[rozmiar] = {false};
    
    Osoba* grupaAM[rozmiar] = {nullptr};
    bool tabObAM[rozmiar] = {false};

    string numerIndeksu, imie, nazwisko;
    bool obecnosc;
    int wybor, wyborGrupy;

    do {
        cout << "Menu:" << endl;
        cout << "1.Dodaj osobe do BAZY GLOWNEJ" << endl;
        cout << "2.Przydziel osobe z bazy do GRUPY" << endl;
        cout << "3.Ustaw obecnosc w grupie" << endl;
        cout << "4.Drukuj liste obecnosci grupy" << endl;
        cout << "5.Zmien informacje o osobie" << endl;
        cout << "6.Usun osobe z bazy i grup" << endl;
        cout << "7.Drukuj baze glowna studentow" << endl;
        cout << "0.Zakoncz program" << endl;
        cout << "Wybierz: ";
        cin >> wybor;

        switch (wybor) {
            case 1:
                cout << "Podaj numer indeksu: ";
                cin >> numerIndeksu;
                cout << "Podaj imie: ";
                cin >> imie;
                cout << "Podaj nazwisko: ";
                cin >> nazwisko;
                dodajStudenta(listaStudentow, numerIndeksu, imie, nazwisko);
                break;
            case 2:
                cout << "Podaj indeks studenta do przydzialu: ";
                cin >> numerIndeksu;
                cout << "Do jakiej grupy? (1-PPO, 2-AM): ";
                cin >> wyborGrupy;
                if(wyborGrupy == 1) dodajDoGrupy(listaStudentow, grupaPPO, numerIndeksu);
                else if (wyborGrupy == 2) dodajDoGrupy(listaStudentow, grupaAM, numerIndeksu);
                else cout << "Zly wybor grupy." << endl;
                break;
            case 3:
                cout << "Podaj indeks: ";
                cin >> numerIndeksu;
                cout << "Wpisz obecnosc (1-obecny, 0-nieobecny): ";
                cin >> obecnosc;
                cout << "W jakiej grupie? (1-PPO, 2-AM): ";
                cin >> wyborGrupy;
                if(wyborGrupy == 1) ustawObecnosc(grupaPPO, tabObPPO, numerIndeksu, obecnosc);
                else if (wyborGrupy == 2) ustawObecnosc(grupaAM, tabObAM, numerIndeksu, obecnosc);
                break;
            case 4:
                cout << "Ktora grupe wydrukowac? (1-PPO, 2-AM): ";
                cin >> wyborGrupy;
                if(wyborGrupy == 1) drukujListe(grupaPPO, tabObPPO, "PPO");
                else if (wyborGrupy == 2) drukujListe(grupaAM, tabObAM, "AM");
                break;
            case 5:
                cout << "Podaj indeks studenta do modyfikacji: ";
                cin >> numerIndeksu;
                zmienInformacje(listaStudentow, numerIndeksu);
                break;
            case 6:
                cout << "Podaj indeks: ";
                cin >> numerIndeksu;
                usunOsobe(listaStudentow, grupaPPO, grupaAM, numerIndeksu);
                break;
            case 7:
                drukujBazeStudentow(listaStudentow);
                break;
            case 0:
                cout << "Koniec programu." << endl;
                break;
            default:
                cout << "Niepoprawny wybor" << endl;
        }
    } while (wybor != 0);
    
    return 0;
}