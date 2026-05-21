#include <iostream>
#include <string>

using namespace std;

class Osoba {
    protected:
        string imie;
        string nazwisko;
        
    public:
        string getImie() { return imie; }
        string getNazwisko() { return nazwisko; }

        void setImie(string i) { imie = i; }
        void setNazwisko(string n) { nazwisko = n; }
};

class Student : public Osoba {
    private:
        string nr_indeksu;

    public:
        void setNrIndeksu(string nr) { nr_indeksu = nr; }
        string getNrIndeksu() { return nr_indeksu; }

        void drukujImieStudenta() {
            cout << "STUDENT: " << imie << endl;
        }
};

class Pracownik : public Osoba {
    private:
        string id_pracownika;
        
    public:
        void setIdPracownika(string id) { id_pracownika = id; }
        string getIdPracownika() { return id_pracownika; }
};

int main() {
    Osoba os1;
    Student stud1;
    Pracownik prac1;

    os1.setImie("Edward");
    os1.setNazwisko("Piatkewycz");

    stud1.setImie("Jan");
    stud1.setNazwisko("Kowalski");
    stud1.setNrIndeksu("290555");
    
    prac1.setImie("Anna");
    prac1.setIdPracownika("290111");

    cout << "Imie osoby bazowej: " << os1.getImie() << endl;
    
    stud1.drukujImieStudenta(); 
    
    return 0;
}