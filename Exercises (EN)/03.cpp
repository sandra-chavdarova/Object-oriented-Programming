/*
 Create a class for describing cinema. For each cinema, keep information for the following: (5 points)
 •	 the name (string of up to 20 characters)
 •	 the number of the cinema hall (integer)
 •	 student discount (real number)
 •	 ticket price in MKD (real numbe)
 All the data in the class should be private.
 Student discount is the same for all objects of the class cinema and can be changed by the cinema managers.
 For that purpose, provide a method for changing the student discount.
 Student discount is expressed in percentages and the starting value is 17 percent. (5 points)

 The basic price of one movie ticket is calculated using the method: (5 points)
 price (bool isStudent)
 - that returns the price of the ticket. If the variable isStudent is true, a student discount should also be calculated.

 For the needs of CineDays, a special kind of cinema halls, 3D cinema, should be provided.
 For each 3D cinema, additional information is stored: (5 points)
 •	 the movie name that is currently available in that hall (dynamically allocated array of characters),
 •	 the duration of the movie in hours (real number) and
 •	 the logical variable for whether it is a movie premiere or not (premiere - true / regular projection - false).
 A method for calculating the ticket price (5 points) should be available for each 3D cinema:
 price (bool isStudent)
 - the initial price is proportionally increased depending on the duration of the movie.
 If the duration of the movie is longer than 2.5 hours, the initial price is increased by 50 denars.
 If the duration is longer than 3 hours, the initial price is increased by 70 denars.
 If it's a premiere, the initial price of the film is increased by 60 denars.

Also implement the following functions:
 •	 bool searchCinema (Cinema ** c, int n, char * title, bool premiere, bool isStudent)
    - in which the cinema halls that have the same name as the input variable will be searched.
      If the premiere variable is true, the search should be performed only through the 3D halls for which the projection is a premiere,
      otherwise all the cinema halls are searched. If the appropriate cinema is found,
      its name and price are printed and the method returns true.
      If the required cinema is not found, the method returns false. (10 points)
 •	 void cheapestCinema(Cinema ** halls, int n,bool isStudent)
    - to print the name and price of the cheapest cinema in the array.
    Additionally, also print out how many of the cinema halls are 3D, and how many are not 3D, in the following format: (10 points)
    [3D cinema halls: X of total Y]

 Input:
 6

 Result:
 Milenium3D 236.55
 Found
 Not found
*/

#include <iostream>
#include <cstring>

using namespace std;

class Cinema {
private:
    char name[21];
    int number;
    static double discount;
    double basePrice;
public:
    Cinema(char *name = "", int number = 0, double basePrice = 0.0) {
        strcpy(this->name, name);
        this->number = number;
        this->basePrice = basePrice;
    }

    static void setStudentDiscount(double d) {
        discount = d;
    }

    virtual double price(bool isStudent) {
        if (isStudent)
            return basePrice * (1 - discount);
        return basePrice;
    }

    const char *getname() const {
        return name;
    }

    static double getStudentDiscount() {
        return discount;
    }
};

class ThreeDCinema : public Cinema {
private:
    char *available;
    double duration;
    bool premiere;
public:
    ThreeDCinema(char *name = "", int number = 0, double basePrice = 0.0, char *available = "", double duration = 0.0,
                 bool premiere = true) : Cinema(name, number, basePrice) {
        this->available = new char[strlen(available) + 1];
        strcpy(this->available, available);
        this->duration = duration;
        this->premiere = premiere;
    }

    double price(bool isStudent) {
        double index = 0;
        if (duration > 2.5)
            index += 50;
        else if (duration > 3)
            index += 70;
        if (premiere)
            index += 60;
        return Cinema::price(isStudent) + index;
    }
};

double Cinema::discount = 0.17;

bool searchCinema(Cinema **c, int n, char *title, bool premiere, bool isStudent) {
    for (int i = 0; i < n; ++i) {
        ThreeDCinema *t = dynamic_cast<ThreeDCinema *>(c[i]);
        if (premiere && !strcmp(c[i]->getname(), title) && t) {
            cout << c[i]->getname() << " " << c[i]->price(isStudent) << endl;
            return true;
        } else if (!strcmp(c[i]->getname(), title)) {
            cout << c[i]->getname() << " " << c[i]->price(isStudent) << endl;
            return true;
        }
    }
    return false;
}

void cheapestCinema(Cinema **halls, int n, bool isStudent) {
    int index = 0, threeD = 0;
    for (int i = 0; i < n; ++i) {
        if (halls[i]->price(isStudent) < halls[index]->price(isStudent))
            index = i;
        ThreeDCinema *t = dynamic_cast<ThreeDCinema *>(halls[i]);
        if (t)
            threeD++;
    }
    cout << "Cheapest movie hall: " << halls[index]->getname() << " " << halls[index]->price(isStudent) << endl;
    cout << "3D cinema halls: " << threeD << " from total " << n << endl;
}

int main() {
    int tip, n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin >> tip;
    if (tip == 1) {//Cinema
        cin >> name >> no >> ticketPrice;
        Cinema k1(name, no, ticketPrice);
        cout << "Cinema created with name: " << k1.getname() << endl;
    } else if (tip == 2) {//price - Cinema
        cin >> name >> no >> ticketPrice >> isStudent;
        Cinema k1(name, no, ticketPrice);
        cout << "Initial price for the cinema with name " << k1.getname() << " is: " << k1.price(isStudent) << endl;
    } else if (tip == 3) {//3D Cinema
        cin >> name >> no >> ticketPrice >> movieName >> hours >> premiere;
        ThreeDCinema s(name, no, ticketPrice, movieName, hours, premiere);
        cout << "Cinema created with name " << s.getname() << " and discount " << s.getStudentDiscount() << endl;
    } else if (tip == 4) {//price - 3DCinema
        cin >> name >> no >> ticketPrice >> movieName >> hours >> premiere >> isStudent;
        ThreeDCinema s(name, no, ticketPrice, movieName, hours, premiere);
        cout << "The price for the cinema " << s.getname() << " is: " << s.price(isStudent) << endl;
    } else if (tip == 5) {//cheapest Cinema
        Cinema **halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[2] = new ThreeDCinema("Home", 44, 299, "Godfather", 5, false);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);
        cheapestCinema(halls, 5, true);
    } else if (tip == 6) {//search
        Cinema **halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);

        if (searchCinema(halls, 5, "Milenium3D", true, true))
            cout << "Found" << endl;
        else cout << "Not found" << endl;

        if (searchCinema(halls, 5, "CinePlexx1", false, false))
            cout << "Found" << endl;
        else cout << "Not found" << endl;

    } else if (tip == 7) {//change price
        Cinema **halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1", 1, 350);
        halls[1] = new ThreeDCinema("Milenium3D", 44, 285, "Shrek", 2.5, false);
        halls[2] = new ThreeDCinema("Vardar", 12, 333, "StarWars", 4, true);
        halls[2] = new ThreeDCinema("Domasno", 44, 299, "Godfather", 5, false);
        halls[3] = new Cinema("Cineplexx2", 2, 333);
        halls[4] = new ThreeDCinema("Cinedays", 1, 310, "ManInBlack", 5, true);
        halls[2]->setStudentDiscount(0.9);
        cheapestCinema(halls, 4, true);
    }
    return 0;
}
