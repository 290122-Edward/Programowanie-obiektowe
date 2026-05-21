#include <iostream>
#include <string>

using namespace std;

const int rozmiar = 20;

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

class ListaObecnosci {
private:
    Osoba* tab[rozmiar];
    bool obecnosc[rozmiar];
    string nazwaGrupy;

public:
    ListaObecnosci(string nazwa = "") {
        nazwaGrupy = nazwa;
        for (int i = 0; i < rozmiar; i++) {
            tab[i] = nullptr;
            obecnosc[i] = false;
        }
    }

    void ustawObecnosc(string indeks, bool ob) {
        bool czy_jest_taki_indeks = false;
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr && tab[i]->getIndeks() == indeks) {
                czy_jest_taki_indeks = true;
                obecnosc[i] = ob;
                break;
            }
        }
        if (!czy_jest_taki_indeks) {
            cout << "Nie znaleziono studenta w grupie " << nazwaGrupy << "." << endl;
        }
    }

    void dodajDoListy(Osoba* student) {
        if (student == nullptr) return;
        bool wolne_miejsce = false;
        
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] == nullptr) {
                tab[i] = student;
                obecnosc[i] = false;
                wolne_miejsce = true;
                cout << "Pomyslnie dodano studenta do grupy " << nazwaGrupy << "." << endl;
                break;
            }
        }
        if (!wolne_miejsce) cout << "Grupa " << nazwaGrupy << " jest pelna." << endl;
    }

    void usunZListy(string indeks) {
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr && tab[i]->getIndeks() == indeks) {
                tab[i] = nullptr;
                obecnosc[i] = false;
            }
        }
    }

    void wydrukujListe() {
        cout << "--- Lista dla grupy: " << nazwaGrupy << " ---" << endl;
        cout << "Indeks ---- Imie ---- Nazwisko ---- Obecnosc" << endl;
        
        bool ktokolwiek = false;
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr) {
                ktokolwiek = true;
                cout << tab[i]->getIndeks() << " ---- " 
                     << tab[i]->getImie() << " ---- " 
                     << tab[i]->getNazwisko() << " ---- " 
                     << (obecnosc[i] ? "Obecny" : "Nieobecny") << endl;
            }
        }
        if(!ktokolwiek) cout << "Grupa jest pusta." << endl;
        cout << "\n";
    }
};

class BazaStudentow {
private:
    Osoba listaStudentow[rozmiar];

public:
    void dodajStudenta(string indeks, string imie, string nazwisko) {
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
        if (!wolne_miejsce) cout << "Baza studentow jest pelna!" << endl;
        cout << "\n";
    }

    void drukujBaze() {
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

    void zmienInformacje(string indeks) {
        int indexBazy = -1;
        for (int i = 0; i < rozmiar; i++) {
            if (listaStudentow[i].getIndeks() == indeks) {
                indexBazy = i;
                break;
            }
        }

        if (indexBazy != -1) {
            int wyborZmiany;
            string nowaWartosc;
            do {
                cout << "1.Zmien imie\n2.Zmien nazwisko\n0.Anuluj\nWybierz: ";
                cin >> wyborZmiany;
                if (wyborZmiany == 1) {
                    cout << "Wpisz nowe imie: ";
                    cin >> nowaWartosc;
                    listaStudentow[indexBazy].setImie(nowaWartosc);
                } else if (wyborZmiany == 2) {
                    cout << "Wpisz nowe nazwisko: ";
                    cin >> nowaWartosc;
                    listaStudentow[indexBazy].setNazwisko(nowaWartosc);
                }
                cout << "\n";
            } while (wyborZmiany != 0);
        } else {
            cout << "Nie znalezionio takiej osoby w bazie.\n" << endl;
        }
    }

    Osoba* znajdzStudenta(string indeks) {
        for (int i = 0; i < rozmiar; i++) {
            if (listaStudentow[i].getIndeks() == indeks) {
                return &listaStudentow[i];
            }
        }
        return nullptr;
    }

    void usunOsobe(ListaObecnosci* ppo, ListaObecnosci* am, string indeks) {
        int pozycja = -1;
        for (int i = 0; i < rozmiar; i++) {
            if (listaStudentow[i].getIndeks() == indeks) {
                pozycja = i;
                break;
            }
        }

        if (pozycja != -1) {
            if(ppo != nullptr) ppo->usunZListy(indeks);
            if(am != nullptr) am->usunZListy(indeks);

            listaStudentow[pozycja].setIndeks("");
            listaStudentow[pozycja].setImie("");
            listaStudentow[pozycja].setNazwisko("");

            cout << "Usunieto studenta z bazy oraz ze wszystkich grup." << endl;
        } else {
            cout << "Nie znalezionio takiego indeksu." << endl;
        }
        cout << "\n";
    }
};

class InterfejsUzytkownika {
private:
    BazaStudentow* bazaGlowna;
    ListaObecnosci* grupaPPO;
    ListaObecnosci* grupaAM;

public:
    InterfejsUzytkownika() {
        bazaGlowna = nullptr;
        grupaPPO = nullptr;
        grupaAM = nullptr;
    }

