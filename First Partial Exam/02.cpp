/*
 Да се имплементира класа List во којашто ќе се чуваат информации за:
    •	броеви што се дел од листата (динамички алоцирана низа од цели броеви)
    •	бројот на броеви што се дел од листата
 За класата да се дефинираат следните методи:
    •	конструктор (со аргументи), copy-конструктор, деструктор, оператор =
    •	void pecati() метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
    •	int sum() метод што ја враќа сумата на елементите во листата
    •	double average() метод што ќе го враќа просекот на броевите во листата

 Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:
    •	низа од листи (динамички алоцирана низа од објекти од класата List)
    •	број на елементи во низата од листи (цел број)
    •	број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
 За класата потребно е да ги дефинирате следните методи:
    •	конструктор (default), copy-конструктор, деструктор, оператор =
    •	void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
    •	доколку контејнерот е празен се печати само порака The list is empty.
    •	void addNewList(List l) метод со којшто се додава листа во контејнерот
 Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
    •	int sum() метод што ја враќа сумата на сите елементи во сите листи
    •	double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот

 Input:
 2
 1
 1
 2
 0 1
 0

 Result:
 List number: 1 List info: 1: 1 sum: 1 average: 1
 Sum: 1 Average: 1
 Successful attempts: 1 Failed attempts: 1
*/

#include <iostream>

using namespace std;

class List {
private:
    int *numbers;
    int n;

    void copy(const List &l) {
        this->n = l.n;
        this->numbers = new int[this->n];
        for (int i = 0; i < n; i++) {
            this->numbers[i] = l.numbers[i];
        }
    }

public:
    List(int *numbers = nullptr, int n = 0) { // constructor
        this->n = n; // Update the size
        this->numbers = new int[this->n];
        for (int i = 0; i < this->n; i++) {
            this->numbers[i] = numbers[i];
        }
    }

    List(const List &l) { // copy-constructor
        copy(l);
    };

    ~List() {
        delete[] numbers;
    };

    List &operator=(const List &l) {
        if (this != &l) {
            delete[] numbers;
            copy(l);
        }
        return *this;
    }

    int getN() {
        return n;
    }

    double sum() {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += double(numbers[i]);
        }
        return sum;
    }

    double average() {
        return sum() / double(n);
    }

    void print() {
        cout << n << ": ";
        for (int i = 0; i < n; i++) {
            cout << numbers[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }
};

class ListContainer {
private:
    List *lists;
    int n;
    int tries;

    void copy(const ListContainer &lc) {
        this->n = lc.n;
        this->tries = lc.tries;
        this->lists = new List[this->n];
        for (int i = 0; i < n; i++) {
            this->lists[i] = lc.lists[i];
        }
    }

public:
    ListContainer() {
        this->tries = 0;
        this->n = 0;
        this->lists = new List[this->n];
    }

    ListContainer(const ListContainer &lc) {
        copy(lc);
    }

    ~ListContainer() {
        delete[] lists;
    }

    ListContainer &operator=(const ListContainer &lc) {
        if (this != &lc) {
            delete[] lists;
            copy(lc);
        }
        return *this;
    }

    int sum() {
        int listsSum = 0;
        for (int i = 0; i < n; i++)
            listsSum += lists[i].sum();
        return listsSum;
    }

    double average() {
        double sum = 0;
        int elements = 0;
        for (int i = 0; i < n; i++) {
            sum += lists[i].sum();
            elements += lists[i].getN();
        }
        return sum / elements;
    }

    void addNewList(List l) {
        tries++;
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (lists[i].sum() == l.sum()) {
                flag = false;
                break;
            }
        }
        if (flag) {
            List *tmp = new List[n + 1];
            for (int i = 0; i < n; i++) {
                tmp[i] = lists[i];
            }
            tmp[n++] = l;
            delete[] lists;
            lists = tmp;
        }
    }

    void print() {
        if (n == 0) {
            cout << "The list is empty" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            cout << "List number: " << i + 1 << " List info: ";
            lists[i].print();
        }
        cout << "Sum: " << sum() << " Average: " << average() << endl;
        cout << "Successful attempts: " << n << " Failed attempts: " << tries - n << endl;
    }
};


int main() {
    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];

        }

        List l = List(niza, n);

        lc.addNewList(l);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();

    } else {
        lc.print();
    }
}