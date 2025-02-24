/*
 For the needs of an Internet operator, it is necessary to model a system for bill (invoice) payment.
 For that purpose, create an abstract class for representing a monthly invoice (MonthlyInvoice) of an Internet operator.
 Each invoice is represented by the following information:
 •	username (array of up to 100 characters)
 •	user number (integer)
 •	initial price of the package (float number)
 •	amount of used internet in a given month in gigabytes (integer)

 Implement separate derived classes for different types of invoices:
 for a business user (BusinessInvoice) and a private user (PrivateInvoice).

 Each invoice for a business user is represented by the following information:
 •	whether the line is optical or cable (boolean variable, optics - true, cable -false)
 •	quantity of included free transfer (in gigabytes - int)

 Each invoice for a private user is represented by the following information:
 •	identification number of the citizen (array of up to 13 characters)
 •	dynamically allocated array of the sizes of online movies from the video collection.
    The array keeps an information of the size (in GB) of each movie that was watched by the private user within the given month.
    If the user watched 3 movies from the video, then 3 integers are stored to represent the size in gigabytes of each movie
    (e.g. the {1, 2, 4} array represents 1GB, 2GB and 4GB movies respectively).
 •	number of movies watched from the video collection (integer).

 Calculate the total cost of the invoice for each of the derived classes.
  •	For a business user it is calculated as: initial_price + amount_of_used_internet_over_the_included_free_internet * 100.
    If the connection is optical, the initial price increases by 50%.
  •	For a private user, the price is counted as: 'initialPrice + amountOfUsedInternet * 50 + totalamountofgigabytesfromthewatchedmoviesfromthemovie_collection * 10`.

 Define the following functionalities for the BusinessInvoice:
 •	operator ++ (post notation) * - increases the amount of the used internet by 1GB

 Define the following operators for the PrivateInvoice class:
 •	operator [] * - returns the size of the movie on a given position specified by the input argument.
    If you search for a movie on an index that does not exist, it returns -1
    (for example: if there are 3 movies and the element with an index 5 is required, it should return -1).
    The first film is on position (index) '0'.
 •	operator += * - adds a new movie size in the array of watched movies
 •	operator ++ * - increases the amount of the used internet by 1GB

 Overload the operator > for comparison of two accounts based on the total cost of their monthly invoice.
 Overload the << operator that will print all the relevant information for each user in the following format:

 For the business invoice:
 [user number] - [user name], [initial price]
 [line type], [quantity of the used internet over the free gigabytes]
 For the private invoice:

 [user number] - [user name], [initial price]
 [used gigabytes]
 [number of watched movies], [total movie size (in gigabytes)]

 Write the `biggestInvoice ' function that accepts an array of pointers to the invoices as input argument
 and returns an object (of the appropriate type) that represents the invoice with the highest total cost.

 Input:
 3
 Finki
 123456
 20000
 1000
 1
 1999

 Result:
 Testing total_price()
 123456 - Finki, 20000
 optical link, 0
 30000
 123456 - Finki, 20000
 optical link, 0
 30000
*/

#include <iostream>
#include <cstring>

using namespace std;

class MonthlyInvoice {
protected:
    char name[101];
    int number;
    float initialPrice;
    int spentGigabytes;
public:
    MonthlyInvoice(char *name, int number, float initialPrice, int spentGigabytes) { // constructor
        strcpy(this->name, name);
        this->number = number;
        this->initialPrice = initialPrice;
        this->spentGigabytes = spentGigabytes;
    }

    MonthlyInvoice(const MonthlyInvoice &m) { // copy-constructor
        strcpy(this->name, m.name);
        this->number = m.number;
        this->initialPrice = m.initialPrice;
        this->spentGigabytes = m.spentGigabytes;
    }

    virtual int total_price() = 0;

    bool operator>(MonthlyInvoice &m) {
        return total_price() > m.total_price();
    }

    ~MonthlyInvoice() {} // destructor
};

class BusinessInvoice : public MonthlyInvoice {
private:
    bool optical;
    int freeGigabytes;
public:
    // constructor
    BusinessInvoice(char *name = "", int number = 0, float initialPrice = 0.0, int spentGigabytes = 0,
                    bool optical = true, int freeGigabytes = 0) : MonthlyInvoice(name, number, initialPrice,
                                                                                 spentGigabytes) {
        this->optical = optical;
        this->freeGigabytes = freeGigabytes;
    }

    int total_price() {
        int sum = initialPrice;
        if (optical)
            sum = initialPrice * 1.5;
        int internet = spentGigabytes - freeGigabytes;
        return (sum + ((internet > 0) ? internet : 0) * 100);
    }

