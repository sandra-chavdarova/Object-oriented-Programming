/*
 Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:
    •	име (динамички алоцирана низа од знаци)
    •	пол (bool)
    •	возраст (цел број) (5 поени).
 За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)
 Дополнително за оваа класа да се преоптоварат:
 оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
 операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)

 Да се дефинира класа Maraton за кој се чуваат:
    •	локација (низа од максимум 100 знаци)
    •	низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
    •	број на учесници (цел број) (5 поени).
 За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)
 Исто така да се имплементираат следните методи:
    •	оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
    •	prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
    •	pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

 Input:
 5
 Skopje
 Elena 0 23
 Mitko 1 41
 Iskra 0 31
 Jovan 1 28
 Zoran 1 40

 Result:
 Elena
 zhenski
 23
 Iskra
 zhenski
 31
 Jovan
 mashki
 28
 32.6
*/

#include <iostream>
#include <cstring>

using namespace std;

class Ucesnik {
private:
    char *name;
    bool gender;
    int age;

    void copy(const Ucesnik &u) {
        this->gender = u.gender;
        this->age = u.age;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, u.name);
    }

public:
    Ucesnik(char *name = "", bool gender = false, int age = 0) { // constructor
        this->gender = gender;
        this->age = age;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Ucesnik() {
        delete[] name;
    }

    Ucesnik(const Ucesnik &u) {
        delete[] name;
        copy(u);
    }

    Ucesnik &operator=(const Ucesnik &u) {
        if (this != &u) {
            delete[] name;
            copy(u);
        }
        return *this;
    }

    bool operator>(const Ucesnik &u) {
        return this->age > u.age;
    }

    friend ostream &operator<<(ostream &out, const Ucesnik &u) {
        out << u.name << endl;
        if (!u.gender)
            cout << "zhenski" << endl;
        else
            cout << "mashki" << endl;
        out << u.age << endl;
        return out;
    }

    int getAge() const {
        return age;
    }
};

class Maraton {
private:
    char location[100];
    Ucesnik *participants;
    int n;

    void copy(const Maraton &m) {
        strcpy(this->location, m.location);
        this->n = m.n;
        this->participants = new Ucesnik[m.n];
        for (int i = 0; i < n; i++) {
            this->participants[i] = m.participants[i];
        }
    }

public:
    Maraton(char *location = "") {
        strcpy(this->location, location);
        this->n = 0;
        this->participants = new Ucesnik[n];
    }

    Maraton(const Maraton &m) {
        copy(m);
    }

    ~Maraton() {
        delete[] participants;
    }

    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            delete[] participants;
            copy(m);
        }
        return *this;
    }

    Maraton &operator+=(const Ucesnik &m) {
        Ucesnik *temp = new Ucesnik[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = participants[i];
        }
        temp[n] = m;
        n++;
        delete[] participants;
        participants = temp;
        return *this;
    }

    double prosecnoVozrast() {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += participants[i].getAge();
        }
        return sum / n;
    }

    void pecatiPomladi(Ucesnik &u) {
        for (int i = 0; i < n; i++) {
            if (participants[i].getAge() < u.getAge())
                cout << participants[i];
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete[] u;
    return 0;
}