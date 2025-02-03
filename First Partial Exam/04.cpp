/*
 Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа:
 име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).
 За оваа класа да се преоптоварат:
    •	Оператор << - за печатење на информациите за патникот во формат:
        Име на патник
        Бројот на класата (1 или 2)
        Дали има велосипед?

 Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци),
 динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број),
 број на дозволени велосипеди (цел број).
 За класата да се обезбедат:
    •	Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
    •	Оператор << - за печатење на крајната дестинација до која вози и листата на патници
    •	Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот со велосипед.
        Притоа треба да се внимава дека во пресметувањето на вкупниот број патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа,
        а потоа се дозволува да влегуваат патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот.
        На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

 Input:
 Amsterdam
 0
 5
 Ana
 1
 1
 Kate
 2
 0
 Ace
 2
 0
 Borce
 2
 1
 Mimi
 2
 0

 Result:
 Amsterdam
 Kate
 2
 0

 Ace
 2
 0

 Mimi
 2
 0

 Brojot na patnici od 1-va klasa koi ostanale bez mesto e: 0
 Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: 0
*/

#include <iostream>
#include <cstring>

using namespace std;

class Patnik {
private:
    char name[100];
    int wagon;
    bool bike;
public:
    Patnik(char *name = "", int wagon = 0, bool bike = false) {
        strcpy(this->name, name);
        this->wagon = wagon;
        this->bike = bike;
    }

    friend ostream &operator<<(ostream &out, const Patnik &p) {
        out << p.name << endl << p.wagon << endl << p.bike << endl << endl;
        return out;
    }

    bool isBike() const {
        return bike;
    }

    int getWagon() const {
        return wagon;
    }
};

class Voz {
private:
    char destination[100];
    Patnik *passengers;
    int n;
    int allowedBikes;
public:
    Voz(char *destination = "", int allowedBikes = 0) { // constructor
        strcpy(this->destination, destination);
        this->n = 0;
        this->allowedBikes = allowedBikes;
        this->passengers = new Patnik[0];
    }

    Voz(const Voz &v) { // copy-constructor
        strcpy(this->destination, v.destination);
        this->n = v.n;
        this->allowedBikes = v.allowedBikes;
        this->passengers = new Patnik[this->n];
        for (int i = 0; i < this->n; i++) {
            this->passengers[i] = v.passengers[i];
        }
    }

    ~Voz() { // destructor
        delete[] passengers;
    }

    Voz &operator=(const Voz &v) {
        if (this != &v) {
            delete[] passengers;
            strcpy(this->destination, v.destination);
            this->n = v.n;
            this->allowedBikes = v.allowedBikes;
            this->passengers = new Patnik[this->n];
            for (int i = 0; i < this->n; i++) {
                this->passengers[i] = v.passengers[i];
            }
        }
        return *this;
    }

    Voz &operator+=(const Patnik &p) {
        if (p.isBike() && allowedBikes == 0) {
            return *this;
        }
        Patnik *temp = new Patnik[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = passengers[i];
        }
        temp[n] = p;
        n++;
        delete[] passengers;
        passengers = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Voz &voz) {
        out << voz.destination << endl;
        for (int i = 0; i < voz.n; i++) {
            out << voz.passengers[i];
        }
        return out;
    }

    void patniciNemaMesto() {
        int bikes = 0, wagon1 = 0, wagon2 = 0;
        for (int i = 0; i < n; i++) {
            if (passengers[i].isBike() && passengers[i].getWagon() == 1)
                bikes++;
            if ((passengers[i].isBike() && passengers[i].getWagon() == 1) && (bikes > allowedBikes))
                wagon1++;
        }
        for (int i = 0; i < n; i++) {
            if (passengers[i].isBike() && passengers[i].getWagon() == 2)
                bikes++;
            if ((passengers[i].isBike() && passengers[i].getWagon() == 2) && (bikes > allowedBikes))
                wagon2++;
        }

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << wagon1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << wagon2 << endl;
    }
};

int main() {
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++) {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();
    return 0;
}
