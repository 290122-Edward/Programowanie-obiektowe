#include <iostream>
#include <string>

using namespace std;

const int rozmiar = 10;

void dodajOsobe(int *tabIndeks, string *tabImie, string *tabNazwisko, int numerIndeksu, string imie, string nazwisko){

    bool wolne_miejsce = false;
    for (int i = 0; i < rozmiar; i++){
        if (tabNazwisko[i] == ""){
            tabIndeks[i] = numerIndeksu;
            tabImie[i] = imie;
            tabNazwisko[i] = nazwisko;
            wolne_miejsce = true;
            break;
        }
    }
    if (!wolne_miejsce) {
        cout << "Lista jest pelna" << endl;
    }

    cout << "\n";
}

void ustawObecnosc(int *tabIndeks, bool *tabObecnosc, int numerIndeksu, bool obecnosc){

    bool czy_jest_taki_indeks = false;

    for (int i = 0; i < rozmiar; i++){
        if (tabIndeks[i] == numerIndeksu){
            czy_jest_taki_indeks = true;
            tabObecnosc[i] = obecnosc;
            break;
        }
    }

    if(!czy_jest_taki_indeks){
        cout << "Nie znalezionio takiego indeksu." << endl;
    }
    cout << "\n";
}

void zmienInformacje(int *tabIndeks, string *tabImie, string *tabNazwisko, int numerIndeksu){

    bool czy_jest_taki_indeks = false;
    int indeks;

    for(int i = 0; i < rozmiar; i++){
        if (tabIndeks[i] == numerIndeksu){
            czy_jest_taki_indeks = true;
            indeks = i;
            break;
        }
    }

    if(czy_jest_taki_indeks){

        int wyborZmiany;
        string noweImie;
        string noweNazwisko;
        do{
            cout << "1.Zmien imie\n2.Zmien nazwisko\n0.Anuluj\nWybierz: ";
            cin >> wyborZmiany;
            switch(wyborZmiany){
                case 1:
                    cout << "Wpisz imie: ";
                    cin >> noweImie;
                    tabImie[indeks] = noweImie;
                    cout << "\n";
                    break;
                case 2:                
                    cout << "Wpisz nazwisko: ";
                    cin >> noweNazwisko;
                    tabNazwisko[indeks] = noweNazwisko;
                    cout << "\n";
                    break;
                case 0:
                    break;
                default:
                    cout << "Niepoprawny wybor" << endl;
            }
        } while(wyborZmiany != 0);
    }

    if(!czy_jest_taki_indeks){
        cout << "Nie znalezionio takiej osoby." << endl;
    }
    cout << "\n"; 

}

void usunOsobe(int *tabIndeks, string *tabImie, string *tabNazwisko, bool *tabObecnosc, int numerIndeksu){
    
    bool czy_jest_taki_indeks = false;
    int pozycja;

    for(int i = 0; i < rozmiar; i++){
        if (tabIndeks[i] == numerIndeksu){
            czy_jest_taki_indeks = true;
            pozycja = i;
            break;
        }
    }

    if(czy_jest_taki_indeks){
        
        for(int i = pozycja; i < rozmiar - 1; i++){
            tabIndeks[i] = tabIndeks[i + 1];
            tabImie[i] = tabImie[i + 1];
            tabNazwisko[i] = tabNazwisko[i + 1];
            tabObecnosc[i] = tabObecnosc[i + 1];
        }
        tabIndeks[rozmiar - 1] = 0;
        tabImie[rozmiar - 1] = "";
        tabNazwisko[rozmiar - 1] = "";
        tabObecnosc[rozmiar - 1] = false;
               
        cout << "Usunieto studenta." << endl;
    }

    if(!czy_jest_taki_indeks){
        cout << "Nie znalezionio takiego indeksa." << endl;
    }
    cout << "\n";    
}

void drukujListe(int *tabIndeks, string *tabImie, string *tabNazwisko, bool *tabObecnosc){
    cout << "Indeks ---- Imie ---- Nazwisko ---- Obecnosc" << endl;
    for(int i = 0; i < rozmiar; i++){
        if(tabNazwisko[i] != ""){
            cout << tabIndeks[i] << " ---- " << tabImie[i] << " ---- " << tabNazwisko[i] << " ---- " << tabObecnosc[i] << endl;
        }
        else{
            break;
        }
    }
    cout << "\n";
}


int main(){

    int tabIndeks[rozmiar] = {};
    string tabImie[rozmiar] = {""};
    string tabNazwisko[rozmiar] = {""};
    bool tabObecnosc[rozmiar] = {false};
    int numerIndeksu;
    string imie;
    string nazwisko;
    bool obecnosc;
    int wybor;

    do{
        cout << "Menu:" << endl;
        cout << "1.Dodaj osobe" << endl;
        cout << "2.Ustaw obecnosc" << endl;
        cout << "3.Drukuj liste obecnosci" << endl;
        cout << "4.Zmien informacje" << endl;
        cout << "5.Usun osobe z listy" << endl;
        cout << "0.Zakoncz program" << endl;
        cout << "Wybierz: ";
        cin >> wybor;

        switch(wybor){
            case 1:
                cout << "Podaj numer indeksu: ";
                cin >> numerIndeksu;
                cout << "Podaj imie: ";
                cin >> imie;
                cout << "Podaj nazwisko: ";
                cin >> nazwisko;
                dodajOsobe(tabIndeks, tabImie, tabNazwisko, numerIndeksu, imie, nazwisko);
                break;
            case 2:
                cout << "Podaj indeks: ";
                cin >> numerIndeksu;
                cout << "Wpisz obecnosc: ";
                cin >> obecnosc;
                ustawObecnosc(tabIndeks, tabObecnosc, numerIndeksu, obecnosc);
                break;
            case 3:
                drukujListe(tabIndeks, tabImie, tabNazwisko, tabObecnosc);
                break;
            case 4:
                cout << "Podaj indeks: ";
                cin >> numerIndeksu;
                zmienInformacje(tabIndeks, tabImie, tabNazwisko, numerIndeksu);
                break;
            case 5:
                cout << "Podaj indeks: ";
                cin >> numerIndeksu;
                usunOsobe(tabIndeks, tabImie, tabNazwisko, tabObecnosc, numerIndeksu);
                break;
            case 0:
                cout << "Koniec programu.";
                break;
            default:
                cout << "Niepoprawny wybor" << endl;
        }
        } while(wybor != 0);
}

