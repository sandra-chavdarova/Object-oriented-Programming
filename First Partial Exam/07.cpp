/*
 Да се дефинира класа Пица за која ќе се чуваат податоци за:
    •	име на пицата (низа од 15 знаци)
    •	цена (цел број)
    •	состојки (динамички алоцирана низа од знаци)
    •	намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
 За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:
    •	pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
    •	istiSe(Pica p) - функција за споредба на две пици според состојките :

 Да се дефинира класа Picerija во која се чуваат:
    •	име (низа од максимум 15 знаци)
    •	динмички алоцирана низа од објекти од класата Pica
    •	број на пици (цел број)
 За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:
    •	dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
    •	void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

 Input:
 FINKI-Pica
 4
 Margarita
 200
 Domaten sos, kaskaval, maslinovo maslo
 0
 Napolitana
 210
 Domaten sos, kaskaval, svezi sampinjoni, maslinovo maslo
 0
 Kapricioza
 210
 Domaten sos, kaskaval, sunka, svezi sampinjoni
 30
 Vegetarijana
 230
 Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka
 20
 Pica-FINKI
 Vegetarijana
 230
 Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka
 20

 Result:
 FINKI-Pica
 Pici na promocija:
 Kapricioza  - Domaten sos, kaskaval, sunka, svezi sampinjoni, 210 147
 Vegetarijana - Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka, 230 184
 Pica-FINKI
 Pici na promocija:
 Kapricioza  - Domaten sos, kaskaval, sunka, svezi sampinjoni, 210 147
 Vegetarijana - Domaten sos, kaskaval, tikvici, svezi sampinjoni, piperka, domat, maslinki, rukola, pcenka, 230 184
*/

#include <iostream>
#include <cstring>

using namespace std;

class Pica {
private:
    char name[15];
    int price;
    char *ingredients;
    int percent;

    void copy(const Pica &p) {
        strcpy(name, p.name);
        price = p.price;
        ingredients = new char[strlen(p.ingredients) + 1];
        strcpy(ingredients, p.ingredients);
        percent = p.percent;
    }

public:
    Pica(char *name = "", int price = 0, char *ingredients = "", int percent = 0) {
        strcpy(this->name, name);
        this->price = price;
        this->ingredients = new char[strlen(ingredients) + 1];
        strcpy(this->ingredients, ingredients);
        this->percent = percent;
    }

    Pica(const Pica &p) {
        copy(p);
    }

    ~Pica() {
        delete[] ingredients;
    }

    Pica &operator=(const Pica &p) {
        if (this != &p) {
            delete[] ingredients;
            copy(p);
        }
        return *this;
    }

    void pecati() {
        cout << name << " - " << ingredients << ", " << price;
    }

    bool istiSe(Pica p) {
        return !strcmp(this->ingredients, p.ingredients);
    }

    int getPercent() const {
        return percent;
    }

    int getPrice() const {
        return price;
    }
};

class Picerija {
private:
    char name[15];
    Pica *pizzas;
    int n;

    void copy(const Picerija &p) {
        strcpy(this->name, p.name);
        this->n = p.n;
        this->pizzas = new Pica[p.n];
        for (int i = 0; i < p.n; i++) {
            this->pizzas[i] = p.pizzas[i];
        }
    }

public:
    Picerija(char *name = "", int n = 0) {
        strcpy(this->name, name);
        this->n = n;
        this->pizzas = new Pica[n];
        for (int i = 0; i < n; i++) {
            this->pizzas[i] = pizzas[i];
        }
    }

    Picerija(const Picerija &p) {
        copy(p);
    }

    ~Picerija() {
        delete[] pizzas;
    }

    Picerija &operator=(const Picerija &p) {
        if (this != &p) {
            delete[] pizzas;
            copy(p);
        }
        return *this;
    }

    Picerija &operator+=(const Pica &p) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (pizzas[i].istiSe(p)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            Pica *temp = new Pica[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = pizzas[i];
            }
            temp[n] = p;
            n++;
            delete[] pizzas;
            pizzas = temp;
        }
        return *this;
    }

    void piciNaPromocija() {
        for (int i = 0; i < n; i++) {
            if (pizzas[i].getPercent() != 0) {
                pizzas[i].pecati();
                cout << " " << pizzas[i].getPrice() - pizzas[i].getPrice() * pizzas[i].getPercent() / 100.0 << endl;
            }
        }
    }

    const char *getIme() const {
        return name;
    }

    void setIme(char *name) {
        strcpy(this->name, name);
    }
};

int main() {
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++) {
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1 += p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2 += p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
