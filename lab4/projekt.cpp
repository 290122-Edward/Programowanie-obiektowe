#include <iostream>
#include <string>

using namespace std;

const int rozmiar = 10;

class IPrzedstawialny {
public:
    virtual string przedstawSie() = 0;
    virtual ~IPrzedstawialny() {} 
};

class Osoba {
protected:
    string imie;
    string nazwisko;

public:
    Osoba(string i = "", string n = "") {
        imie = i;
        nazwisko = n;
    }
    virtual ~Osoba() {} 

    void setImie(string noweImie) { imie = noweImie; }
    string getImie() { return imie; }

    void setNazwisko(string noweNazwisko) { nazwisko = noweNazwisko; }
    string getNazwisko() { return nazwisko; }

    virtual string getId() = 0; 
};

class Pracownik : public Osoba, public IPrzedstawialny {
private:
    string id_pracownika;

public:
    Pracownik(string id, string i, string n) : Osoba(i, n) {
        id_pracownika = id;
    }
    
    string getId() override { return id_pracownika; }
    
    string przedstawSie() override {
        return "PRACOWNIK: " + imie + " " + nazwisko + " (ID: " + id_pracownika + ")";
    }
};

class Student : public Osoba, public IPrzedstawialny {
protected:
    string nr_indeksu;

public:
    Student(string idx, string i, string n) : Osoba(i, n) {
        nr_indeksu = idx;
    }
    
    string getId() override { return nr_indeksu; }
    
    string przedstawSie() override {
        return "STUDENT: " + imie + " " + nazwisko + " (Indeks: " + nr_indeksu + ")";
    }
};

class StudentZaoczny : public Student {
public:
    StudentZaoczny(string idx, string i, string n) : Student(idx, i, n) {}
    
    string przedstawSie() override {
        return "STUDENT ZAOCZNY: " + imie + " " + nazwisko + " (Indeks: " + nr_indeksu + ")";
    }
};

void drukuj(IPrzedstawialny* obj) {
    if (obj != nullptr) {
        cout << obj->przedstawSie();
    }
}

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

    void ustawObecnosc(string id, bool ob) {
        bool czy_jest_taki_indeks = false;
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr && tab[i]->getId() == id) {
                czy_jest_taki_indeks = true;
                if (dynamic_cast<Student*>(tab[i]) != nullptr) {
                    obecnosc[i] = ob;
                } else {
                    cout << "Wybrana osoba to pracownik. Pracownikowi nie ustawia sie obecnosci." << endl;
                }
                break;
            }
        }
        if (!czy_jest_taki_indeks) {
            cout << "Nie znaleziono osoby w tej grupie." << endl;
        }
        cout << "\n";
    }

    void dodajDoListy(Osoba* student) {
        if (student == nullptr) return;
        
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr && tab[i]->getId() == student->getId()) {
                cout << "Blad: Ta osoba znajduje sie juz w tej grupie." << endl;
                cout << "\n";
                return;
            }
        }

        bool wolne_miejsce = false;
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] == nullptr) {
                tab[i] = student;
                obecnosc[i] = false;
                wolne_miejsce = true;
                cout << "Pomyslnie dodano osobe do grupy." << endl;
                break;
            }
        }
        if (!wolne_miejsce) cout << "Wybrana grupa jest pelna." << endl;
        cout << "\n";
    }

    void usunZListy(string id) {
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr && tab[i]->getId() == id) {
                tab[i] = nullptr;
                obecnosc[i] = false;
            }
        }
    }

    void wydrukujListe() {
        cout << "--- Lista dla grupy: " << nazwaGrupy << " ---" << endl;
        bool ktokolwiek = false;
        
        for (int i = 0; i < rozmiar; i++) {
            if (tab[i] != nullptr) {
                ktokolwiek = true;
                
                IPrzedstawialny* ip = dynamic_cast<IPrzedstawialny*>(tab[i]);
                if (ip) {
                    drukuj(ip);
                    if (dynamic_cast<Student*>(tab[i]) != nullptr) {
                        cout << " ---- Obecnosc: " << obecnosc[i] << endl;
                    } else {
                        cout << endl;
                    }
                }
            }
        }
        if(!ktokolwiek) cout << "Grupa jest pusta." << endl;
        cout << "\n";
    }
};

class BazaOsob {
private:
    Osoba* lista[rozmiar];

public:
    BazaOsob() {
        for (int i = 0; i < rozmiar; i++) lista[i] = nullptr;
    }

