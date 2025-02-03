/*
 Да се дефинира класа IceCream во која се чуваат податоци за:
    •	име (динамичка низа од знаци),
    •	состав (низа од знаци, најмногу 100)
    •	цена (децимален број),
    •	попуст (цел број, изразен во проценти) иницијална вредност 0.
 За потребите на класата да се имплементираат:
    •	соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
    •	оператор << за печатење на податоците за сладоледот во следниов формат:
        име: состав цена [цена на попуст]
        делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)
    •	оператор ++ во префикс нотација за зголемување на попустот за 5
    •	оператор + - за собирање на објект од класата IceCream со низа од знаци.
        Собирањето се реализира на начин што името на новиот сладолед се добива со спојување на името на сладоледот
        и низата од знаци одделени со „ + “. Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
    •	метод void setDiscount(int discount) со кој може да се смени вредноста на попустот. Дозволените вредности на попустот се во интервалот [0,100]
    •	метод void setName(char* name) со кој се менува името на сладоледот.

 Да се креира класа IceCreamShop во која се чува:
    •	име на продавницата (низа од знаци, најмногу 50)
    •	динамички резервирано поле од објекти од класата IceCream
    •	број на сладоледи во полето (цел број).
 За оваа класа да се обезбедат:
    •	соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
    •	оператор += за додавање нов објект од класата IceCream во полето
    •	оператор << за печатење на листа од сите сладоледи во продавницата.
        Прво се печати името на продавницата, а потоа се печатат податоците за сите сладоледи одделени со нов ред.

 Input:
 3
 FINKI Ice Cream
 3
 Strawberry Ice Cream in Lemon Bowls
 Strawberry ice cream, Lemons
 100
 Caramel Apple Delight
 Caramel Delight ice cream, Apples
 120
 Dreyer’s Ice Cream Blueberry Pie
 French Vanilla ice cream, Graham cracker pie crust, blueberries
 60

 Result:
 ====== TESTING IceCreamShop ======
 CONSTRUCTOR
 OPERATOR +=
 FINKI Ice Cream
 Strawberry Ice Cream in Lemon Bowls: Strawberry ice cream, Lemons 100
 Caramel Apple Delight: Caramel Delight ice cream, Apples 120
 Dreyer’s Ice Cream Blueberry Pie: French Vanilla ice cream, Graham cracker pie crust, blueberries 60
*/

#include <iostream>
#include <cstring>

using namespace std;

class IceCream {
private:
    char *name;
    char ingredients[500];
    double price;
    int discount;

    void copy(const IceCream &i) {
        this->name = new char[strlen(i.name) + 1];
        strcpy(this->name, i.name);
        strcpy(this->ingredients, i.ingredients);
        this->price = i.price;
        this->discount = i.discount;
    }

public:
    IceCream(char *name = "", char *ingredients = "", double price = 0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
        this->price = price;
        this->discount = 0;
    }

    IceCream(const IceCream &i) {
        copy(i);
    }

    ~IceCream() {
        delete[] name;
    }

    IceCream &operator=(const IceCream &i) {
        if (this != &i) {
            delete[] name;
            copy(i);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const IceCream &i) {
        out << i.name << ": " << i.ingredients << " " << i.price;
        if (i.discount != 0) {
            out << " (" << (i.price - i.price * i.discount / 100)
                << ")";
        }
        return out;
    }

    IceCream &operator++() {
        this->discount += 5;
        return *this;
    }

    IceCream &operator+(const char *word) {
        char *temp = new char[strlen(name) + strlen(word) + 4];
        strcpy(temp, name);
        strcat(temp, " + ");
        strcat(temp, word);
        this->price += 10;
        delete[] name;
        strcpy(this->name, temp);
        return *this;
    }

    void setName(const char *newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    void setDiscount(int discount) {
        if (discount >= 0 && discount <= 100)
            this->discount = discount;
    }
};

class IceCreamShop {
private:
    char name[500];
    IceCream *iceCreams;
    int n;

    void copy(const IceCreamShop &ice) {
        strcpy(this->name, ice.name);
        this->n = ice.n;
        this->iceCreams = new IceCream[n];
        for (int i = 0; i < n; ++i) {
            this->iceCreams[i] = ice.iceCreams[i];
        }
    }

public:
    IceCreamShop(char *name = "", int n = 0) {
        strcpy(this->name, name);
        this->n = n;
        this->iceCreams = new IceCream[n];
        for (int i = 0; i < n; ++i) {
            this->iceCreams[i] = iceCreams[i];
        }
    }

    IceCreamShop(const IceCreamShop &i) {
        copy(i);
    }

    ~IceCreamShop() {
        delete[] iceCreams;
    }

    IceCreamShop &operator=(const IceCreamShop &i) {
        if (this != &i) {
            delete[] iceCreams;
            copy(i);
        }
        return *this;
    }

    IceCreamShop &operator+=(const IceCream &i) {
        IceCream *temp = new IceCream[n + 1];
        for (int j = 0; j < n; ++j) {
            temp[j] = iceCreams[j];
        }
        temp[n] = i;
        n++;
        delete[] iceCreams;
        iceCreams = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const IceCreamShop &i) {
        out << i.name << endl;
        for (int j = 0; j < i.n; ++j) {
            out << i.iceCreams[j] << endl;
        }
        return out;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if (testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if (testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if (testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if (testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName, 100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, 100);
            cin.getline(ingr, 100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics += x;
        cout << ics << endl;
        cout << icp << endl;
    }
    return 0;
}

/*
int main() {
    char *name = "cookie ice cream";
    char *word = "chocolate";
    char temp[strlen(name) + strlen(word) + 4];
    strcpy(temp, name);
    strcat(temp, " + ");
    strcat(temp, word);
    cout << temp << endl;
}
 */