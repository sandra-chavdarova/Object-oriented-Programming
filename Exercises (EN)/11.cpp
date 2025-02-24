/*
 Create a class for describing post parcels with information for:
 •	ID number of the parcel (integer)
 •	processing price (integer).
 The price for processing a parcel is equal for all parcels and can be changed with the function setProcessingPrice.
 The initial value of this price is 150 MKD.

 Create a class Parcel with all required methods for full functionality of the program (10 points).
 A parcel can be in shape of envelope and for each envelope additional information is needed,
 such as the width, height of the envelope (integers) and the receiver of the envelope (char array of max 50).

 Create a functioning class Envelope that also implements the following method (10 points):
 •	price() - that returns the price for sending the envelope which is calculated as: C + L * W * 0.3,
    where C is the price for processing a basic parcel while L and W are the length and the width of the envelope.

 Create a class PostOffice that keeps information for at most 100 envelops and number (n<100) of envelops sent in that office. (5 points)

 The class should implement following methods:
 •	int sendEnvelope(int id, char* receiver, int length, int width) - that adds an envelope with the given arguments in the array of envelops.
    This method returns the price for sending the envelope. (5 points)
 •	void printEnvelopsTo(char* receiver) - that prints the ID of the envelopes that are addressed to the passed receiver.
    The printing is in the following format (5 points):
    For [receiver] are envelops with ids:  [ID1] [ID2]  ...

 Fully functioning program. (5 points).

 Input:
 2
 4 1
 5 2 V.Velkovski20b 34 6

 Result:
 Parcel with id [1] is created
 Price of sending envelope with ID: 2 To: V.Velkovski20b is: 211
*/

#include <iostream>
#include <cstring>

using namespace std;

class Parcel {
protected:
    int id;
    static int processingPrice;
public:
    Parcel(int id = 0) {
        this->id = id;
    }

    static void setProcessingPrice(int p) {
        processingPrice = p;
    }

    int getId() {
        return id;
    }
};

class Envelope : public Parcel {
private:
    int width;
    int height;
    char receiver[51];
public:
    Envelope(int id = 0, char *receiver = "", int width = 0, int height = 0) : Parcel(id) {
        this->width = width;
        this->height = height;
        strcpy(this->receiver, receiver);
    }

    int price() {
        return processingPrice + height * width * 0.3;
    }

    const char *getReceiver() {
        return receiver;
    }
};

class PostOffice {
private:
    Envelope *envelopes;
    int n;

    void copy(const PostOffice &p) {
        this->n = p.n;
        this->envelopes = new Envelope[n];
        for (int i = 0; i < n; ++i) {
            this->envelopes[i] = p.envelopes[i];
        }
    }

public:
    PostOffice(Envelope *envelopes = nullptr, int n = 0) {
        this->n = n;
        this->envelopes = new Envelope[n];
        for (int i = 0; i < n; ++i) {
            this->envelopes[i] = envelopes[i];
        }
    }

    PostOffice(const PostOffice &p) {
        copy(p);
    }

    ~PostOffice() {
        delete[] envelopes;
    }

    PostOffice &operator=(const PostOffice &p) {
        if (this != &p) {
            delete[] envelopes;
            copy(p);
        }
        return *this;
    }

    int sendEnvelope(int id, char *receiver, int length, int width) {
        Envelope newEnvelope(id, receiver, width, length);
        if (n < 100) {
            Envelope *temp = new Envelope[n + 1];
            for (int i = 0; i < n; ++i) {
                temp[i] = envelopes[i];
            }
            temp[n++] = newEnvelope;
            delete[] envelopes;
            envelopes = temp;
        }
        return newEnvelope.price();
    }

    void printEnvelopsTo(char *receiver) {
        cout << "For " << receiver << " are envelops with ids: ";
        for (int i = 0; i < n; ++i) {
            if (!strcmp(envelopes[i].getReceiver(), receiver))
                cout << envelopes[i].getId() << " ";
        }
        cout << endl;
    }
};

int Parcel::processingPrice = 150;

int main() {
    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:"
                 << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: "
                 << p2.price() << endl;
        }
    }
    return 0;
}