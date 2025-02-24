/*
 Туристичка агенција нуди различни понуди за транспорт на патници.
 За секоја понуда се чуваат податоци за дестинацијата (низа од знаци),
 основна цена (цел број)
 и податок за растојанието до дестинацијата изразено во km (цел број).

 Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите
 за транспорт кои нудат транспорт со автомобил или комбе, соодветно.
 За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата има платен шофер (булова променлива),
 а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

 За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
 •	 конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
 •	 метод cenaTransport, за пресметување на цената на понудата на следниот начин:
     •	 За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
     •	 За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето.
         За секој патник во комбето цената се намалува за 200 (10 поени)
 •	 преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
 Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник,
 бројот на елементите од низата и една понуда T.
 Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата
 кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата). (10 поени)

 Комплетна функционалност на кодот (5 поени)

 Input:
 3
 1 Belgrad 3200 900 1
 1 Bitola 2500 400 0
 2 Sofija 5000 1040 2

 Result:
 Bitola 400 2500
 Belgrad 900 3840
 Sofija 1040 4600
*/

#include <iostream>
#include <cstring>

using namespace std;

class Transport {
protected:
    char destination[50];
    double basePrice;
    int distance;

public:
    Transport(const char *destination = "", double basePrice = 0, int distance = 0) {
        strcpy(this->destination, destination);
        this->basePrice = basePrice;
        this->distance = distance;
    }

    Transport(const Transport &t) {
        strcpy(this->destination, t.destination);
        this->basePrice = t.basePrice;
        this->distance = t.distance;
    }

    virtual double cenaTransport() = 0;

    bool operator<(Transport &t) const {
        return distance < t.distance;
    }

    double getBasePrice() const {
        return basePrice;
    }

    const char *getDestination() const {
        return destination;
    }

    int getDistance() const {
        return distance;
    }
};

class AvtomobilTransport : public Transport {
private:
    bool chauffer;
public:
    AvtomobilTransport(const char *destination = "", double basePrice = 0, int distance = 0, bool chauffer = true)
            : Transport(destination, basePrice, distance) {
        this->chauffer = chauffer;
    }

    AvtomobilTransport(const AvtomobilTransport &a) : Transport(a) {
        this->chauffer = a.chauffer;
    }

    double cenaTransport() {
        if (chauffer)
            return basePrice * 1.2;
        return basePrice;
    }
};

class KombeTransport : public Transport {
private:
    int people;
public:
    KombeTransport(const char *destination = "", double basePrice = 0, int distance = 0, int people = 0) : Transport(
            destination, basePrice, distance) {
        this->people = people;
    }

    KombeTransport(const KombeTransport &k) : Transport(k) {
        this->people = k.people;
    }

    double cenaTransport() {
        return basePrice - people * 200;
    }
};

void sort(Transport **transports, int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (*transports[i + 1] < *transports[i]) {
                Transport *temp = transports[i];
                transports[i] = transports[i + 1];
                transports[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

void pecatiPoloshiPonudi(Transport **transports, int n, Transport &t) {
    Transport **temp = new Transport *[n];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (transports[i]->getBasePrice() > t.getBasePrice()) {
            temp[j] = transports[i];
            j++;
        }
    }
    sort(temp, j);

    for (int i = 0; i < j; ++i) {
        cout << temp[i]->getDestination() << " " << temp[i]->getDistance() << " " << temp[i]->cenaTransport() << endl;
    }
    delete[] temp;
}

int main() {
    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++) {
        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1) {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);

        } else {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }
    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++)
        delete ponudi[i];
    delete[] ponudi;
    return 0;
}