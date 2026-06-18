#include <iostream>
#include <string>

using namespace std;

class Osoba {
private: 
    string imie;
    string nazwisko;
    
public:
    Osoba(string i, string n = "") : imie(i), nazwisko(n) {}
    
    virtual ~Osoba() = default;

    string getImie() const { return imie; }
    string getNazwisko() const { return nazwisko; }

    // Proste przypisanie
    void setImie(string i) { imie = i; }
    void setNazwisko(string n) { nazwisko = n; }

    virtual void przedstawSie() const {
        cout << "Osoba: " << imie << endl;
    }
};

class Student : public Osoba {
private:
    string nr_indeksu;

public:
    Student(string i, string nr) : Osoba(i), nr_indeksu(nr) {}

    void setNrIndeksu(string nr) { nr_indeksu = nr; }
    string getNrIndeksu() const { return nr_indeksu; }

    void przedstawSie() const override {
        cout << "STUDENT: " << getImie() << ", Indeks: " << nr_indeksu << endl;
    }
};

class Pracownik : public Osoba {
private:
    string id_pracownika;
    
public:
    Pracownik(string i, string id) : Osoba(i), id_pracownika(id) {}

    void setIdPracownika(string id) { id_pracownika = id; }
    string getIdPracownika() const { return id_pracownika; }

    void przedstawSie() const override {
        cout << "PRACOWNIK: " << getImie() << ", ID: " << id_pracownika << endl;
    }
};

int main() {
    Osoba os1("Edward");
    Student stud1("Jan", "123456");
    Pracownik prac1("Anna", "P-987");

    Osoba* tab[3];
    tab[0] = &os1;
    tab[1] = &stud1;
    tab[2] = &prac1;

    for (int i = 0; i < 3; ++i) {
        tab[i]->przedstawSie(); 
    }

    return 0;
}