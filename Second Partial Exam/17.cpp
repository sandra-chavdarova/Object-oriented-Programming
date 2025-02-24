/*
 Да се имплементира апстрактна класа FudblaskaEkipa во која се чува: (5 поени)
 •	 име на тренерот на екипата (максимум 100 знаци)
 •	 бројот на постигнати голови на последните 10 натпревари, последниот натпревар е на позиција 9, предпоследниот на позиција 8, итн
     (поле од 10 цели броеви)

 Од класата FudblaskaEkipa да се изведат класите Klub и Reprezentacija.
 За секој клуб дополнително се чува податок за името и бројот на титули што ги има освоено,
 а за репрезентацијата се чуваат податоци за името на државата и вкупен број на меѓународни настапи.
 За овие класи да се имплементираат следните методи:
 •	 соодветен конструктор (5 поени)
 •	 оператор << за печатење на стандарден излез во формат [IME_NA_KLUB/DRZHAVA]\n[TRENER]\n[USPEH]\n (5 поени)
 •	 преоптоварен оператор+= за додавање на голови од последниот натпревар
     (внимавајте секогаш се чуваат головите само од последните 10 натпревари) (10 поени)
 •	 метод uspeh, за пресметување на успехот на тимот на следниот начин:
     •	 За Klub се пресметува како збир од збирот на головите од последните 10 натпревари помножен со 3
         и бројот на титули помножен со 1000 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на титули = 3,
         достигнување = 18 * 3 + 3 * 1000 = 3054)
     •	 За Reprezentacija како збир од збирот на головите од последните 10 натпревари помножен со 3
         и бројот на меѓународни настапи помножен со 50 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3}
         и број на меѓународни настапи=150, достигнување = 18 * 3 + 150 * 50 = 7554) (10 поени)
 •	 преоптоварен оператор > за споредба на две фудбласки екипи од каков било вид (клубови или репрезентации) според успехот (5 поени)

 Да се имплементира функција najdobarTrener што на влез прима низа од покажувачи кон FudblaskaEkipa
 и големина на низата и го печати тимот со најголем успех (10 поени).

 Input:
 5
 0
 Zinedin Zidane
 2 2 2 3 4 1 5 3 0 3
 Real Madrid CF
 2
 0
 Luis Enrique
 3 4 5 1 3 0 6 5 4 3
 FC Barcelona
 6
 1
 Visente Del Boske
 1 1 4 0 2 2 3 1 3 5
 Spain
 2
 1
 Antonio Conte
 0 0 1 4 2 3 4 1 2 2
 Italy
 3
 0
 Claudio Ranieri
 3 2 2 3 1 2 2 0 3 4
 Leicester City FC
 1
 3
 2
 3
 2
 1

 Result:
 ===== SITE EKIPI =====
 Real Madrid CF
 Zinedin Zidane
 2075
 FC Barcelona
 Luis Enrique
 6102
 Spain
 Visente Del Boske
 166
 Italy
 Antonio Conte
 207
 Leicester City FC
 Claudio Ranieri
 1066
 ===== DODADI GOLOVI =====
 dodavam golovi: 3
 dodavam golovi: 2
 dodavam golovi: 3
 dodavam golovi: 2
 dodavam golovi: 1
 ===== SITE EKIPI =====
 Real Madrid CF
 Zinedin Zidane
 2078
 FC Barcelona
 Luis Enrique
 6099
 Spain
 Visente Del Boske
 172
 Italy
 Antonio Conte
 213
 Leicester City FC
 Claudio Ranieri
 1060
 ===== NAJDOBAR TRENER =====
 FC Barcelona
 Luis Enrique
 6099
*/

#include <iostream>
#include <cstring>

using namespace std;

class FudbalskaEkipa {
protected:
    char name[100];
    int goals[10];
public:
    FudbalskaEkipa(char *name = "", int *goals = 0) {
        strcpy(this->name, name);
        for (int i = 0; i < 10; ++i) {
            this->goals[i] = goals[i];
        }
    }

    virtual int uspeh() = 0;

    bool operator>(FudbalskaEkipa &f) {
        return uspeh() > f.uspeh();
    }

    FudbalskaEkipa &operator+=(int goal) {
        int j = 0;
        for (int i = 1; i < 10; ++i, j++) {
            goals[j] = goals[i];
        }
        goals[j] = goal;
        return *this;
    }

    const char *getName() {
        return name;
    }
};

class Klub : public FudbalskaEkipa {
private:
    char club[100];
    int titles;
public:
    Klub(char *name = "", int *goals = 0, char *club = "", int titles = 0) : FudbalskaEkipa(name, goals) {
        strcpy(this->club, club);
        this->titles = titles;
    }

    int uspeh() {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += goals[i];
        }
        return sum * 3 + titles * 1000;
    }

    const char *getClub() {
        return club;
    }
};

class Reprezentacija : public FudbalskaEkipa {
private:
    char country[50];
    int representations;
public:
    Reprezentacija(char *name = "", int *goals = 0, char *country = "", int representations = 0) : FudbalskaEkipa(name,
                                                                                                                  goals) {
        strcpy(this->country, country);
        this->representations = representations;
    }

    int uspeh() {
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            sum += goals[i];
        }
        return sum * 3 + representations * 50;
    }

    const char *getCountry() {
        return country;
    }
};

ostream &operator<<(ostream &out, FudbalskaEkipa &k) {
    if (dynamic_cast<Klub *>(&k)) {
        out << dynamic_cast<Klub *>(&k)->getClub();
    } else if (dynamic_cast<Reprezentacija *>(&k)) {
        out << dynamic_cast<Reprezentacija *>(&k)->getCountry();
    }
    out << "\n" << k.getName() << "\n" << k.uspeh() << "\n";
    return out;
}

void najdobarTrener(FudbalskaEkipa **teams, int n) {
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (teams[i]->uspeh() > teams[index]->uspeh())
            index = i;
    }
    cout << *teams[index];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}