    ~BazaOsob() {
        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr) delete lista[i]; 
        }
    }

    void dodajOsobe(Osoba* nowaOsoba) {
        if (nowaOsoba == nullptr) return;

        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr && lista[i]->getId() == nowaOsoba->getId()) {
                cout << "Blad: Osoba o podanym ID juz istnieje w bazie!" << endl;
                cout << "\n";
                delete nowaOsoba;
                return;
            }
        }

        bool wolne_miejsce = false;
        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] == nullptr) {
                lista[i] = nowaOsoba;
                wolne_miejsce = true;
                break;
            }
        }
        if (!wolne_miejsce) {
            cout << "Baza jest pelna!" << endl;
            delete nowaOsoba; 
        }
        cout << "\n";
    }

    void drukujBaze() {
        cout << "--- BAZA GLOWNA OSOB ---" << endl;
        bool ktokolwiek = false;
        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr) {
                ktokolwiek = true;
                IPrzedstawialny* ip = dynamic_cast<IPrzedstawialny*>(lista[i]);
                if (ip) {
                    drukuj(ip);
                    cout << endl;
                }
            }
        }
        if (!ktokolwiek) cout << "Baza jest pusta." << endl;
        cout << "\n";
    }

    void zmienInformacje(string id) {
        bool czy_jest_taki_indeks = false;
        int indexBazy = -1;

        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr && lista[i]->getId() == id) {
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
                        lista[indexBazy]->setImie(nowaWartosc);
                        cout << "\n";
                        break;
                    case 2:
                        cout << "Wpisz nowe nazwisko: ";
                        cin >> nowaWartosc;
                        lista[indexBazy]->setNazwisko(nowaWartosc);
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

    Osoba* znajdzOsobe(string id) {
        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr && lista[i]->getId() == id) {
                return lista[i];
            }
        }
        return nullptr;
    }

    void usunOsobe(ListaObecnosci* ppo, ListaObecnosci* am, string id) {
        bool czy_jest_taki_indeks = false;
        int pozycja = -1;

        for (int i = 0; i < rozmiar; i++) {
            if (lista[i] != nullptr && lista[i]->getId() == id) {
                czy_jest_taki_indeks = true;
                pozycja = i;
                break;
            }
        }

        if (czy_jest_taki_indeks) {
            if(ppo != nullptr) ppo->usunZListy(id);
            if(am != nullptr) am->usunZListy(id);

            delete lista[pozycja]; 
            lista[pozycja] = nullptr; 

            cout << "Usunieto osobe z bazy oraz ze wszystkich grup." << endl;
        } else {
            cout << "Nie znalezionio takiego indeksu." << endl;
        }
        cout << "\n";
    }
};

class InterfejsUzytkownika {
private:
    BazaOsob* bazaGlowna;
    ListaObecnosci* grupaPPO;
    ListaObecnosci* grupaAM;

public:
    InterfejsUzytkownika() {
        bazaGlowna = nullptr;
        grupaPPO = nullptr;
        grupaAM = nullptr;
    }

    void setBazaOsob(BazaOsob* b) { bazaGlowna = b; }
    void setGrupaPPO(ListaObecnosci* g) { grupaPPO = g; }
    void setGrupaAM(ListaObecnosci* g) { grupaAM = g; }

    void petla() {
        int wybor, wyborTypu, wyborGrupy;
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
            cout << "7.Drukuj baze glowna osob" << endl;
            cout << "0.Zakoncz program" << endl;
            cout << "Wybierz: ";
            cin >> wybor;

            switch (wybor) {
                case 1:
                    cout << "Kogo chcesz dodac?\n1.Student\n2.Student Zaoczny\n3.Pracownik\nWybierz: ";
                    cin >> wyborTypu;
                    cout << "Podaj numer indeksu/ID: "; 
                    cin >> numerIndeksu;
                    cout << "Podaj imie: "; 
                    cin >> imie;
                    cout << "Podaj nazwisko: "; 
                    cin >> nazwisko;
                    
                    if (wyborTypu == 1) bazaGlowna->dodajOsobe(new Student(numerIndeksu, imie, nazwisko));
                    else if (wyborTypu == 2) bazaGlowna->dodajOsobe(new StudentZaoczny(numerIndeksu, imie, nazwisko));
                    else if (wyborTypu == 3) bazaGlowna->dodajOsobe(new Pracownik(numerIndeksu, imie, nazwisko));
                    else cout << "Zly wybor." << endl;
                    break;
                case 2:
                    cout << "Podaj indeks studenta do przydzialu: "; 
                    cin >> numerIndeksu;
                    cout << "Do jakiej grupy? (1-PPO, 2-AM): "; 
                    cin >> wyborGrupy;
                    {
                        Osoba* wskaznikNaStudenta = bazaGlowna->znajdzOsobe(numerIndeksu);
                        if (wskaznikNaStudenta != nullptr) {
                            if (wyborGrupy == 1) grupaPPO->dodajDoListy(wskaznikNaStudenta);
                            else if (wyborGrupy == 2) grupaAM->dodajDoListy(wskaznikNaStudenta);
                            else cout << "Zly wybor grupy." << endl;
                        } else {
                            cout << "Blad: Nie znaleziono studenta o takim indeksie w bazie glownej." << endl;
                            cout << "\n";
                        }
                    }
                    break;
                case 3:
                    cout << "Podaj indeks: "; 
                    cin >> numerIndeksu;
                    cout << "Wpisz obecnosc (1-obecny, 0-nieobecny): "; 
                    cin >> obecnosc;
                    cout << "W jakiej grupie? (1-PPO, 2-AM): "; 
                    cin >> wyborGrupy;
                    if (wyborGrupy == 1) grupaPPO->ustawObecnosc(numerIndeksu, obecnosc);
                    else if (wyborGrupy == 2) grupaAM->ustawObecnosc(numerIndeksu, obecnosc);
                    break;
                case 4:
                    cout << "Ktora grupe wydrukowac? (1-PPO, 2-AM): "; 
                    cin >> wyborGrupy;
                    if (wyborGrupy == 1) grupaPPO->wydrukujListe();
                    else if (wyborGrupy == 2) grupaAM->wydrukujListe();
                    break;
                case 5:
                    cout << "Podaj indeks studenta do modyfikacji: "; 
                    cin >> numerIndeksu;
                    bazaGlowna->zmienInformacje(numerIndeksu);
                    break;
                case 6:
                    cout << "Podaj indeks: "; 
                    cin >> numerIndeksu;
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
    BazaOsob glownaBaza;
    ListaObecnosci listaPPO("PPO");
    ListaObecnosci listaAM("AM");

    InterfejsUzytkownika ui;
    ui.setBazaOsob(&glownaBaza);
    ui.setGrupaPPO(&listaPPO);
    ui.setGrupaAM(&listaAM);

    ui.petla();

    return 0;
}