/*
 Define a class IceCream that stores information for:
 •	name (dynamically allocated array of chars),
 •	ingredients (char array, max 100)
 •	price (decimal number),
 •	discount (integer in percentage) initial value 0.

 For this class implement:
 •	constructors and destructor (see the main function for calls) (5 points)
 •	operator << for printing the data in the following format:
    name: ingredients price [discounted price]
    the part "discounted price" is printed only if the icecream has discount (discount value is bigger than 0) (5 points)
 •	operator ++ in prefix notation for increasing the discount for 5 (5 points)
 •	operator + for addition of object of class IceCream with char array.
    The addition to be implemented so the name of the new icecream is formed by concatenating the name of the icecream and the char array,
    separated with +. The price of the new icecream is increased for 10, and the discount and the ingredients stay the same. (10 points)
 •	method void setDiscount(int discount) that can change the value of the discount.
    If the value is negative or larger than 100, an exception should be thrown that will carry the invalid value.
    In the marked part of the main function write a code segment that will handle with this exception and write message
    Invalid discount value: [the value]. (10 points)
 •	method void setName(char* name) that changes the name of the icecream. (5 points)

 Create class IceCreamShop that have:
 •	name of the store (char array, max 50)
 •	dynamically allocated array of objects of class IceCream
 •	number of icecream objects (integer).

 For this class implement:
 •	constructs and desctructor (see the calls in the main function)
 •	operator += for adding new object of the class IceCream in the field (10 points)
 •	operator << for printing a list of all icecreams in the store.
    First the name of the store is printed, and then the data for all icecreams in new lines. (5 points)

 Input:
 2
 Caramel Apple Delight
 Caramel Delight ice cream, Apples
 60
 Caramel Apple Delight Ice Cream in Apples
 Special Ice Cream
 -40

 Result:
 ====== TESTING IceCream CONSTRUCTORS ======
 CONSTRUCTOR
 Caramel Apple Delight: Caramel Delight ice cream, Apples 60
 COPY CONSTRUCTOR
 Caramel Apple Delight: Caramel Delight ice cream, Apples 60
 Caramel Apple Delight Ice Cream in Apples: Caramel Delight ice cream, Apples 60
 OPERATOR =
 Caramel Apple Delight Ice Cream in Apples: Caramel Delight ice cream, Apples 60
 Special Ice Cream: Caramel Delight ice cream, Apples 60
 TESTING EXCEPTION
 Invalid discount value: -40
*/

#include <iostream>
#include <cstring>

using namespace std;

class InvalidValueException {
private:
    int discount;
public:
    InvalidValueException(int discount = 0) {
        this->discount = discount;
    }

    void message() {
        cout << "Invalid discount value: " << discount << endl;
    }
};

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
        if (discount < 0 || discount > 100)
            throw InvalidValueException(discount);
        else
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
        cout << "OPERATOR &lt;&lt;" << endl;  // popravena linija
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
        cout << "TESTING EXCEPTION" << endl;

        // your exception handling code

        cin >> discount;
        try {
            ic1.setDiscount(discount);
        }
        catch (InvalidValueException &e) {
            e.message();
        }

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