    BusinessInvoice operator++(int) {
        BusinessInvoice temp = *this;
        this->spentGigabytes++;
        return temp;
    }

    friend ostream &operator<<(ostream &out, const BusinessInvoice &b) {
        out << b.number << " - " << b.name << ", " << b.initialPrice << endl;
        int internet = b.spentGigabytes - b.freeGigabytes;
        out << (b.optical ? "optical link, " : "cable link, ") << ((internet > 0) ? internet : 0) << endl;
        return out;
    }
};

class PrivateInvoice : public MonthlyInvoice {
private:
    char id[14];
    int *sizes;
    int n;
public:
    //constructor
    PrivateInvoice(char *name = "", int number = 0, float initialPrice = 0.0, int spentGigabytes = 0, char *id = "",
                   int *sizes = nullptr, int n = 0) : MonthlyInvoice(name, number, initialPrice, spentGigabytes) {
        strcpy(this->id, id);
        this->n = n;
        this->sizes = new int[n];
        for (int i = 0; i < n; ++i) {
            this->sizes[i] = sizes[i];
        }
    }

    PrivateInvoice(const PrivateInvoice &p) : MonthlyInvoice(p) { // copy-constructor
        strcpy(this->id, p.id);
        this->n = p.n;
        this->sizes = new int[n];
        for (int i = 0; i < n; ++i) {
            this->sizes[i] = p.sizes[i];
        }
    }

    ~PrivateInvoice() { // destructor
        delete[] sizes;
    }

    PrivateInvoice &operator=(const PrivateInvoice &p) {
        if (this != &p) {
            delete[] sizes;
            strcpy(this->id, p.id);
            this->n = p.n;
            this->sizes = new int[n];
            for (int i = 0; i < n; ++i) {
                this->sizes[i] = p.sizes[i];
            }
        }
        return *this;
    }

    int total_price() {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += sizes[i];
        }
        return initialPrice + spentGigabytes * 50 + sum * 10;
    }

    int operator[](int index) {
        if (index >= 0 && index < n) {
            return sizes[index];
        }
        return -1;
    }

    PrivateInvoice &operator+=(int newSize) {
        int *temp = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = sizes[i];
        }
        temp[n++] = newSize;
        sizes = temp;
        return *this;
    }

    PrivateInvoice operator++(int) {
        PrivateInvoice temp = *this;
        this->spentGigabytes++;
        return temp;
    }

    friend ostream &operator<<(ostream &out, PrivateInvoice &p) {
        int sum = 0;
        for (int i = 0; i < p.n; ++i) {
            sum += p.sizes[i];
        }
        out << p.number << " - " << p.name << ", " << p.initialPrice << endl;
        out << p.spentGigabytes << endl;
        out << p.n << ", " << sum << endl;
        return out;
    }

    int getMoviesNo() {
        return n;
    }
};

MonthlyInvoice &biggestInvoice(MonthlyInvoice **invoices, int n) {
    MonthlyInvoice *invoice = invoices[0];
    for (int i = 1; i < n; ++i) {
        if (invoices[i]->total_price() > invoice->total_price())
            invoice = invoices[i];
    }
    return *invoice;
}

int main() {
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case Business Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice Created:\n";
        cout << bi;
    } else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            bi++;
        }
        cout << bi;
    } else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout << bi.total_price() << endl;
        bi++;
        cout << bi;
        cout << bi.total_price() << endl;
    } else if (test_case == 4) {
        // Test Case Private Invoice - Constructor, operator <<
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;

        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << "Private Invoice Created:\n";
        cout << pi;
    } else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
    } else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
    } else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i = 0; i < pi.getMoviesNo(); ++i) {
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    } else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber, basic_price, spent_gigabytes);
        cout << pi;
        cout << pi.total_price() << endl;
        cin >> num_inc;
        int film_length;
        for (int i = 0; i < num_inc; ++i) {
            cin >> film_length;
            pi += film_length;
        }
        cin >> num_inc;
        for (int i = 0; i < num_inc; ++i) {
            pi++;
        }
        cout << pi;
        cout << pi.total_price() << endl;
    } else if (test_case == 9) {
        // Test Case
        int num_invoices;
        int invoice_type;

        cin >> num_invoices;
        MonthlyInvoice **mi = new MonthlyInvoice *[num_invoices];
        for (int j = 0; j < num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice *bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout << bip->total_price() << endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice *pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice &invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice *m = &invoice;
        BusinessInvoice *bip;
        PrivateInvoice *pip;
        if (dynamic_cast<BusinessInvoice *> (m)) {
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout << *bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)) {
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout << *pip << pip->total_price();
        }
    }
    return 0;
}