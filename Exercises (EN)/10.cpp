/*
 Create a program for managing products in a piano store.
 For that purpose, the class' Piano` (5 points) should be created.
 The class should include:
 •	Serial number (array of 25 characters)
 •	Price (decimal number)
 •	Year of production (integer)

 For this class, implement a method equals that accepts an object from the Piano class as an argument,
 and makes a comparison between the objects on the bases of their serial number. (5 points)

 In addition, for this class, provide a print() method for printing the object in the following format (5 points):
 [Serial number] [Year of production] [Price]

 Create a PShop class * (5 points) * that contains:
 •	Store name (array of 50 characters)
 •	A list of pianos in the store (dynamically allocated array of objects of the Piano class)
 •	Number of objects in the array (integer)

 For this class, provide the following methods:
 •	double value() - to calculate the current value of the pianos in the store.
    It is calculated as a sum of the price of all the pianos in the store (5 points).
 •	void add(Piano p) - to add a new piano in the store (adding a new object from the Piano class to the array of pianos) (10 points)
 •	void sell(Piano p) to delete a given piano from the array
    (delete all items that are equal to the input argument, according to the serial number) (10 points)
 •	void print() - to print the information about the store, so that the first row displays its name,
    and then in each row the information for each piano. (5 points)

 For all classes, define the necessary constructors, destructor and all other methods necessary to provide a correct program functionality.
 All data members in the classes are private. (5 points)

 Input:
 5
 FINKI-Piano
 3
 12345
 990
 2000
 12346
 1200
 2010
 12347
 1300
 2015
 12348
 950
 2012
 12349
 1500
 2017

 Result:
 ---Add method---
 FINKI-Piano
 1. 12345 2000 990
 2. 12346 2010 1200
 3. 12347 2015 1300
 FINKI-Piano
 1. 12345 2000 990
 2. 12346 2010 1200
 3. 12347 2015 1300
 4. 12348 2012 950
 FINKI-Piano
 1. 12345 2000 990
 2. 12346 2010 1200
 3. 12347 2015 1300
 FINKI-Piano
 1. 12345 2000 990
 2. 12346 2010 1200
 3. 12347 2015 1300
 4. 12349 2017 1500
*/

#include <iostream>
#include <cstring>

using namespace std;

class Piano {
private:
    char serialNumber[25];
    float price;
    int year;

    void copy(const Piano &p) {
        strcpy(this->serialNumber, p.serialNumber);
        this->price = p.price;
        this->year = p.year;
    }

public:
    Piano(const char *serialNumber = "", float price = 0.0, int year = 0) {
        strcpy(this->serialNumber, serialNumber);
        this->price = price;
        this->year = year;
    }

    Piano(const Piano &p) {
        copy(p);
    }

    ~Piano() {

    }

    bool equals(Piano &p) {
        return !strcmp(this->serialNumber, p.serialNumber);
    }

    void print() {
        cout << serialNumber << " " << year << " " << price << endl;
    }

    float getPrice() const {
        return price;
    }

    const char *getSerial() const {
        return serialNumber;
    }

    void setSerial(char *newSerial) {
        strcpy(this->serialNumber, newSerial);
    }
};

class PShop {
private:
    char name[50];
    Piano *pianos;
    int n;

    void copy(const PShop &p) {
        strcpy(this->name, p.name);
        this->n = p.n;
        this->pianos = new Piano[n];
        for (int i = 0; i < n; ++i) {
            this->pianos[i] = p.pianos[i];
        }
    }

public:
    PShop(char *name = "", int n = 0) {
        strcpy(this->name, name);
        this->n = n;
        this->pianos = new Piano[n];
        for (int i = 0; i < n; ++i) {
            this->pianos[i] = pianos[i];
        }
    }

    PShop(const PShop &p) {
        copy(p);
    }

    ~PShop() {
        delete[] pianos;
    }

    PShop &operator=(const PShop &p) {
        if (this != &p) {
            delete[] pianos;
            copy(p);
        }
        return *this;
    }

    double value() {
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += pianos[i].getPrice();
        }
        return sum;
    }

    void add(Piano p) {
        Piano *temp = new Piano[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = pianos[i];
        }
        temp[n] = p;
        n++;
        delete[] pianos;
        pianos = temp;
    }

    void sell(Piano p) {
        int index = -1;
        Piano *temp = new Piano[n - 1];
        for (int i = 0; i < n; ++i) {
            if (!strcmp(pianos[i].getSerial(), p.getSerial())) {
                index = i;
                break;
            }
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (index != i) {
                temp[j] = pianos[i];
                j++;
            }
        }
        n--;
        delete[] pianos;
        pianos = temp;
    }

    void print() {
        cout << name << endl;
        for (int i = 0; i < n; ++i) {
            cout << i + 1 << ". ";
            pianos[i].print();
        }
    }

    Piano getP(int i) {
        if (i >= 0 && i < n)
            return pianos[i];
        exit(1);
    }
};

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "---Class Piano---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin >> serialNo >> price >> pYear;
        Piano p(serialNo, price, pYear);
        p.print();
    } else if (n == 2) {
        cout << "---Equals---" << endl;
        char serialNo[25];
        int pYear;
        float price;
        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        Piano p2(p1);
        if (p1.equals(p2))
            cout << "Equality" << endl;
        else
            cout << "Inequality" << endl;
        p2.setSerial("12344");
        if (p1.equals(p2))
            cout << "Equality" << endl;
        else
            cout << "Inequality" << endl;
    } else if (n == 3) {
        cout << "---Class PShop---" << endl;
        char name[50];
        cin >> name;
        PShop ps(name);
        ps.print();
    } else if (n == 4) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        ps.print();
    } else if (n == 5) {
        cout << "---Add method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        PShop ps2(ps), ps3;

        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin >> serialNo >> price >> pYear;
        Piano p2(serialNo, price, pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

    } else if (n == 6) {
        cout << "---value method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        cout << "Total price: " << ps.value() << endl;
    } else if (n == 7) {
        cout << "---sell method---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        int d;
        cin >> d;
        Piano p1(ps.getP(d).getSerial());
        ps.sell(p1);
        ps.print();
    } else if (n == 8) {
        cout << "---Full Test---" << endl;
        char name[50];
        cin >> name;
        int no;
        cin >> no;
        PShop ps(name);
        char serialNo[25];
        int pYear;
        float price;
        for (int i = 0; i < no; i++) {
            cin >> serialNo >> price >> pYear;
            Piano p(serialNo, price, pYear);
            ps.add(p);
        }
        ps.print();

        cout << endl;

        PShop ps2(ps), ps3;

        cin >> serialNo >> price >> pYear;
        Piano p1(serialNo, price, pYear);
        ps2.add(p1);

        ps.print();
        ps2.print();

        ps3 = ps;
        cin >> serialNo >> price >> pYear;
        Piano p2(serialNo, price, pYear);
        ps3.add(p2);

        ps.print();
        ps3.print();

        cout << endl;

        cout << "Total price: " << ps.value() << endl;

        cout << endl;

        int d;
        cin >> d;
        Piano p3(ps.getP(d).getSerial());
        ps.sell(p3);
        ps.print();

        cout << "Total price: " << ps.value() << endl;
    }
    return 0;
}