    void setBazaOsob(BazaStudentow* b) { bazaGlowna = b; }
    void setGrupaPPO(ListaObecnosci* g) { grupaPPO = g; }
    void setGrupaAM(ListaObecnosci* g) { grupaAM = g; }

    void petla() {
        if (bazaGlowna == nullptr || grupaPPO == nullptr || grupaAM == nullptr) {
            cout << "Blad: Nie podpieto baz danych do interfejsu!" << endl;
            return;
        }

        int wybor, wyborGrupy;
        string numerIndeksu, imie, nazwisko;
        bool obecnosc;

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
            cout << "\n";

            switch (wybor) {
                case 1:
                    cout << "Podaj numer indeksu: "; cin >> numerIndeksu;
                    cout << "Podaj imie: "; cin >> imie;
                    cout << "Podaj nazwisko: "; cin >> nazwisko;
                    bazaGlowna->dodajStudenta(numerIndeksu, imie, nazwisko);
                    break;
                case 2:
                    cout << "Podaj indeks studenta do przydzialu: "; cin >> numerIndeksu;
                    cout << "Do jakiej grupy? (1-PPO, 2-AM): "; cin >> wyborGrupy;
                    {
                        Osoba* znaleziony = bazaGlowna->znajdzStudenta(numerIndeksu);
                        if (znaleziony != nullptr) {
                            if (wyborGrupy == 1) grupaPPO->dodajDoListy(znaleziony);
                            else if (wyborGrupy == 2) grupaAM->dodajDoListy(znaleziony);
                            else cout << "Zly wybor grupy." << endl;
                        } else {
                            cout << "Blad: Nie znaleziono studenta o takim indeksie w bazie glownej." << endl;
                        }
                    }
                    cout << "\n";
                    break;
                case 3:
                    cout << "Podaj indeks: "; cin >> numerIndeksu;
                    cout << "Wpisz obecnosc (1-obecny, 0-nieobecny): "; cin >> obecnosc;
                    cout << "W jakiej grupie? (1-PPO, 2-AM): "; cin >> wyborGrupy;
                    if (wyborGrupy == 1) grupaPPO->ustawObecnosc(numerIndeksu, obecnosc);
                    else if (wyborGrupy == 2) grupaAM->ustawObecnosc(numerIndeksu, obecnosc);
                    cout << "\n";
                    break;
                case 4:
                    cout << "Ktora grupe wydrukowac? (1-PPO, 2-AM): "; cin >> wyborGrupy;
                    if (wyborGrupy == 1) grupaPPO->wydrukujListe();
                    else if (wyborGrupy == 2) grupaAM->wydrukujListe();
                    break;
                case 5:
                    cout << "Podaj indeks studenta do modyfikacji: "; cin >> numerIndeksu;
                    bazaGlowna->zmienInformacje(numerIndeksu);
                    break;
                case 6:
                    cout << "Podaj indeks do usuniecia: "; cin >> numerIndeksu;
                    bazaGlowna->usunOsobe(grupaPPO, grupaAM, numerIndeksu);
                    break;
                case 7:
                    bazaGlowna->drukujBaze();
                    break;
                case 0:
                    cout << "Koniec programu." << endl;
                    break;
                default:
                    cout << "Niepoprawny wybor" << endl;
            }
        } while (wybor != 0);
    }
};

int main() {

    BazaStudentow glownaBaza;
    ListaObecnosci listaPPO("PPO");
    ListaObecnosci listaAM("AM");

    InterfejsUzytkownika ui;

    ui.setBazaOsob(&glownaBaza);
    ui.setGrupaPPO(&listaPPO);
    ui.setGrupaAM(&listaAM);

    ui.petla();

    return 0;
}