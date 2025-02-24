/*
 Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:
    •	името (низа од 50 знаци),
    •	електронска адреса (низа од 50 знаци),
    •	вид на купувач (стандардни, лојални или вип),
    •	основен попуст (цел број изразен во проценти),
    •	дополнителен попуст (цел број изразен во проценти) и
    •	број на купени производи. (5 поени)
 Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата.
 Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата.
 Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%.
 Стандардните купувачи немаат право на попуст (5 поени).

 За оваа класа да се имплементира оператор << за печатење на купувач во формат:
 [ime_na_kupuvac]
 [email_na_kupuvac]
 [broj_na_proizvodi]
 [vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
 каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

 Да се креира класа за онлајн книжара FINKI-bookstore во која се чува
 низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени)
 За класата да се обезбедат:
    •	Оператор += (10 поени) за додавање купувач во листата од купувачи,
        но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса).
        Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException.
        Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место.
        Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
    •	Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални,
        а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
    •	Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
 Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

 Input:
 6
 5
 Albert Einstein
 einstein@finki.mk
 1
 2
 Isaac Newton
 newton@finki.mk
 2
 10
 Galileo Galilei
 galilei@finki.mk
 1
 12
 Stephen Hawking
 hawking@finki.mk
 0
 17
 Nikola Tesla
 tesla@finki.mk
 0
 7

 Result:
 ===== Test Case - update method  ======

 Update:
 Albert Einstein
 einstein@finki.mk
 2
 loyal 10
 Isaac Newton
 newton@finki.mk
 10
 vip 30
 Galileo Galilei
 galilei@finki.mk
 12
 vip 30
 Stephen Hawking
 hawking@finki.mk
 17
 loyal 10
 Nikola Tesla
 tesla@finki.mk
 7
 loyal 10
*/

#include <iostream>
#include <cstring>

using namespace std;

int MAX = 100;

enum typeC {
    standard = 0, loyal = 1, vip = 2
};

class UserExistsException {
public:
    void message() {
        cout << "The user already exists in the list!" << endl;
    }
};

class Customer {
private:
    char name[51];
    char email[51];
    typeC type;
    static int baseDiscount;
    static int additionalDiscount;
    int products;
public:
    Customer(const char *name = "", const char *email = "", typeC type = standard, int products = 0) {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = type;
        this->products = products;
    }

    friend ostream &operator<<(ostream &out, const Customer &c) {
        out << c.name << endl << c.email << endl << c.products << endl;
        if (c.type == 0)
            out << "standard " << 0 << endl;
        else if (c.type == 1)
            out << "loyal " << baseDiscount << endl;
        else
            out << "vip " << baseDiscount + additionalDiscount << endl;
        return out;
    }

    const char *getEmail() const {
        return email;
    }

    int getProducts() const {
        return products;
    }

    void setType(typeC type) {
        this->type = type;
    }

    static void setDiscount1(int d) {
        baseDiscount = d;
    }

    typeC getType() const {
        return type;
    }
};

class FINKI_bookstore {
private:
    Customer *customers;
    int n;

    void copy(const FINKI_bookstore &f) {
        this->n = f.n;
        this->customers = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->customers[i] = f.customers[i];
        }
    }

public:
    FINKI_bookstore(Customer *customers = nullptr, int n = 0) {
        this->n = n;
        this->customers = new Customer[n];
        for (int i = 0; i < n; ++i) {
            this->customers[i] = customers[i];
        }
    }

    FINKI_bookstore(const FINKI_bookstore &f) {
        copy(f);
    }

    ~FINKI_bookstore() {
        delete[] customers;
    }

    FINKI_bookstore &operator+=(const Customer &c) {
        bool flag = false;
        for (int i = 0; i < n; ++i) {
            if (!strcmp(customers[i].getEmail(), c.getEmail())) {
                flag = true;
                break;
            }
        }
        if (flag) {
            throw UserExistsException();
        } else {
            Customer *temp = new Customer[n + 1];
            for (int i = 0; i < n; ++i) {
                temp[i] = customers[i];
            }
            temp[n] = c;
            n++;
            delete[] customers;
            customers = temp;
        }
        return *this;
    }

    void update() {
        for (int i = 0; i < n; ++i) {
            if (customers[i].getType() == (typeC) 0) {
                if (customers[i].getProducts() > 5)
                    customers[i].setType(loyal);
            } else if (customers[i].getType() == (typeC) 1) {
                if (customers[i].getProducts() > 10)
                    customers[i].setType(vip);
            }
        }
    }

    friend ostream &operator<<(ostream &out, const FINKI_bookstore &f) {
        for (int i = 0; i < f.n; ++i) {
            out << f.customers[i];
        }
        return out;
    }

    void setCustomers(Customer *c, int number) {
        delete[] customers;
        this->n = number;
        this->customers = new Customer[number];
        for (int i = 0; i < number; ++i) {
            this->customers[i] = c[i];
        }
    }
};

int Customer::baseDiscount = 10;
int Customer::additionalDiscount = 20;

int main() {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1) {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2) {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3) {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4) {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try {
            fc += c;
        }
        catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 5) {
        cout << "===== Test Case - operator+= (exception) ======" << endl; // editirana linija
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts); // dodadena linija

        try {
            fc += c;
        }
        catch (UserExistsException &e) {
            e.message();
        }

        cout << fc;
    }

    if (testCase == 6) {
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;
}
