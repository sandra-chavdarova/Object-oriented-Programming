/*
 Create a Race class. Each race is represented by the following information:
 •	the name of the city in which it is performed (array of up to 40 characters)
 •	year (integer)
 •	month (integer)
 •	best time in seconds (float)
 •	length in km (float)
 For this class, implement the following methods:
 •	method complexity() that calculates the complexity of the race according to the following formula:
    best time in seconds / length in km
 •	operator << for printing the race in the following format:
    [City] [month] [year] [complexity]

  Create a MotoGPRace class that, besides with the basic information about the race,
  additionally is represented by the following information:
 •	array of best times of preparation (dynamically allocated array of float numbers)
 •	the number of best times (integer)
 •	number of laps (integer)
 In this class, override the complexity() method so that the average of the best times of the preparations
 multiplied by the MotoGP coefficient will be added to the initial complexity of the race.
 MotoGP coefficient is the same for all MotoGP races and can be changed by the commission (the initial value is 0.4).
 Additionally, if the number of laps is greater than 22, the complexity is increased by 20%.

 For this class, provide the following methods:
 •	operator += - to add a new time of preparation to the dynamically allocated array of the best times of preparation.
    If an attempt is made to add a value less than 9.5, throw an exception (an object of the 'InvalidTimeException' class).
    The exception handling should be performed in the main function on the appropriate place.
    If an exception was thrown, an appropriate error message "Invalid Time" should be printed,
    and this value should not be entered in the array.
 •	operator ++ in postfix notation - to increase the number of laps by one for a given MotoGpRace.
 Provide all the necessary functions for the proper functioning of the program.

 Input:
 5
 5
 1
 Madrid
 2015
 1
 206.3
 34.5
 2
 Mugello
 2019
 6
 99.7
 5.245
 20
 4
 105.2
 103.4
 99.99
 34.2
 1
 Skopje
 2013
 8
 70.0
 1844.5
 2
 Brno
 2017
 7
 85.824
 4.533
 24
 4
 105.2
 103.4
 99.99
 34.2
 1
 Sofia
 2015
 9
 85.824
 4.533
 55.55

 Result:
 ===== Testing - coefficient ======

 List of all races:
 Madrid 1.2015 5.97971
 Mugello 6.2019 53.2876
 Skopje 8.2013 0.0379507
 Brno 7.2017 63.8546
 Sofia 9.2015 18.9332

 List of all races:
 Madrid 1.2015 5.97971
 Mugello 6.2019 78.9968
 Skopje 8.2013 0.0379507
 Brno 7.2017 94.7057
 Sofia 9.2015 18.9332
*/

#include <iostream>
#include <cstring>

using namespace std;

class InvalidTimeException {
public:
    void message() {
        cout << "Invalid Time" << endl;
    }
};

class Race {
protected:
    char city[41];
    int year;
    int month;
    float bestTimeSeconds;
    float lengthKM;
private:
public:
    Race(char *city = "", int year = 0, int month = 0, float bestTimeSeconds = 0.0, float lengthKM = 0) {
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->bestTimeSeconds = bestTimeSeconds;
        this->lengthKM = lengthKM;
    }

    Race(const Race &r) {
        strcpy(this->city, r.city);
        this->year = r.year;
        this->month = r.month;
        this->bestTimeSeconds = r.bestTimeSeconds;
        this->lengthKM = r.lengthKM;
    }

    virtual float complexity() {
        return bestTimeSeconds / lengthKM;
    }

    friend ostream &operator<<(ostream &out, Race &r) {
        out << r.city << " " << r.month << "." << r.year << " " << r.complexity() << endl;
        return out;
    }
};

class MotoGPRace : public Race {
private:
    float *bestTimes;
    int n;
    int laps;
    static float coefficient;

    void copy(const MotoGPRace &m) {
        this->n = m.n;
        this->laps = m.laps;
        this->bestTimes = new float[n];
        for (int i = 0; i < m.n; ++i) {
            this->bestTimes[i] = m.bestTimes[i];
        }
    }

public:
    MotoGPRace(char *city = "", int year = 0, int month = 0, float bestTimeSeconds = 0.0, float lengthKM = 0,
               float *bestTimes = nullptr, int n = 0, int laps = 0) : Race(city, year, month, bestTimeSeconds,
                                                                           lengthKM) {
        this->n = n;
        this->laps = laps;
        this->bestTimes = new float[n];
        for (int i = 0; i < n; ++i) {
            this->bestTimes[i] = bestTimes[i];
        }
    }

    MotoGPRace(const MotoGPRace &m) : Race(m) {
        copy(m);
    }

    ~MotoGPRace() {
        delete[] bestTimes;
    }

    float complexity() {
        float sum = 0, c = Race::complexity();
        for (int i = 0; i < n; ++i) {
            sum += bestTimes[i];
        }
        c += (sum / (float) n) * coefficient;
        if (laps > 22)
            return c * 1.20f;
        return c;
    }

    MotoGPRace &operator+=(float t) {
        if (t < 9.5)
            throw InvalidTimeException();
        else {
            bestTimes[n++] = t;
        }
        return *this;
    }

    MotoGPRace operator++(int) {
        MotoGPRace temp = *this;
        this->laps++;
        return temp;
    }

    void setNumberLaps(int l) {
        laps = l;
    }

    int getNumberLaps() {
        return laps;
    }

    static void setK(float c) {
        coefficient = c;
    }
};

float MotoGPRace::coefficient = 0.4;

int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *nn = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (nn != 0) {
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3) {
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1, time2;
        cin >> time1 >> time2;
        try {
            mgt += time1;
        }
        catch (InvalidTimeException &e) {
            e.message();
        }
        try {
            mgt += time2;
        }
        catch (InvalidTimeException &e) {
            e.message();
        }
        cout << mgt;
    }
    if (testCase == 4) {
        cout << "===== Testing - operator++ ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        float v, koef2;
        cout << (mgt++).getNumberLaps() << endl;
        cout << mgt;
        mgt++;
        cout << mgt;
    }
    if (testCase == 5) {
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6) {
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (choice == 1) {
                rArray[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin >> newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin >> newBest;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            MotoGPRace *pok = dynamic_cast<MotoGPRace *>(rArray[i]);
            if (pok != 0) {
                (*pok)++;
                try {
                    (*pok) += newBest;
                }
                catch (InvalidTimeException &e) {
                    e.message();
                }
                if (flag == 1) {
                    flag = 0;
                    try {
                        *pok += 1.4;
                    }
                    catch (InvalidTimeException &e) {
                        e.message();
                    }
                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    return 0;
}