/*
 Implement class Pair that has a key (dynamically allocated array of characters) and value (real number) (5 points).
 For this class implement:
 •	constructors and destructor (5 points)
 •	operator for printing on the SO << in format ('[key]', [value]) (5 points)
 •	operator ++ in prefix and postfix that increases the value for +1 (5 points)
 •	operator + for addition of two objects of this class that returns a new object in which the key is the longer (in length)
    of the keys of the objects that are adding and the values are added.
    If both objects have keys with equal length take the key from the left on in the operation addition. (10 points)

 Implement a class Collection where you keep dynamically allocated array of objects from the class Pair and length of the array (5 points).
 For this class implement:
 •	constructors and destructor (5 points)
 •	operator += for adding new object of the class Pair in the array (5 points)
 •	operator for printing on the SO << that prints the number of elements in the array, and then each object in a new line (5 points)
 •	operator == for comparing two objects of this class.
    Two collections are equal if they have equal number of elements and all objects on corresponding positions are equal. (5 points)
 •	method Pair* find(const char* key) that returns a pointer to the first objects with the provided key,
    if such object does not exist returns NULL pointer. (5 points)

 Input:
 some-key 55
 other-key 20

 Result:
 ----- class Pair -----
 ----- constructor -----
 ----- operator << -----
 ('some-key', 55)
 ('other-key', 20)
 ----- operator ++(int) -----
 ('some-key', 55)
 ('some-key', 56)
 ----- operator ++ -----
 ('other-key', 21)
 ----- operator + -----
 ----- operator = -----
 ('other-key', 77)
 ----- class Collection -----
 ----- constructor -----
 ----- operator += -----
 ----- operator << -----
 Size: 3
 ('some-key', 56)
 ('other-key', 21)
 ('other-key', 77)
 ----- copy constructor -----
 ----- operator == -----
 k == k2
 ----- find -----
 ('other-key', 21)
 other-keyother not found
*/

#include <iostream>
#include <cstring>

using namespace std;

class Pair {
private:
    char *key;
    int value;

    void copy(const Pair &p) {
        this->key = new char[strlen(p.key) + 1];
        strcpy(this->key, p.key);
        this->value = p.value;
    }

public:
    Pair(char *key = "", int value = 0) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }

    Pair(const Pair &p) {
        copy(p);
    }

    ~Pair() {
        delete[] key;
    }

    Pair &operator=(const Pair &p) {
        if (this != &p) {
            delete[] key;
            copy(p);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Pair &p) {
        out << "('" << p.key << "', " << p.value << ")" << endl;
        return out;
    }

    Pair &operator++() {
        value++;
        return *this;
    }

    Pair operator++(int) {
        Pair temp = *this;
        this->value++;
        return temp;
    }

    Pair operator+(Pair &p) {
        char *temp = new char(strlen(this->key));
        if (strlen(this->key) < strlen(p.key)) {
            strcpy(temp, p.key);
        } else {
            strcpy(temp, this->key);
        }
        Pair pair(temp, this->value + p.value);
        return pair;
    }

    int getValue() {
        return value;
    }

    char *getKey() const {
        return key;
    }
};

class Collection {
private:
    Pair *pairs;
    int n;

    void copy(const Collection &c) {
        this->n = c.n;
        this->pairs = new Pair[n];
        for (int i = 0; i < n; ++i) {
            this->pairs[i] = c.pairs[i];
        }
    }

public:
    Collection(int n = 0) {
        this->n = n;
        this->pairs = new Pair[n];
        for (int i = 0; i < n; ++i) {
            this->pairs[i] = pairs[i];
        }
    }

    Collection(const Collection &c) {
        copy(c);
    }

    ~Collection() {
        delete[] pairs;
    }

    Collection &operator=(const Collection &c) {
        if (this != &c) {
            delete[] pairs;
            copy(c);
        }
        return *this;
    }

    Collection &operator+=(const Pair &p) {
        Pair *temp = new Pair[n + 1];
        for (int i = 0; i < n; ++i) {
            temp[i] = pairs[i];
        }
        temp[n] = p;
        n++;
        delete[] pairs;
        pairs = temp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Collection &c) {
        out << "Size: " << c.n << endl;
        for (int i = 0; i < c.n; ++i) {
            out << c.pairs[i];
        }
        return out;
    }

    bool operator==(const Collection &c) {
        if (this->n != c.n)
            return false;
        for (int i = 0; i < this->n; ++i) {
            if (this->pairs[i].getValue() != c.pairs[i].getValue() && this->pairs[i].getKey() != c.pairs[i].getKey())
                return false;
        }
        return true;
    }

    Pair *find(const char *key) {
        for (int i = 0; i < n; ++i) {
            if (!strcmp(pairs[i].getKey(), key))
                return pairs + i;
        }
        return nullptr;
    }
};

void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}

int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if (k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if (k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair *f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if (f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}