/*
 Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи
 кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

 OperativenSistem
 Во класата OperativenSistem треба да се чуваат следниве податоци:
    •	име на оперативниот систем (динамички алоцирана низа од знаци)
    •	верзија (float)
    •	тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
    •	големина (во GB) (float)
 Дополнително, во рамките на класата потребно е да се дефинира:
    •	конструктори со и без параметри
    •	copy constructor
    •	destructor
    •	преоптоварување на операторот =
    •	метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
    •	метод за проверка на еднаквост помеѓу два оперативни системи
        (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
    •	метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os),
        кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема
        и 1 во преостанатиот случај.
    •	метод за проверка дали два оперативни системи се од иста фамилија.
        Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип.
        bool istaFamilija(const OperativenSistem &sporedba)

 Repozitorium
 Во класата Repozitorium треба да се чуваат следниве податоци:
    •	име на репозиториумот (низа од 20 знака)
    •	динамички алоцирана низа од OperativenSistem
    •	број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
 Дополнително, во рамките на класата потребно е да се дефинира:
    •	конструктор Repozitorium(const char *ime)
    •	деструктор
    •	метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
    •	метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
    •	метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
        o	Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
    o	Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

 Input:
 FINKICloud
 2
 Ubuntu
 17.04
 1
 2.25
 Ubuntu
 16.04
 1
 1.25
 Ubuntu
 14.04
 1
 1.25

 Result:
 Repozitorium: FINKICloud
 Ime: Ubuntu Verzija: 17.04 Tip: 1 Golemina:2.25GB
 Ime: Ubuntu Verzija: 16.04 Tip: 1 Golemina:1.25GB
 =====Brishenje na operativen sistem=====
 Repozitorium: FINKICloud
 Ime: Ubuntu Verzija: 17.04 Tip: 1 Golemina:2.25GB
 Ime: Ubuntu Verzija: 16.04 Tip: 1 Golemina:1.25GB
*/

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

enum Tip {
    LINUX = 0, UNIX = 1, WINDOWS = 2
};

class OperativenSistem {
private:
    char *name;
    float version;
    Tip type;
    float size;

    void copy(const OperativenSistem &os) {
        this->name = new char[strlen(os.name) + 1];
        strcpy(this->name, os.name);
        this->version = os.version;
        this->type = os.type;
        this->size = os.size;
    }

public:
    OperativenSistem(char *name = "", float version = 0, Tip type = LINUX, float size = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->version = version;
        this->type = type;
        this->size = size;
    }

    OperativenSistem(const OperativenSistem &os) {
        copy(os);
    }

    ~OperativenSistem() {
        delete[] name;
    }

    OperativenSistem &operator=(const OperativenSistem &os) {
        if (this != &os) {
            delete[] name;
            copy(os);
        }
        return *this;
    }

    void pecati() {
        cout << "Ime: " << name << " Verzija: " << version << " Tip: " << type << " Golemina:" << setw(1) << size
             << "GB" << endl;
    }

    bool ednakviSe(const OperativenSistem &os) {
        return !strcmp(this->name, os.name) && this->version == os.version && this->type == os.type &&
               this->size == os.size;
    }

    int sporediVerzija(const OperativenSistem &os) {
        if (this->version == os.version)
            return 0;
        else if (this->version < os.version)
            return -1;
        else
            return 1;
    }

    bool istaFamilija(const OperativenSistem &sporedba) {
        return !strcmp(this->name, sporedba.name) && this->type == sporedba.type;
    }

    float getVersion() const {
        return version;
    }
};

class Repozitorium {
private:
    char name[20];
    OperativenSistem *systems;
    int n;

    void copy(const Repozitorium &r) {
        this->n = r.n;
        this->systems = new OperativenSistem[n];
        strcpy(this->name, r.name);
        for (int i = 0; i < n; i++) {
            this->systems[i] = r.systems[i];
        }
    }

public:
    Repozitorium(char *name = "", int n = 0) {
        this->n = n;
        this->systems = new OperativenSistem[n];
        strcpy(this->name, name);
        for (int i = 0; i < n; i++) {
            this->systems[i] = systems[i];
        }
    }

    Repozitorium(const Repozitorium &r) {
        copy(r);
    }

    ~Repozitorium() {
        delete[] systems;
    }

    Repozitorium &operator=(const Repozitorium &r) {
        if (this != &r) {
            delete[] systems;
            copy(r);
        }
        return *this;
    }

    void pecatiOperativniSistemi() {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < n; ++i) {
            systems[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem) {
        int index = -1;
        for (int i = 0; i < n; ++i) {
            if (systems[i].ednakviSe(operativenSistem)) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            OperativenSistem *temp = new OperativenSistem[n - 1];
            int j = 0;
            for (int i = 0; i < n; ++i) {
                if (index != i) {
                    temp[j] = systems[i];
                    j++;
                }
            }
            n--;
            delete[] systems;
            systems = temp;
        }
    }

    void dodadi(const OperativenSistem &nov) {
        int index = -1;
        for (int i = 0; i < n; ++i) {
            if (systems[i].istaFamilija(nov) && systems[i].getVersion() < nov.getVersion()) {
                index = i;
            }
        }
        if (index != -1) {
            systems[index] = nov;
        } else {
            OperativenSistem *temp = new OperativenSistem[n + 1];
            for (int i = 0; i < n; ++i) {
                temp[i] = systems[i];
            }
            temp[n] = nov;
            n++;
            delete[] systems;
            systems = temp;
        }
    }
};

int main() {
    char repoName[20];
    cin >> repoName;
    Repozitorium repozitorium = Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++) {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip) tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}