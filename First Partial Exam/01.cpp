/*
 Да се дефинира класата Pesna во која се чуваат информации за (5 поени):
    - име на песна (динамички алоцирано поле од знаци)
    - времетраење на песната во минути
    - тип на песна кој може да биде: поп, рап или рок (енумерација tip)
 Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)
 Дополнително за оваа класа да се дефинира методот:
    - pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)

 Да се креира класата CD во која се чуваат информации за (5 поени):
    - низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
    - број на песни снимени на CD-то
    - максимално времетраење на песните на CD-то (во минути)
 Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)
 Дополнително за оваа класа да се дефинираат методите:
    - dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
    - pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
 Комплетна функционалност (5 поени).

 Input:
 3
 4
 Happy 5 0
 Layla 8 2
 Stan 4 1
 Revolution 7 2

 Result:
 ===== Testiranje na metodot dodadiPesna() od klasata CD ======
 "Happy"-5min
 "Layla"-8min
 "Stan"-4min
*/

#include <iostream>
#include <cstring>

using namespace std;

enum tip {
    pop = 0, rap = 1, rok = 2
};

class Pesna {
    char *name; // dinamicki alocirano
    int time;
    tip type;

    void copyPesna(const Pesna &p) {
        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);
        time = p.time;
        type = p.type; // Updated the assignment
    }

public:
    Pesna() { // default constructor
        this->name = new char[10];
        strcpy(this->name, "");
        this->time = 0;
        this->type = pop;
    }

    Pesna(char *name, int time, enum tip tip) { // constructor with parameters
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->time = time;
        this->type = tip;
    }

    Pesna(const Pesna &p) { // copy-constructor
        copyPesna(p);
    }

    Pesna &operator=(const Pesna &p) {  // operator =
        if (this != &p) {
            delete[] name;
            copyPesna(p);
        }
        return *this;
    }

    ~Pesna() {  // destructor
        delete[] name;
    }

    // getters
    char *getName() {
        return name;
    }

    int getTime() {
        return time;
    }

    enum tip getTip() {
        return type;
    }

    // pecati
    void pecati() {
        cout << "\"" << name << "\"-" << time << "min" << endl;
    }
};

class CD {
    int brPesni;
    int maxTime;
    Pesna pesna[10];

    void copyCD(CD &cd) {
        this->brPesni = cd.brPesni;
        this->maxTime = cd.maxTime;
        for (int i = 0; i < this->brPesni; i++) {
            this->pesna[i] = cd.pesna[i];
        }
    }

public:
    CD() { // default
        this->brPesni = 0;
        this->maxTime = 0;
    }

    CD(int maxTime) { // parameters
        this->brPesni = 0;
        this->maxTime = maxTime;
    }

    CD(CD &cd) { // copy-constructor
        copyCD(cd);
    }

    CD &operator=(CD &cd) { // operator =
        if (this != &cd) {
            copyCD(cd);
        }
        return *this;
    }

    ~CD() { // destructor
    }

    Pesna getPesna(int i) {
        return pesna[i];
    }

    int getBroj() {
        return brPesni;
    }

    int getMaxTime() {
        return maxTime;
    }

    void dodadiPesna(Pesna p) {
        int time = 0;
        for (int i = 0; i < brPesni; i++) {
            time += pesna[i].getTime();
        }
        if (p.getTime() + time < maxTime && brPesni < 10) {
            pesna[brPesni] = p;
            brPesni++;
        }
    }

    void pecatiPesniPoTip(tip t) {
        for (int i = 0; i < brPesni; i++) {
            if (pesna[i].getTip() == t)
                pesna[i].pecati();
        }
    }
};


int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime, minuti, (tip) kojtip);
        p.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime, minuti, (tip) kojtip);
            omileno.dodadiPesna(p);
        }
        cin >> kojtip;
        omileno.pecatiPesniPoTip((tip) kojtip);

    }
    return 0;
}

