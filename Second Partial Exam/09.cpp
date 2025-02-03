/*
 Да се имплементира класа Trud во која се чуваат информации за: (5 поени)
    •	вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
    •	година на издавање (цел број).

 Да се имплементира класа Student во која се чува: (5 поени)
    •	името на студентот (низа од најмногу 30 карактери)
    •	индекс (цел број)
    •	година на упис (цел број)
    •	листа на оцени од положени предмети (низа од цели броеви)
    •	број на положени предмети (цел број)
 За оваа класа да се имплементираат следните методи:
    •	функција rang() што пресметува просек од положените испити на студентот (5 поени)
    •	оператор << за печатење на студентот во формат: (5 поени)
        Индекс Име Година на упис ранг

 Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)
    •	листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
    •	бројот на трудови (цел број)
 Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити
 ќе се додаде и збирот од поените од објавените трудови на PhD студентот.
 Во зависност од видот на трудот, секој универзитет има посебен начин на бодување на трудовите.
 Начинот на бодување е ист за сите PhD студенти.
 Иницијално да се смета дека конференциски труд се бодува со 1 поен, а труд во списание со 3 поени.
 Универзитетот има можност да ги менува вредностите на бодовите. (5 поени + 5 поени)
 За оваа класа да се обезбеди:
    •	оператор += за додавање нов објект од класата Trud во листата (5 поени).
    Ако се направи обид да се внесе труд што е издаден порано од годината на упис на студентот да се фрли исклучок
    (објект од класата Exception). Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно,
    но и во конструктор ако е потребно. Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка
    "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)

 Напомена: Сите променливи на класите се чуваат како приватни.
 Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

 Input:
 2
 3
 1
 PhDStudent_1
 111222
 2012
 5
 10 10 10 9 10
 1
 j
 2015
 1
 PhDStudent_2
 123456
 2003
 5
 10 9 10 8 10
 3
 c
 2003
 j
 2003
 j
 2005
 0
 Student
 12234
 2010
 3
 10 10 10
 123456
 C
 2004

 Result:
 ===== Testiranje na operatorot += ======

 Lista na site studenti:
 111222 PhDStudent_1 2012 12.8
 123456 PhDStudent_2 2003 16.4
 12234 Student 2010 10

 Lista na site studenti:
 111222 PhDStudent_1 2012 12.8
 123456 PhDStudent_2 2003 17.4
 12234 Student 2010 10
*/

#include <iostream>
#include <cstring>

using namespace std;

class Exception {
public:
    void message() {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud {
private:
    char type;
    int year;
public:
    Trud(char type = 'a', int year = 0) {
        this->type = type;
        this->year = year;
    }

    friend istream &operator>>(istream &in, Trud &t) {
        in >> t.type >> t.year;
        return in;
    }

    char getType() {
        return type;
    }

    int getYear() {
        return year;
    }
};

class Student {
protected:
    char name[30];
    int index;
    int yearOfEnrollment;
    int grades[50];
    int passedSubjects;
public:
    Student(char *name = "", int index = 0, int yearOfEnrollment = 0, int *grades = 0, int passedSubjects = 0) {
        strcpy(this->name, name);
        this->index = index;
        this->yearOfEnrollment = yearOfEnrollment;
        this->passedSubjects = passedSubjects;
        for (int i = 0; i < passedSubjects; ++i) {
            this->grades[i] = grades[i];
        }
    }

    virtual float rang() {
        float sum = 0, n = 0;
        for (int i = 0; i < passedSubjects; ++i) {
            if (grades[i] >= 6) {
                sum += grades[i];
                n++;
            }
        }
        return sum / n;
    }

    friend ostream &operator<<(ostream &out, Student &s) {
        out << s.index << " " << s.name << " " << s.yearOfEnrollment << " " << s.rang() << endl;
        return out;
    }

    int getIndex() {
        return index;
    }
};

class PhDStudent : public Student {
private:
    Trud *theses;
    int n;
    static int conference;
    static int journal;
public:
    PhDStudent(char *name = "", int index = 0, int yearOfEnrollment = 0, int *grades = 0, int passedSubjects = 0,
               Trud *theses = nullptr, int n = 0) : Student(name, index, yearOfEnrollment, grades, passedSubjects) {
        this->n = n;
        this->theses = new Trud[n];
        for (int i = 0; i < n; ++i) {
            try {
                if (theses[i].getYear() < yearOfEnrollment)
                    throw Exception();
                else
                    this->theses[i] = theses[i];
            } catch (Exception &e) {
                e.message();
            }
        }
    }

    float rang() {
        float points = 0;
        for (int i = 0; i < n; ++i) {
            if (theses[i].getType() == 'C' || theses[i].getType() == 'c')
                points += conference;
            else if (theses[i].getType() == 'J' || theses[i].getType() == 'j')
                points += journal;
        }
        return Student::rang() + points;
    }

    PhDStudent &operator+=(Trud &t) {
        if (t.getYear() < yearOfEnrollment)
            throw Exception();
        else {
            Trud *temp = new Trud[n + 1];
            for (int i = 0; i < n; ++i) {
                temp[i] = theses[i];
            }
            temp[n] = t;
            n++;
            delete[] theses;
            theses = temp;
        }
        return *this;
    }

    static void setConference(int c) {
        conference = c;
    }

    static void setJournal(int j) {
        journal = j;
    }
};

int PhDStudent::conference = 1;
int PhDStudent::journal = 3;

int main() {
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool flag = false;
        try {
            for (int i = 0; i < n; ++i) {
                if (niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent *>(niza[i])) {
                    *dynamic_cast<PhDStudent *>(niza[i]) += t;
                    flag = true;
                }
            }
        }
        catch (Exception &e) {
            e.message();
        }

        if (!flag)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++) {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        try {
            for (int i = 0; i < m; i++) {
                if (niza[i]->getIndex() == indeks && dynamic_cast<PhDStudent *>(niza[i])) {
                    *dynamic_cast<PhDStudent *>(niza[i]) += t;
                }
            }
        } catch (Exception &e) {
            e.message();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

        PhDStudent::setConference(conf);
        PhDStudent::setJournal(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    return 0;
}