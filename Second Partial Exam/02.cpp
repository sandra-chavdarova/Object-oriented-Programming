/*
 Да се дефинира класа Vozac во која се чуваат информации за:
    •	име (низа од максимум 100 знаци)
    •	возраст (цел број)
    •	број на трки (цел број)
    •	дали е ветеран (да/не).
 Да се преоптоварат:
    •	операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
    •	операторот == за споредување на два возачи според заработувачката по трка.

 Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.
 За автомобилистот дополнително се чува:
    •	цена на автомобилот (децимален број).
 За мотоциклистот дополнително се чува:
    •	моќност на мотор (цел број).
 Заработувачката по трка на возачите се пресметува како:
    o	за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
    o	за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
 Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:
    o	за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
    o	за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
 Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac,
 нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

 Input:
 5
 1
 Hamilton 30 95 0 55000
 Vetel 26 88 1 800
 Barrichello 38 198 0 810
 Rossi 32 130 1 800
 Lorenzo 24 45 0 900
 VozacX 38 198 1 800

 Result:
 === DANOK ===
 Hamilton
 30
 95
 1650
 Vetel
 26
 88
 VETERAN
 4000
 Barrichello
 38
 198
 3240
 Rossi
 32
 130
 VETERAN
 4000
 Lorenzo
 24
 45
 3600
 === VOZAC X ===
 VozacX
 38
 198
 VETERAN
 === SO ISTA ZARABOTUVACKA KAKO VOZAC X ===
 2
*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Vozac {
protected:
    char name[105];
    int age;
    int races;
    bool veteran;
public:
    Vozac(char *name = "", int age = 0, int races = 0, bool veteran = true) {
        strcpy(this->name, name);
        this->age = age;
        this->races = races;
        this->veteran = veteran;
    }

    ~Vozac() {}

    Vozac(const Vozac &v) {
        strcpy(this->name, v.name);
        this->age = v.age;
        this->races = v.races;
        this->veteran = v.veteran;
    }

    friend ostream &operator<<(ostream &out, const Vozac &v) {
        out << v.name << endl << v.age << endl << v.races << endl;
        if (v.veteran)
            out << "VETERAN" << endl;
        return out;
    }

    virtual float zarabotuvacka() = 0;

    virtual float danok() = 0;

    bool operator==(Vozac &v) {
        return zarabotuvacka() == v.zarabotuvacka();
    }
};

class Avtomobilist : public Vozac {
private:
    float price;

public:
    Avtomobilist(char *name = "", int age = 0, int races = 0, bool veteran = true, float price = 0.0) : Vozac(name,
                                                                                                              age,
                                                                                                              races,
                                                                                                              veteran) {
        this->price = price;
    }

    ~Avtomobilist() {}

    Avtomobilist(const Avtomobilist &a) : Vozac(a) {
        this->price = a.price;
    }

    float zarabotuvacka() {
        return price / 5;
    }

    float danok() {
        if (races > 10)
            return 0.15f * zarabotuvacka();
        else
            return 0.1f * zarabotuvacka();
    }

};

class Motociklist : public Vozac {
private:
    int power;

public:
    Motociklist(char *name = "", int age = 0, int races = 0, bool veteran = true, int power = 0) : Vozac(name, age,
                                                                                                         races,
                                                                                                         veteran) {
        this->power = power;
    }

    ~Motociklist() {}

    Motociklist(const Motociklist &m) : Vozac(m) {
        this->power = m.power;
    }

    float zarabotuvacka() {
        return (float) power * 20;
    }

    float danok() {
        if (veteran)
            return 0.25f * zarabotuvacka();
        else
            return 0.2f * zarabotuvacka();
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *vozac) {
    int counter = 0;
    for (int i = 0; i < n; ++i) {
        if (*vozac == *vozaci[i])
            counter++;
    }
    return counter;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}
